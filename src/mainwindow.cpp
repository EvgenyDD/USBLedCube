#include "mainwindow.h"
#include <QMainWindow>

#include <math.h>
#include <iostream>

#include "static_settings.h"
#include "fftprocessor.h"

#include <QMessageBox>
#include "complexnumber.h"

//#define PLOT_HISTOGRAM

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      space(29),
      deltaX(24),
      deltaY(13),
      deltaZ(12),
      voxelDiameter(4),
      VolumeRBptr(0),
      specMult(1),
      SpectreRBptr(0),
      GraphRBptr(0)
{
    setupUI();

    ap = new audioProcessor(DEFAULT_FFT_SIZE);
    ap->setFrameLength(DEFAULT_FRAME_LENGTH);

    setCentralWidget();

    Cube = new CubeClass();
    // Cube->start(); //start thread

    HIDDevice = new USBHID(this, Cube->GetPCube());
    HIDDevice->updateHID();

    HIDDevice->setWorkingMode(PC_MONITORING/*PC_CONTROLS*/);
    HIDDevice->SetRxFromDevice();

    if(!HIDDevice->isLibLoaded())
        QMessageBox::about(this, "Error", "Library 'hidapi.dll' was not loaded");

    connect(soundcardSettingsAction, SIGNAL(triggered()), this, SLOT(onSoundcardSettingsAction()));
    connect(ap, SIGNAL(frameProcessed(fftProcessor*)), this, SLOT(onFrameProcessed(fftProcessor*)));
    connect(displayCheckBox, SIGNAL(clicked(bool)), this, SLOT(onVisualizeClicked(bool)));
    connect(HIDDevice, SIGNAL(HIDStateChanged(bool)), this, SLOT(onHIDUpdate(bool)));

    // connect(runButton, SIGNAL(pressed()), this, SLOT(onRunButton()));

    paintTimer = new QTimer();
    paintTimer->setInterval(20);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(cubeRePaint()));
    paintTimer->start();

    effectsBox->addItem("Test [ON/OFF]");
    effectsBox->addItem("Random Pixel");
    effectsBox->addItem("Random Pixel Accumulate");
    effectsBox->addItem("Rain");
    effectsBox->addItem("True SNAKE");
    effectsBox->addItem("Move Voxels Along Z Axis");
    effectsBox->addItem("Outline Box");
    effectsBox->addItem("Outline Random Boxes");
    effectsBox->addItem("Random Midway to Dest");
    effectsBox->addItem("Ripples");
    effectsBox->addItem("Side Waves");
    effectsBox->addItem("Firework");
    effectsBox->addItem("Random Invert");
    effectsBox->addItem("Sine Lines");
    effectsBox->addItem("Worm Qqueeze");
    effectsBox->addItem("Random Send Parallel");

    connect(effectsBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEffectChanged(int)));

    /* Add audio devices to list */
    for(int i=0; i < ap->getDeviceCount(); i++)
    {
        QByteArray inArray = QString(ap->getDeviceName(i)).toUtf8();
        QString out;

        for(int i=0; i<inArray.length(); i++)
            if(inArray[i] != (char)4)
            {
                if(inArray[i+1] == (char)4)
                    out.append(QChar(1024+inArray[i]));
                else
                    out.append(QChar(inArray[i]));
            }
        deviceBox->addItem(out);
    }

    for(int i=0; i<VOL_RB_SIZE; i++)
        VolumeRB[i]=0.0000001;
}


MainWindow::~MainWindow()
{
    HIDDevice->setWorkingMode(PC_MONITORING);
    Cube->terminate();

    delete mainPlot;
    delete ap;
}




void MainWindow::initPlot(QwtPlot* plot, const char* xTitle, const char* yTitle, int xmin, int xmax, int ymin, int ymax)
{
    QwtText xQwTitle = QwtText(xTitle), yQwTitle = QwtText(yTitle);

    QwtText title = QwtText("QwtPlot");
    title.setFont(QFont("SansSerif", 8));

    QwtText xAxisTitle = xQwTitle,yAxisTitle = yQwTitle;
    xAxisTitle.setFont(QFont("SansSerif", 8));
    yAxisTitle.setFont(QFont("SansSerif", 8));

    plot->setAxisAutoScale(QwtPlot::yLeft);
    plot->setAxisAutoScale(QwtPlot::xBottom);

    QFont axisFont = QFont("SansSerif", 6);
    plot->setAxisFont(QwtPlot::xBottom, axisFont);
    plot->setAxisFont(QwtPlot::yLeft, axisFont);
    // Axis
    plot->setAxisTitle(QwtPlot::xBottom, xAxisTitle);
    plot->setAxisTitle(QwtPlot::yLeft, yAxisTitle);


    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(plot);

    plot->setCanvasBackground(QColor(255,255,255));
    plot->setGeometry(QRect(20, 20, 600, 220));
    plot->resize(200, 200);

#ifndef PLOT_HISTOGRAM
    plot->setAxisScale(QwtPlot::xBottom, xmin, xmax);
    plot->setAxisScale(QwtPlot::yLeft, ymin, ymax);
#endif

    QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());
    panner->setMouseButton(Qt::RightButton);
}





