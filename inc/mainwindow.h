/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_histogram.h>

#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>

#include "fftprocessor.h"

//#include "audioprocessor_io_copy.h"
//#include "audioprocessor_noise.h"
//#include "audioprocessor_sine.h"
#include "audioprocessor_fft.h"

#include "soundsettingsdlg.h"

#include "static_settings.h"

#include "usbhid.h"
#include "cubeclass.h"

#define SP  space
#define SX  deltaX
#define SY  deltaY
#define SZ  deltaZ
#define CR  voxelDiameter


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupUI();

    soundSettingsDlg *dlg;
    audioProcessor *ap;

private:
    QwtPlot *mainPlot;
    QwtPlotCurve *mainCurve;
    QwtPlotCurve *subCurve;
    QwtPlotZoomer *mainCurveZoomer;
    QwtPlotHistogram *histogram;

    double *mainCurveXData;
    double *mainCurveYData;
    double *mainCurveYDataNormed;
    double *subCurveYData;

    void initPlot(QwtPlot* plot, const char* xTitle, const char* yTitle, int xmin, int xmax, int ymin, int ymax);
    void setCentralWidget();
    void paintCubeBase(QPainter *painter);
    void paintCubeVoxels(QPainter *painter);

    USBHID *HIDDevice;
    CubeClass *Cube;

    unsigned char space, deltaX, deltaY, deltaZ, voxelDiameter;

    QMenu *menu;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QWidget *centralWidget;

    QGridLayout *gridLayout;

    QPixmap *cubeBase;
    QLabel *CubeVisualizator;

    QAction *soundcardSettingsAction;


    //Volume Ring Buffer
#define VOL_RB_SIZE (14*4)  //14 samples in 1 second
    float VolumeRB[VOL_RB_SIZE];//5 sec max_volume measure interval, sampling is 70ms = 5/0.070 = 72
    int VolumeRBptr;
    float VolMaxPower;
    float VolMinPower;

    //Spectre Ring Buffer
#define SPECTRE_RB_SIZE (14*4)  //14 samples in 1 second
    float SpectreRB[SPECTRE_RB_SIZE];//5 sec max_volume measure interval, sampling is 70ms = 5/0.070 = 72
    int SpectreRBptr;
    float specMult;

    //Graph Ring Buffer
#define GRAPH_RB_SIZE (14*4) //14 samples in 1 second
    float GraphRB[GRAPH_RB_SIZE];
    int GraphRBptr;

    float map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }


    //1lvl
    QRadioButton *modeRadioButton[3];
    enum {RADIO_MONITOR=0, RADIO_EFFECTS=1, RADIO_VISUALIZER=2}RADIO_BUTTONS;

    QCheckBox *displayCheckBox;
    //sub
    QFrame* line1;

    //2lvl
    QComboBox *effectsBox;
    //QCheckBox *randomCheckBox;
    //QComboBox *randomTimeBox;

    //sub
    QFrame* line2;

    //3lvl
    QComboBox *deviceBox;
    QTimer *paintTimer;

    QSpinBox *spinBox;
    QCheckBox *SpectreCheckSmooth;
    QCheckBox *VolumeCheckSmooth;

public slots:

protected slots:    

private slots:
    void onSoundcardSettingsAction();
    void onRunButton();
    void onStopButton();
    void onFrameProcessed(fftProcessor *fft);
    void cubeRePaint();
    void onVisualizeClicked(bool state);
    void onHIDUpdate(bool state);
    void onRadio_Visualizer();
    void onRadio_Effects();
    void onRadio_Monitor();
    void soundSettDlgAccptd();
    void onDeviceChooseChanged(int num);
    void onEffectChanged(int num);
};

#endif // MAINWINDOW_H
