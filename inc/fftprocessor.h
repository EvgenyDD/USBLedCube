/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#ifndef FFTPROCESSOR_H
#define FFTPROCESSOR_H
#include "fftw3.h"

#define M_TWOPI 6.28318530717958647692f

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795f
#endif

class fftProcessor
{
public:
  fftProcessor(int fftSize);
  ~fftProcessor();
  //inline void execute() { fftw_execute(fftwPlan); calcAbsResponse(); }
  inline int getfftSize() { return fftSize; }

  double* fftIn;
  double* fftOutAbs;
  fftw_complex* fftOut;

  void execute();

protected:
  unsigned int fftSize;
  int outArraySize;
  fftw_plan fftwPlan;

  void calcAbsResponse();
};

#endif // FFTPROCESSOR_H
