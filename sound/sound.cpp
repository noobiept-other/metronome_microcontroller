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

#include "sound.h"

#include <avr/interrupt.h>



Sound::Sound (unsigned int strongBeat)

    : strongBeat_obj (strongBeat),
      countBeats_obj (0),
      isPlaying_obj (false)

{
    //as output PB3
DDRB |= (1 << DDB3);

    //50% duty cycle... +-
OCR2A = 127;


    //fast PWM - Clear OC2A on Compare Match, set OC2A at BOTTOM, (non-inverting mode)
    //page 159 of datasheet
TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);

    //no prescaler (no sound)
    //stoped -> xxxxx000
TCCR2B = 0b00000000;

TIMSK2 = 0; //no interrupts
}



    //reset the configurations
Sound::~Sound()
{
TCCR2A = 0;
TCCR2B = 0;
TIMSK2 = 0;

OCR2A = 0;

    //configure the pin as input (its safer)
DDRB &= ~(1 << DDB3);
}


void Sound::turnOn ()
{
/*
    start the sound (setting up a prescaler)
        (see pag. 163 of atmega328p datasheet)

    f_pwm = f_osc / (prescaler * 256)
    with freqOsc = 16 MHz and prescaler:

        8    -> we get around 7812 Hz
        32   -> 1953 Hz
        64   ->  976 Hz
        128  ->  488 Hz
        256  ->  244 Hz
        1024 ->   61 Hz

    I'll choose the 976 Hz as normal beat, and 1953 Hz as strong beat.
    prescaler:
        32  - xxxxx011 (strong beat)
        64  - xxxxx100 (normal beat)
*/

    //there's no strong beat
if (strongBeat_obj < 2)
    {
    TCCR2B |= (1 << CS22);
    TCCR2B &= ~((1 << CS21) | (1 << CS20));

    countBeats_obj = 0;
    }

else
    {
    countBeats_obj++;

        //the first beat (which is the strong one)
    if (countBeats_obj == 1)
        {
            //select the 32 prescaler
        TCCR2B |= (1 << CS21) | (1 << CS20);
        TCCR2B &= ~(1 << CS22);
        }

    else
        {
            //select the 64 prescaler
        TCCR2B |= (1 << CS22);
        TCCR2B &= ~((1 << CS21) | (1 << CS20));


        if (countBeats_obj >= strongBeat_obj)
            {
            countBeats_obj = 0;
            }
        }
    }

isPlaying_obj = true;
}



void Sound::turnOff ()
{
    //turn off the sound (no clock source, timer/counter stopped)
    //xxxxx000
TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));

isPlaying_obj = false;
}





bool Sound::isPlaying()
{
return isPlaying_obj;
}



void Sound::setStrongBeat(unsigned int strongBeat)
{
strongBeat_obj = strongBeat;
}



void Sound::nextStrongBeat()
{
strongBeat_obj++;

if (strongBeat_obj > 4)
    {
    strongBeat_obj = 1;
    }
}


unsigned int Sound::getStrongBeat() const
{
return strongBeat_obj;
}
