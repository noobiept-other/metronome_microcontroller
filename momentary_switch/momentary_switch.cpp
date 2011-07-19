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

#include "momentary_switch.h"
#include "../error/error.h"
#include <avr/io.h>


MomentarySwitch::MomentarySwitch (int pin, bool isActiveAtOne, bool isPullupOn)

    : isActiveAtOne_obj (isActiveAtOne)

{
    //check if pin is within the valid range
if (pin < 0 || pin > 13)
    {
        //error, there's only 13 digital pins on arduino uno
    Error::wrongPin = true;
    }

else
    {
        //PORTD (digital pins 0 to 7)
    if (pin < 8)
        {
            //save the port registers, so that we can refer to it later
        ddr_obj = &DDRD;
        port_obj = &PORTD;
        pin_obj = &PIND;
        }

        //PORTB (digital pins 8 to 13 - PB0 to PB5)
    else
        {
            //so that for example, digital pin 8 corresponds to PB0
        pin -= 8;

        ddr_obj = &DDRB;
        port_obj = &PORTB;
        pin_obj = &PINB;
        }


        //clear the bit chosen - so that it works as input (put a 0)
    *ddr_obj &= ~(1 << pin);

        //we can activate an internal pullup resistor on the pin
    if (isPullupOn == true)
        {
            //when we define as input (in the DDRx), writing a one in the PORTx activates the internal pullups
        *port_obj |= (1 << pin);
        }

    pinNumber_obj = pin;
    }
}




MomentarySwitch::MomentarySwitch (char port, int pin, bool isActiveAtOne, bool isPullupOn)

    : pinNumber_obj (pin),
    isActiveAtOne_obj (isActiveAtOne)


{
if (port == 'B' || port == 'b')
    {
    port_obj = &PORTB;
    pin_obj = &PINB;
    ddr_obj = &DDRB;
    }

else if (port == 'C' || port == 'c')
    {
    port_obj = &PORTC;
    pin_obj = &PINC;
    ddr_obj = &DDRC;
    }

else if (port == 'D' || port == 'd')
    {
    port_obj = &PORTD;
    pin_obj = &PIND;
    ddr_obj = &DDRD;
    }

else
    {
        //an error.. atmega328p only has port B, C and D
    Error::wrongPort = true;
    }



if (pin < 0 || pin > 7)
    {
        //another error, ports are 8 bits, so only from 0 to 7
    Error::wrongPin = true;
    }

else
    {
        //clear the bit chosen - so that it works as input (put a 0)
    *ddr_obj &= ~(1 << pin);

        //we can activate an internal pullup resistor on the pin
    if (isPullupOn == true)
        {
            //when we define as input (in the DDRx), writing a one in the PORTx activates the internal pullups
        *port_obj |= (1 << pin);
        }
    }
}




bool MomentarySwitch::isPressed ()
{
if (isActiveAtOne_obj == true)
    {
        //if the switch is been pressed, it'll have a one
        //so, an AND operation between two 1's is something different than zero
    if ((*pin_obj & (1 << pinNumber_obj)) != 0)
        {
        return true;
        }

    return false;
    }

else
    {
        //here, we just reverse the returns
    if ((*pin_obj & (1 << pinNumber_obj)) != 0)
        {
        return false;
        }

    return true;
    }
}
