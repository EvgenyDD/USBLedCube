/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
//#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
#include <QDebug>

#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
                QwtPlot plot;
                plot.setTitle( "Plot Demo" );
                plot.setCanvasBackground( Qt::white );
                plot.setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
                plot.insertLegend( new QwtLegend() );

                QwtPlotGrid *grid = new QwtPlotGrid();
                grid->attach( &plot );

                QwtPlotCurve *curve = new QwtPlotCurve();
                curve->setTitle( "Some Points" );
                curve->setPen( QPen( Qt::blue, 4 ) ),
                curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

                QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
                   QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
                curve->setSymbol( symbol );

                QPolygonF points;
                points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
                   << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
                   << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
                curve->setSamples( points );

                curve->attach( &plot );

                plot.resize( 600, 400 );
                plot.show();
#endif

    MainWindow w;
    w.show();

    int ret = a.exec();
    qDebug() << "Programm terminated !";

    return ret;
}


//#define Utf QTextCodec::codecForLocale()->toUnicode
//   qDebug() << Utf(paw->getDeviceName(i)) <<Utf("азазаза-Фэйл(");
