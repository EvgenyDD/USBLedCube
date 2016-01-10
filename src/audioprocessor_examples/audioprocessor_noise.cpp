/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "audioprocessor_noise.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>

using namespace std;

audioProcessor::audioProcessor(int fftSize)
{
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
    out[i] = 0.5*(((float) rand())/((float) RAND_MAX)-0.5)*2.0; //set to 0.5 of max. output amplitude
  }

  //  printf("*"); flush(cout);
  return 0;
}
