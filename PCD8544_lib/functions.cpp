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

#include "functions.h"
#include "PCD8544.h"
#include "../error/error.h"

/*
    Writes a string
*/

void PCD8544::print (const char* str)
{
while (*str != '\0')
    {
    write(*str);
    str++;
    }

}


/*
    Writes an int on a line (0 - first line, 1 - second line...)
*/

void PCD8544::printInt (const int line, const int value)
{
char buffer[20];

    //first column, second line
setCursor(0, line);

sprintf(buffer, "%d", value);

    //clear the previous stuff
clearLine();
print(buffer);
}




void shiftOut(int dataPin, int clockPin, int bitOrder, int val)
{
	int i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
}

/*

http://www.arduino.cc/en/Hacking/PinMapping168

    Digital pins 0 to 7 -> PORTD
        (PD0 -> digital pin 0, PD1 -> digital pin 1, etc)

    Digital pins 8 to 13 -> PORTB
        (PB0 -> digital pin 8, PB1 -> digital pin 9, etc)
        (from PB0 to PB5. PB6 and PB7 are used for the crystal)

    Analog pins 0 to 5 -> PORTC
        (PC0 -> analog pin 0, PC1 -> analog pin 1, etc)
        (from PC0 to PC5)


 */

    //only for digital pins (0 to 13)
    //only thought out for the arduino uno (don't know about the others)
void pinMode (unsigned char pin, unsigned char value)
{
    //check if parameters have acceptable values
if (pin < 0 || pin > 13)
    {
    Error::wrongPin = true;

    return;
    }

if (value < 0 || value > 1)
    {
    Error::wrongInit = true;

    return;
    }


    //PORTD (digital pins 0 to 7)
if (pin < 8)
    {
        //set the bit chosen (put a 1)
    if (value == HIGH)
        {
        DDRD |= (1 << pin);
        }

        //clear the bit chosen (put a 0)
    else
        {
        DDRD &= ~(1 << pin);
        }
    }

    //PORTB (digital pins 8 to 13 - PB0 to PB5)
else
    {
        //set the bit chosen (put a 1)
    if (value == HIGH)
        {
        DDRB |= (1 << pin);
        }

        //clear the bit chosen (put a 0)
    else
        {
        DDRB &= ~(1 << pin);
        }
    }
}


void digitalWrite (unsigned char pin, unsigned char value)
{
    //check if parameters have acceptable values
if (pin < 0 || pin > 13)
    {
    Error::wrongPin = true;

    return;
    }

if (value < 0 || value > 1)
    {
    Error::wrongInit = true;

    return;
    }


    //PORTD (digital pins 0 to 7)
if (pin < 8)
    {
        //set the bit chosen (put a 1)
    if (value == HIGH)
        {
        PORTD |= (1 << pin);
        }

        //clear the bit chosen (put a 0)
    else
        {
        PORTD &= ~(1 << pin);
        }
    }

    //PORTB (digital pins 8 to 13 - PB0 to PB5)
else
    {
        //set the bit chosen (put a 1)
    if (value == HIGH)
        {
        PORTB |= (1 << pin);
        }

        //clear the bit chosen (put a 0)
    else
        {
        PORTB &= ~(1 << pin);
        }
    }
}
