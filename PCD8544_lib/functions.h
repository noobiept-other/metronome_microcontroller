/*

	Copyright - 2011 - Pedro Ferreira

	This file is part of metronome_controller.

    metronome_controller is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    metronome_controller is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with metronome_controller.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef FUNCTIONS_GUARD
#define FUNCTIONS_GUARD

#include <avr/io.h>
#include <stdio.h>


/*
    Functions to make the PCD8544 library work without the arduino dependencies

    to check for errors: Error::wrongPin and Error::wrongInit
 */

void shiftOut(int dataPin, int clockPin, int bitOrder, int val);

void pinMode (unsigned char pin, unsigned char value);
void digitalWrite (unsigned char pin, unsigned char value);


#define LSBFIRST 0
#define MSBFIRST 1

#define OUTPUT 1
#define HIGH 1
#define LOW 0

#endif //FUNCTIONS_GUARD
