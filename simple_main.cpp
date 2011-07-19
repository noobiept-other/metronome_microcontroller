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


//avrdude -p m328p -c arduino -P /dev/ttyACM0 -U flash:w:metronome_controller.elf.hex

#include <avr/interrupt.h>
#include <util/delay.h>

#include "./sound/sound.h"
#include "./tempo/tempo.h"
#include "./momentary_switch/momentary_switch.h"



/*
    variables that are going to be used in the interruption functions

    it would be nice if they weren't global variables
    still trying to come up with a nicer way to do this
 */

Sound sound;




    //functions that are called in the interruptions
    //this is called first, so we turn on the led/sound
void firstCompare()
{
    //turn on the sound
sound.turnOn();
}

    //this is called after (the duration is defined in the 'tempo' object)
    //we turn off the led/sound
void secondCompare()
{
    //turn off the sound
sound.turnOff();
}





int main(void)
{
MomentarySwitch increaseTempo (10, false, true);

MomentarySwitch decreaseTempo (12, false, true);



    //start with 100 bpm, and 20ms of duration
Tempo tempo(100, 20);
tempo.setInterrupts(firstCompare, secondCompare);


    //set the global interrupt bit, to allow interruptions to occur
SREG |= 0x80;


    //in milliseconds, the delay after we press a switch
const int normalDelay = 150;

while(1)
    {
    if (increaseTempo.isPressed() == true)
        {
            //give it some time for the switch to stabilize
        _delay_ms(10);

            //if it's still set, then we consider a valid press
        if (increaseTempo.isPressed() == true)
            {
                //sometimes when changing the tempo, you get the sound going 'piiiii'
                //so lets turn if off first
            if (sound.isPlaying() == true)
                {
                sound.turnOff();
                }

                //increase the tempo
            tempo++;


            _delay_ms(normalDelay);
            }
        }

    else if (decreaseTempo.isPressed() == true)
        {
        _delay_ms(10);

        if (decreaseTempo.isPressed() == true)
            {
            if (sound.isPlaying() == true)
                {
                sound.turnOff();
                }

                //decrease the tempo
            tempo--;


            _delay_ms(normalDelay);
            }
        }
    }


return 0;
}
