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

#include "led.h"
#include "../error/error.h"

#include <avr/io.h>

/*

    Initialize the led (pin refers to the digital pins in the arduino board)

 */

Led::Led (int pin)
{
    //check if pin is within the valid range
if (pin >= 0 && pin <= 13)
    {
        //PORTD (digital pins 0 to 7)
    if (pin < 8)
        {
            //save the port, so that we can refer to it later
        port_obj = &PORTD;
        ddr_obj = &DDRD;
        }

        //PORTB (digital pins 8 to 13 - PB0 to PB5)
    else
        {
            //so that for example, digital pin 8 corresponds to PB0
        pin -= 8;

        port_obj = &PORTB;
        ddr_obj = &DDRB;
        }


                //set the bit chosen - output (put a 1)
    *ddr_obj |= (1 << pin);

    pin_obj = pin;
    }

else
    {
        //an error, wrong pin
    Error::wrongPin = true;
    }
}



/*

    Same as above, but you specify the port and pin
        port : 'B', 'C', 'D'
        pin  : from 0 to 7

 */

Led::Led (char port, int pin)
{
if (pin < 0 || pin > 7)
    {
        //error (these are 8 bit ports)
    Error::wrongPin = true;
    }

else
    {
    if (port == 'B' || port == 'b')
        {
        DDRB |= (1 << pin);

        ddr_obj = &DDRB;
        port_obj = &PORTB;

        pin_obj = pin;
        }

    else if (port == 'C' || port == 'c')
        {
        DDRC |= (1 << pin);

        ddr_obj = &PORTC;
        port_obj = &PORTC;

        pin_obj = pin;
        }

    else if (port == 'D' || port == 'd')
        {
        DDRD |= (1 << pin);

        ddr_obj = &PORTD;
        port_obj = &PORTD;

        pin_obj = pin;
        }

    else
        {
            //error, wrong port
        Error::wrongPort = true;
        }
    }
}



    //configure the pin as input
Led::~Led()
{
*ddr_obj &= ~(1 << pin_obj);
}



void Led::turnOn()
{
*port_obj |= (1 << pin_obj);
}




void Led::turnOff()
{
*port_obj &= ~(1 << pin_obj);
}



void Led::toogle()
{
*port_obj ^= (1 << pin_obj);
}
