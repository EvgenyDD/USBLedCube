/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "audioprocessor_freq_detection.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>

using namespace std;

audioProcessor::audioProcessor(int fftSize)
{
  ::paWrapper();
  fft = new fftProcessor(fftSize);
  noOfFramesPerPlot=3;  //plot each (noOfFramesPerPlot+1)'th frame
  framesPerPlotCnt=noOfFramesPerPlot; //start with plotting the 1st frame
  frequency = 1000;
}

audioProcessor::~audioProcessor()
{
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
    unsigned int i,n;
    (void) inputBuffer; // Prevent unused variable warning.
    (void) statusFlags; // Prevent unused variable warning.
    (void) timeInfo; // Prevent unused variable warning.

//    if(stopAudioProcessing) return paComplete;

  double scale_fact=2*M_PI/(framesPerBuffer-1);  //to make it a little bit faster


    assert(fft->fftSize >= framesPerBuffer);
    for( i=0; i<framesPerBuffer; i++ )
    {
//        *out++ = 0.5*(((float) rand())/((float) RAND_MAX)-0.5)*2.0;  /* left */
//       out[i] = in[i];  /* left */
      phase += 2.0 * 3.14 * frequency / sampleRate;
//      phase += 2.0 * 3.14 * 1000.0 / sampleRate;
      out[i] = 0.5*sin(phase);
      fft->fftIn[i] = (0.54-(0.46*cos(scale_fact*i))) * in[i];
//      fft->fftIn[i] = 0.5*(((float) rand())/((float) RAND_MAX)-0.5)*2.0;
//      fft->fftIn[i] = sin(phase);
//      fft->fftIn[i] = (0.54-(0.46*cos(scale_fact*i))) * sin(phase);
    }

  //zero padding:
  for(i=framesPerBuffer; i<fft->fftSize; i++)
  {
    fft->fftIn[i] = 0.0;
  }

  fft->execute();

  //search maximum:
  n=fft->fftSize/2+1;
  maxValue = 1E-300;
  maxIndex = 0;
  for(i=0; i < n; i++)
  {
    if(fft->fftOutAbs[i] > maxValue)
    {
      maxValue = fft->fftOutAbs[i];
      maxIndex = i;
    }
  }
  if(maxValue > 10)
    frequency = ((double) maxIndex)/((double) fft->fftSize) * sampleRate;
  else
    frequency = 0;
//  printf("%f\n",frequency); flush(cout);
//  printf("%f\n",maxValue); flush(cout);

  if(framesPerPlotCnt == noOfFramesPerPlot)
  {
    emit frameProcessed(fft);
    framesPerPlotCnt = 0;
  }
  else
    framesPerPlotCnt++;

//  printf("*"); flush(cout);
//  return -1; //!!!
  return 0;
}
