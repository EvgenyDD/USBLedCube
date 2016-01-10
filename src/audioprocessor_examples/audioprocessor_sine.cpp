/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "audioprocessor_sine.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>

using namespace std;

audioProcessor::audioProcessor(int fftSize)
{
  printf("audioProcessor::audioProcessor()\n"); flush(cout);
  //paWrapper::paWrapper();
  //initAudio();
  frequency = 1000; //freq. of sine
  (void) fftSize; // Prevent unused variable warning.
}

audioProcessor::~audioProcessor()
{
}

int audioProcessor::processingCallback(const void *inputBuffer,
                                        void *outputBuffer,
                                        unsigned long framesPerBuffer,
                                        const PaStreamCallbackTimeInfo* timeInfo,
                                        PaStreamCallbackFlags statusFlags)
{
  float *out = (float*) outputBuffer;
  unsigned int i;
  (void) inputBuffer; // Prevent unused variable warning.
  (void) statusFlags; // Prevent unused variable warning.
  (void) timeInfo; // Prevent unused variable warning.

  for( i=0; i<framesPerBuffer; i++ )
  {
    phase += 2.0 * 3.14 * frequency / sampleRate;
    out[i] = 0.5*sin(phase);
  }

    //  printf("*"); flush(cout);
  return 0;
}
