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

#include "fftprocessor.h"

//#include "audioprocessor_io_copy.h"
//#include "audioprocessor_noise.h"
//#include "audioprocessor_sine.h"
#include "audioprocessor_fft.h"
#include <qwt_scale_engine.h>
#include <qwt_plot_histogram.h>

#include "static_settings.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  audioProcessor *ap;

private:
  Ui::MainWindowClass *ui;

  QwtPlot *mainPlot;
  QwtPlotCurve *mainCurve;
  QwtPlotCurve *subCurve;
  QwtPlotZoomer *mainCurveZoomer;
  QwtPlotHistogram *histogram;

  double *mainCurveXData;
  double *mainCurveYData;
  double *subCurveYData;

  void initPlot(QwtPlot* plot, const char* xTitle, const char* yTitle, int xmin, int xmax, int ymin, int ymax);

public slots:
  void onSoundcardSettingsAction();
  void onContinuousRunPushButton();
  void onStopRunPushButton();
  void onFrameProcessed(fftProcessor *fft);
};

#endif // MAINWINDOW_H