// Methods
void MainWindow::onSoundcardSettingsAction()
{
    dlg = new soundSettingsDlg(ap);
    connect(dlg, SIGNAL(accepted()), this, SLOT(soundSettDlgAccptd()));
    dlg->exec();
}


void MainWindow::onRunButton()
{
    mainPlot->setVisible(true);
    deviceBox->setVisible(true);

    Cube->CubeReset();

    qDebug() << "Device Sample Rate: " << ap->getSampleRate();
    qDebug() << "FFT size: " << DEFAULT_FFT_SIZE;

    for(int i=0; i < DEFAULT_FFT_SIZE/2+1; i++)
        mainCurveXData[i] = ((double) i) / (DEFAULT_FFT_SIZE/2+1) * ap->getSampleRate()/2;

    //mainPlot->setAxisScale(QwtPlot::yLeft, -120, 10);
    mainPlot->setAxisScale(QwtPlot::xBottom, 0, ap->getSampleRate()/2);

    int err = ap->startAudio();
    if(err < 0)
    {
        QString message(ap->getErrorText(err));
        QMessageBox messageBox(QMessageBox::Critical, "Error Starting Audio", message);
        messageBox.exec();
    }
}


void MainWindow::onStopButton()
{
    mainPlot->setVisible(false);
    ap->stopAudio();
}


void MainWindow::onVisualizeClicked(bool state)
{
    CubeVisualizator->setVisible(state);
    centralWidget->updateGeometry();
    this->setFixedSize(state ? QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX) : sizeHint());
}


void MainWindow::onHIDUpdate(bool state)
{
    static int prevState=100;

    if(prevState != state)
    {
        modeRadioButton[RADIO_MONITOR]->setEnabled(state);

        if(state == false)
            qDebug()<<">> Device Disconnected!!!";
    }

    prevState = state;
}


void MainWindow::onRadio_Monitor()
{
    qDebug()<<">> RADIO_MONITOR is active";

    Cube->terminate();
    Cube->newEffect = -1;

    HIDDevice->setWorkingMode(PC_MONITORING);
    HIDDevice->SetRxFromDevice();

    effectsBox->setVisible(false);
    VolumeCheckSmooth->setVisible(false);
    SpectreCheckSmooth->setVisible(false);
    deviceBox->setVisible(false);

    if(ap->isRunning)
        onStopButton();

    centralWidget->updateGeometry();
    this->setFixedSize(sizeHint());
}


void MainWindow::onRadio_Effects()
{
    qDebug()<<">> RADIO_EFFECTS is active";

    Cube->start();
    Cube->newEffect = effectsBox->currentIndex();

    effectsBox->setVisible(true);
    VolumeCheckSmooth->setVisible(false);
    SpectreCheckSmooth->setVisible(false);
    deviceBox->setVisible(false);

    if(ap->isRunning)
        onStopButton();

    HIDDevice->setWorkingMode(PC_CONTROLS);
    HIDDevice->SetTxToDevice();

    centralWidget->updateGeometry();
    this->setFixedSize(sizeHint());
}


void MainWindow::onRadio_Visualizer()
{
    qDebug()<<">> RADIO_VISUALIZER is active";

    Cube->terminate();
    Cube->newEffect = -1;

    effectsBox->setVisible(false);
    VolumeCheckSmooth->setVisible(true);
    SpectreCheckSmooth->setVisible(true);

    HIDDevice->setWorkingMode(PC_CONTROLS);
    HIDDevice->SetTxToDevice();

    centralWidget->updateGeometry();
    this->setFixedSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

    onRunButton();
}


void MainWindow::soundSettDlgAccptd()
{
    qDebug()<<">> soundSettDlgAccptd";
    if(ap->isRunning)
    {
        onStopButton();
        onRunButton();
    }
}


void MainWindow::onDeviceChooseChanged(int num)
{
    if(ap->isRunning)
    {
        onStopButton();
        ap->setInputDevice(num);
        onRunButton();
    }
}


void MainWindow::onEffectChanged(int num)
{
    Cube->newEffect = num;
}
