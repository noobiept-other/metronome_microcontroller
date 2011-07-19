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

#ifndef MOMENTARY_SWITCH_GUARD
#define MOMENTARY_SWITCH_GUARD


#include <inttypes.h>

/*
    To tell if there weren't any errors (if needed), check for Error::wrongPin and Error::wrongPort
 */

class MomentarySwitch
{
    public:

        /*
            Arguments:
                pin           : the digital pin number in the arduino board
                isActiveAtOne : if when we press the switch, we'll see a one or a zero
                isPullupOn    : if we turn the internal pullup on (default value is without pullups)
         */

        MomentarySwitch (int pin, bool isActiveAtOne, bool isPullupOn = false);


        /*
            Arguments:
                port          : which port the switch is connected to ('C' for port C, 'D' for port D, ...)
                pin           : the number representing the pin of that port (from 0 to 7  - if available)
                isActiveAtOne : (same as above)
                isPullupOn    : (same as above)
         */

        MomentarySwitch (char port, int pin, bool isActiveAtOne, bool isPullupOn = false);

        /*
            Tells if the switch is been pressed
         */

        bool isPressed();


    private:

        int pinNumber_obj;

            //the registers of the port where this switch is
        volatile uint8_t *port_obj;
        volatile uint8_t *pin_obj;
        volatile uint8_t *ddr_obj;

            //if when we press the switch, we will read a one or a zero
            //(if it is active at one, or at zero)
        bool isActiveAtOne_obj;
};



#endif //MOMENTARY_SWITCH_GUARD
