/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundsettingsdlg.h"

#include <math.h>
#include <iostream>

#include "static_settings.h"
#include "fftprocessor.h"

#include <QMessageBox>
#include "complexnumber.h"

#define PLOT_HISTOGRAM

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);

    ap = new audioProcessor(DEFAULT_FFT_SIZE);
    ap->setFrameLength(DEFAULT_FRAME_LENGTH);

    mainPlot = new QwtPlot();
    initPlot(mainPlot, "Frequency", "Magnitude", 0, ap->getSampleRate()/2, 0, 5);

    mainCurveZoomer = new QwtPlotZoomer(mainPlot->canvas(),true);
    mainCurveZoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
    mainCurveZoomer->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);

    ui->verticalLayout->insertWidget(0,mainPlot);

    mainCurveXData = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);
    mainCurveYData = (double*) malloc(sizeof(double) * DEFAULT_FFT_SIZE/2+1);
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

   // mainPlot->setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine ());


    connect(ui->soundcardSettingsAction, SIGNAL(triggered()), this, SLOT(onSoundcardSettingsAction()));
    connect(ui->continuousRunPushButton, SIGNAL(pressed()), this, SLOT(onContinuousRunPushButton()));
    connect(ui->stopRunPushButton, SIGNAL(pressed()), this, SLOT(onStopRunPushButton()));
    connect(ap, SIGNAL(frameProcessed(fftProcessor*)), this, SLOT(onFrameProcessed(fftProcessor*)));
}


MainWindow::~MainWindow()
{
    delete mainPlot;
    //delete mainCurveZoomer;
    delete ui;
    delete ap;
}

void MainWindow::initPlot(QwtPlot* plot, const char* xTitle, const char* yTitle, int xmin, int xmax, int ymin, int ymax)
{
    QwtText xQwTitle = QwtText(xTitle);
    QwtText yQwTitle = QwtText(yTitle);

    QwtText title = QwtText("QwtPlot");
    title.setFont(QFont("SansSerif", 8));

    QwtText xAxisTitle = xQwTitle;
    xAxisTitle.setFont(QFont("SansSerif", 8));
    QwtText yAxisTitle = yQwTitle;
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

void MainWindow::onSoundcardSettingsAction()
{
    soundSettingsDlg dlg(ap);
    dlg.exec();
}

void MainWindow::onContinuousRunPushButton()
{
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

void MainWindow::onStopRunPushButton()
{
    ap->stopAudio();
}

void MainWindow::onFrameProcessed(fftProcessor *fft)
{
    unsigned int n = fft->getfftSize()/2+1;
    double one_over_n = 1/((double) n); //to make it a little bit faster

    /*
��� ����������� ������������� ������������� � ��, � ������ ������������ ��������
    � ������� �� ������� 20lg(Ai/Amax), ��� ����������
��� ������������� ���������� ��������� ������������ ���� ��� ����������� ��������
    ������� �� ��������� �������, �������� ��������-�������
*/
    /*
� ���� ���������� �������� ���:
-����� N ������� ������ ������� ������� 2 (2^�).
-���������� ����������� ���, ������ ����� ��������� ������, �������� 2N ��������,
-�������� ������� ��� ������ ������� �������� ��������� �������� �������������� �
    ������ ����� � �������� �� ����� ��. ������ (������ ����������� ������). �������� N �������� �� ������� �������� �� 0 �� N/2-1 ������������ ������ � ������� 0..Fs/2 (Fs-������� �������������), ��� ����������� ����� ������������ ������ ��� �����, ��������� ����� �� N/2 �� N �����������.
- ��� ������������� �������� ���� Amax(����������� ��������� �������� ��������) �
    ����������� �������� � ��������� Di = 20lg(Ai/Amax) - ��� ��� ����������, �.�. �������� ��������������� �������� ���������� �� ��� �������� DP = 10lg(Ai/Amax).
-���������� �������� � ������� ��� ��� ���� (��������, �������, �������, ������� � �.�.).
-���������� ����������� ��� ������������ ��� ��������� (����������, �����������,
    ������������� � �. �.) ��� �������������.
-����� �������� ��� ��� ������ �����.
      */
    /*
2. ����� ����� ������ FFT. �������� ����� ����� ����� [2]. ������ ����� ��������, ��� ��
    �������� _������_ � ���������, ������ ������� ������ 2^N.

3. ��������� FFT ������������ ��������� �������.
3.1 ������ ������, � ������� ����� �������� ���������.
    ������ ���� ����� ������� ����� ����� ����������� �� ����� ��������� �������������� � ������
    ������ ���������������� ����� ���������� ��������������. ����� �������,
    y = sqrt( re(x(i))^2 + im(x(i))^2 ), ��� x = ��������� FFT,
    re(x(i)) ������������ ����� i-�� ��������, im(x(i)) - ������ ����� i-�� ��������.
3.2 ����� ��������� "��������" ������� ���� ���������� ������������ ������� y, power = sum(y).
3.3 � ����� ����� ������ ��������� y(i) = 10 * log10( y(i) / power ). �� ����,
    ��� ���� ���������� ������ �� ����� ��������� �������. ���� ������ � �������
    ������� �������� ����. ����� �� � ������������, ������, ���������� �����-�����
    (�� ������) ������ �� ��, ������� ����� Adobe Audition ��� ������������ �������.
3.4 ����� ����� ����������� �������� �������-����������, ��� ��� ��� ��������
    "�������������" �������, ����������� ������ ���������.

4. ����� ��������� ���������� ������� �� �������� ���������� ������ � �
    ������ ����� ���������� ��������� ���� ���������� �������� ���������������.
    ������, ��� ������ �����, ���������� ����� ������� �������-��������� ����������
    �� � ��������, � � ��������������� �������. ������� ����������, ������ ������,
    WinAmp ������ ������ ���.

5. �����������. ��� �� ��� �� ��� ������.
      */
    for(unsigned int i=0; i<n; i++)
    {
#if 0
        //log+abs fft:
        mainCurveYData[i] = 20.0 * log10(one_over_n * fft->fftOutAbs[i]);
#elif 1
        //abs fft:
        mainCurveYData[i] = sqrt(fft->fftOut[i][0]*fft->fftOut[i][0] + fft->fftOut[i][1]*fft->fftOut[i][1]);
#else
        //real input:
        mainCurveYData[i] = /*fft->fftIn[i]*/rand()%200-100;
#endif

        if(subCurveYData[i] < mainCurveYData[i]) subCurveYData[i] = mainCurveYData[i];
        if(subCurveYData[i] > 0.1) subCurveYData[i]-=0.1;
    }

    mainPlot->setAxisScale(QwtPlot::yLeft, 0, 4);
#ifndef PLOT_HISTOGRAM
    mainCurve->setSamples(mainCurveXData, mainCurveYData, fft->getfftSize()/2+1);
    subCurve->setSamples(mainCurveXData, subCurveYData, fft->getfftSize()/2+1);
#else
    QVector<QwtIntervalSample> samples( n );
    for ( uint i = 0; i < n; i++ )
    {
        QwtInterval interval( double( i ), i + 1.0 );
        interval.setBorderFlags( QwtInterval::ExcludeMaximum );

        samples[i] = QwtIntervalSample( mainCurveYData[i], interval );
    }
    histogram->setData( new QwtIntervalSeriesData( samples ) );
#endif

    mainPlot->replot();
}

