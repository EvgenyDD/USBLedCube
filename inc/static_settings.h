/*
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
*/
#ifndef STATIC_SETTINGS_H
#define STATIC_SETTINGS_H

#define NO_OF_FRAME_LENGTHS 6
#define START_FRAME_LENGTH 128
#define DEFAULT_FRAME_LENGTH 256

//DEFAULT_FFT_SIZE must be greater or equal to DEFAULT_FRAME_LENGTH
//As the FFT size can not be adjusted at the moment, set FFT length to a maximum:
#define DEFAULT_FFT_SIZE START_FRAME_LENGTH*pow(2,NO_OF_FRAME_LENGTHS)

#endif // STATIC_SETTINGS_H
