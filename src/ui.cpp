#include "mainwindow.h"
#include <QMainWindow>
#include "soundsettingsdlg.h"

#include <math.h>
#include <iostream>

#include "static_settings.h"
#include "fftprocessor.h"

#include <QMessageBox>
#include "complexnumber.h"

using namespace std;


void MainWindow::setupUI()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("MainWindowClass"));

    this->resize(600, 400);

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

    gridLayout = new QGridLayout();

    //runButton = new QPushButton(centralWidget);
    //    runButton->setObjectName(QString::fromUtf8("continuousRunPushButton"));

    soundcardSettingsAction = new QAction(this);
    soundcardSettingsAction->setObjectName(QString::fromUtf8("soundcardSettingsAction"));

    QMainWindow::setCentralWidget(centralWidget);

    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    //menuBar->setGeometry(QRect(0, 0, 600, 26));

    menu = new QMenu(menuBar);
    menu->setObjectName(QString::fromUtf8("menu"));
    this->setMenuBar(menuBar);
    menu->addAction(soundcardSettingsAction);

    menuBar->addAction(menu->menuAction());

    //    mainToolBar = new QToolBar(this);
    //    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    //    this->addToolBar(Qt::TopToolBarArea, mainToolBar);

    //    statusBar = new QStatusBar(this);
    //    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    //    this->setStatusBar(statusBar);

    this->setWindowTitle(QString());
    soundcardSettingsAction->setText(QApplication::translate("MainWindowClass", "Sound Settings", 0));

    //runButton->setText(QApplication::translate("MainWindowClass", "Run", 0));

    menu->setTitle(QApplication::translate("MainWindowClass", "&Settings", 0));

    QMetaObject::connectSlotsByName(this);
}


void MainWindow::setCentralWidget()
{
    mainPlot = new QwtPlot();
    initPlot(mainPlot, "Frequency", "Magnitude", 0, ap->getSampleRate()/2, 0, 5);

    mainCurveZoomer = new QwtPlotZoomer(mainPlot->canvas(),true);
    mainCurveZoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
    mainCurveZoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);

    mainCurveXData = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);
    mainCurveYData = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);
    mainCurveYDataNormed = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);
    subCurveYData  = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);

    for(int i=0; i<DEFAULT_FFT_SIZE/2+1; i++) subCurveYData[i] = 0;

#ifdef PLOT_HISTOGRAM
    histogram = new QwtPlotHistogram();
    histogram->setStyle(QwtPlotHistogram::Columns); //lines
    histogram->setPen(QPen(Qt::green)); //black
    histogram->setBrush(QBrush(Qt::green));
    histogram->attach(mainPlot);
#endif

#ifndef PLOT_HISTOGRAM
    mainCurve = new QwtPlotCurve();
    subCurve = new QwtPlotCurve();
    mainCurve->attach(mainPlot);
    subCurve->attach(mainPlot);
#endif

    //right
    cubeBase = new QPixmap(440,400);
    QPainter *paint = new QPainter(cubeBase);
    cubeBase->fill(Qt::white);
    paintCubeBase(paint);

    CubeVisualizator = new QLabel();
    CubeVisualizator->setPixmap(*cubeBase);

    //1lvl
    modeRadioButton[0] = new QRadioButton("Monitor");
    modeRadioButton[0]->setChecked(true);
    modeRadioButton[1] = new QRadioButton("Effects");
    modeRadioButton[2] = new QRadioButton("Equalizer");
    displayCheckBox = new QCheckBox("Visualize");
    displayCheckBox->setChecked(true);
    //sub
    line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);

    //2lvl
    effectsBox = new QComboBox();

    //sub
    //    line2 = new QFrame();
    //    line2->setFrameShape(QFrame::HLine);
    //    line2->setFrameShadow(QFrame::Sunken);

    //3lvl
    deviceBox = new QComboBox();

    effectsBox->setVisible(false);
    //   line2->setVisible(false);
    deviceBox->setVisible(false);

    SpectreCheckSmooth = new QCheckBox("~Spectre");
    VolumeCheckSmooth = new QCheckBox("~Volume");
    SpectreCheckSmooth->setVisible(false);
    SpectreCheckSmooth->setChecked(true);
    VolumeCheckSmooth->setVisible(false);
    VolumeCheckSmooth->setChecked(true);

    gridLayout->addWidget(modeRadioButton[0], 0,0);
    gridLayout->addWidget(modeRadioButton[1], 0,1);
    gridLayout->addWidget(modeRadioButton[2], 0,2);
    gridLayout->addWidget(displayCheckBox,    0,3);

    gridLayout->addWidget(deviceBox, 0,4);
    gridLayout->addWidget(VolumeCheckSmooth, 0, 5);
    gridLayout->addWidget(SpectreCheckSmooth, 0, 6);
    gridLayout->addWidget(mainPlot,  1,4, 4,3);

    gridLayout->addWidget(line1, 1,0,1,4);
    gridLayout->addWidget(effectsBox, 2,0, 1,4);

    //    gridLayout->addWidget(line2, 3,0,1,4);

    gridLayout->addWidget(CubeVisualizator, 4, 0, 1, 4);

    mainPlot->setVisible(false);
    centralWidget->setLayout(gridLayout);

    centralWidget->updateGeometry();
    this->setFixedSize(/*QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX) : */sizeHint());

    connect(modeRadioButton[RADIO_MONITOR], SIGNAL(clicked()), this, SLOT(onRadio_Monitor()));
    connect(modeRadioButton[RADIO_EFFECTS], SIGNAL(clicked()), this, SLOT(onRadio_Effects()));
    connect(modeRadioButton[RADIO_VISUALIZER], SIGNAL(clicked()), this, SLOT(onRadio_Visualizer()));

    connect(deviceBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onDeviceChooseChanged(int)));
}
