/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#include "fftprocessor.h"
#include <math.h>

fftProcessor::fftProcessor(int fftSize)
{
  this->fftSize = fftSize;

  outArraySize = fftSize/2+1;

  fftIn = (double*) fftw_malloc(sizeof(double) * fftSize);
  fftOut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * outArraySize);
  fftOutAbs = (double*) fftw_malloc(sizeof(double) * outArraySize);

  fftwPlan = fftw_plan_dft_r2c_1d(fftSize, fftIn, fftOut, FFTW_ESTIMATE);
//	fftwPlan = fftw_plan_dft_r2c_1d(fftSize, fftIn, fftOut, FFTW_MEASURE);
}

fftProcessor::~fftProcessor()
{
  fftw_free(fftIn);
  fftw_free(fftOut);
  fftw_free(fftOutAbs);
}

void fftProcessor::calcAbsResponse()
{
    int n=fftSize/2+1;
    for(int i=0; i < n; i++)
        fftOutAbs[i] = sqrt(fftOut[i][0]*fftOut[i][0] + fftOut[i][1]*fftOut[i][1]);
}

void fftProcessor::execute()
{
    fftw_execute(fftwPlan);
    calcAbsResponse();
}
