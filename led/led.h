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

#ifndef LED_GUARD
#define LED_GUARD

#include <avr/io.h>
#include <inttypes.h>

/*
    If you need to know if this worked, check for Error::wrongPin or/and Error::wrongPort
 */

class Led
{
    public:

            //pin is the digital pin number in the arduino
        Led (int pin);

            //where port is 'B', 'C', .. (the ports of the microcontroller)
            //and pin is the bit of that port (from 0 to 7)
        Led (char port, int pin);

        ~Led();

        void turnOn();
        void turnOff();
        void toogle();

    private:

        int pin_obj;
        volatile uint8_t *port_obj;
        volatile uint8_t *ddr_obj;
};



#endif //LED_GUARD
