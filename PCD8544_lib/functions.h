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
