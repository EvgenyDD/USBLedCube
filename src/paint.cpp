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



void MainWindow::paintCubeVoxels(QPainter *painter)
{
    if(!CubeVisualizator->isVisible()) return;
    painter->translate(30, 100);
    uint *pCube = Cube->GetPCube();

    for(uint z=0; z<8; z++)
        for(uint y=0; y<8; y++)
            for(uint x=0; x<8; x++)
                if( (*(pCube + 8*(7-z) + (7-x))) & (1<<(7-y)) )
                {
                    QColor voxelColor((8-y)*x*1, (8-y)*x*2,
                                      160+y*5+(8-x)*5, 70+y*8+(8-x)*8);//(R,G,B,alpha)
                    //  painter.setBrush( Qt::transparent );
                    //else
                    painter->setBrush( voxelColor );

                    painter->setPen(Qt::NoPen);

                    // draw leds /
                    painter->drawEllipse( SP*x + y*SX -(CR+y/2)/2,
                                          SP*z + y*SY -x*SZ  -(CR+y/2)/2,
                                          CR+y/3+(8-x)/3,  CR+y/3+(8-x)/3  );
                }
}


void MainWindow::paintCubeBase(QPainter *painter)
{
    painter->translate(30, 100);

    for(uint z=0; z<8; z++)
        for(uint y=0; y<8; y++)
            for(uint x=0; x<8; x++)
            {
                QColor lineColor(100, 100, 100, y*4+(8-x)*4); //(R,G,B,alpha)
                painter->setPen( QPen( lineColor, 1 ,Qt::SolidLine) );
                //painter.setPen(Qt::DashLine);

                if(x != 7)
                    painter->drawLine( SP*x+y*SX, SP*z+y*SY-x*SZ,  SP*x+SP+y*SX,     SP*z+y*SY-(x+1)*SZ );
                if(z != 7)
                    painter->drawLine( SP*x+y*SX, SP*z+y*SY-x*SZ,  SP*x+y*SX,        SP*z+SP+y*SY-x*SZ );
                if(y != 7)
                    painter->drawLine( SP*x+y*SX, SP*z+y*SY-x*SZ,  SP*x+(y+1)*SX,    SP*z+(y+1)*SY-(x+0)*SZ );
            }
}



void MainWindow::cubeRePaint()
{
    CubeVisualizator->setPixmap(*cubeBase);
    QImage temp(cubeBase->toImage());
    QPainter painter(&temp);
    paintCubeVoxels(&painter);

    //Drawing buttons state ellipses
    /*for(int i=0; i<4; i++)
    {
        if((*pButtons) & (1<<i))
            painter->setBrush( Qt::blue );
        else
            painter->setBrush( Qt::transparent );
        painter->setPen(Qt::SolidLine);
        painter->drawEllipse(10+20*i,10,12,12);
    }*/

    CubeVisualizator->setPixmap(QPixmap::fromImage(temp));
}
