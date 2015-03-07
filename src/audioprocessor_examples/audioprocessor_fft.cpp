/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "audioprocessor_fft.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>
#include <QDebug>
#include <stdint.h>

using namespace std;

audioProcessor::audioProcessor(int fftSize)
{
    fft = new fftProcessor(fftSize);
    noOfFramesPerPlot = 3;  //plot each (noOfFramesPerPlot+1)'th frame
    framesPerPlotCnt = noOfFramesPerPlot; //start with plotting the 1st frame
}

audioProcessor::~audioProcessor()
{
    qDebug() << "audioProcessor::~audioProcessor()";
    delete fft;
}

int audioProcessor::processingCallback(const void *inputBuffer,
                                        void *outputBuffer,
                                        unsigned long framesPerBuffer,
                                        const PaStreamCallbackTimeInfo* timeInfo,
                                        PaStreamCallbackFlags statusFlags)
{
    float *out = (float*) outputBuffer;
    float *in = (float*) inputBuffer;
    unsigned int i;

    (void) statusFlags; // Prevent unused variable warning.
    (void) timeInfo; // Prevent unused variable warning.

    double scale_fact=2*M_PI/(framesPerBuffer-1);  //to make it a little bit faster

    //qDebug() << "Frames/buffer : " << framesPerBuffer;


    unsigned int fftSize=fft->getfftSize();

    assert(fftSize >= framesPerBuffer);

    for( i=0; i<framesPerBuffer; i++ )
    {
        out[i] = 0.0; //nothing to output
        fft->fftIn[i] = (0.54-(0.46*cos(scale_fact*i))) * in[i]; //apply hamming window to input
    }

    //qDebug() << "Buf 0 : " << (float)in[0] << " and conv: " << fft->fftIn[0];

    //zero padding if fftSize>framesPerBuffer:
    for(i=framesPerBuffer; i<fftSize; i++)
        fft->fftIn[i] = 0.0;

    fft->execute();

    //fire signal when its time to plot
    if(framesPerPlotCnt == noOfFramesPerPlot)
    {
        emit frameProcessed(fft);
        framesPerPlotCnt = 0;
    }
    else
        framesPerPlotCnt++;

    static uint8_t f=0;
    //qDebug() << "*" << f++;
    return 0;
}
