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

#include "tempo.h"
#include <avr/interrupt.h>


namespace Tempo_interrupts
{
    //function pointers to the functions that are going to be executed during the interruptions
void (*timer1_compA)();
void (*timer1_compB)();
}




Tempo::Tempo(unsigned int bpm, unsigned int duration, long int freqOsc)

    : freqOsc_obj (freqOsc),
      duration_obj (duration),
      bpm_obj (bpm),
      prescaler_obj (0)

{
    //timer 1 (16 bits)
    //mode 4 (CTC)
    //Top: 0CR1A (see page 137 of the datasheet)
TCCR1A = 0;

TCCR1B = (1 << WGM12);

TCCR1C = 0;


    //allow an interruption on compare with OCR1A and OCR1B
TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);


setBpm(bpm);
}



Tempo::~Tempo()
{
TCCR1A = 0;
TCCR1B = 0;
TCCR1C = 0;

TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));
}


/*
    Timer/Counter 1 (16 bit)

    For timing the beats per minute

 */

void Tempo::setBpm (int bpm)
{
bpm_obj = bpm;

    /*
        we have to use the 1024 prescaler (page 138 of datasheet)
        for better precision, we use different prescalers

        f_timer = f_clock / (prescaler * (1 + OCR1A))

        So using the maximum value for OCR1A (2^16 - 1 = 65535) we get:
            with prescaler of 64 -> 3.81 Hz  (228 bpm)
            with prescaler of 256 -> 0.95 Hz (57 bpm)
            with prescaler of 1024 -> 0.24 Hz (14 bpm)

        These values are the minimum possible bpm for that prescaler.

        We'll use the prescaler of 1024 for bpm lower than 58,
            256 for bpm lower than 228 and 64 for above that (although thats probably too fast, no?)
     */

     //go for the 1024
if (bpm < 57)
    {
    if (prescaler_obj != 1024)
        {
            //the last 3 bits define the prescaler
            //xxxxx101 - 1024 (see pag. 138 of datasheet)
        TCCR1B |= (1 << CS12) | (1 << CS10);

        TCCR1B &= ~(1 << CS11);

        prescaler_obj = 1024;
        }
    }

    //we use the 256 prescaler
else if (bpm < 228)
    {
    if (prescaler_obj != 256)
        {
            //xxxxx100 - 256
        TCCR1B |= (1 << CS12);
        TCCR1B &= ~((1 << CS11) | (1 << CS10));

        prescaler_obj = 256;
        }
    }

    //for bpm >= 228, prescaler of 64
else
    {
    if (prescaler_obj != 64)
        {
            //xxxxx011 - 64
        TCCR1B |= (1 << CS11) | (1 << CS10);
        TCCR1B &= ~(1 << CS12);

        prescaler_obj = 64;
        }
    }


double frequency = bpm / 60.0;

    //f_timer = f_clock / (prescaler * (1 + OCR1A))
double finalValue = freqOsc_obj / (frequency * prescaler_obj) - 1;


    //we do the calculation in double, and then we convert to int (implicit conversion)
unsigned int value = finalValue;


    //ajust to the closest int value
if ((finalValue - value) >= 0.5)
    {
    value++;
    }



    //reset of the counter, so that when setting for a value of OCR1A lower
    //than what is on TCNT1, we don't have to wait for it to overflows (it isn't that much of a problem though)
TCNT1 = 0;

OCR1A = value;  //OCR1A is updated immediately



    //now lets deal with the duration of the sound
    //we'll set OCR1B to a value lower than OCR1A, and in the interruption functions,
    //the COMPB starts the sound and the COMPA stops it

    //interval (in ms) = (prescaler * (1 + numberToCount)) / freqOsc
    //numberToCount = interval * freqOsc / prescaler - 1
double inSeconds = duration_obj / 1000.0;

unsigned int numberToCount = inSeconds * freqOsc_obj / prescaler_obj - 1;

    //the sound starts with OCR1B, and its turn off when it reaches OCR1A
OCR1B = OCR1A - numberToCount;
}





void Tempo::setInterrupts (void (*firstCompare)(), void (*secondCompare)())
{
Tempo_interrupts::timer1_compB = firstCompare;
Tempo_interrupts::timer1_compA = secondCompare;
}


    //interrupt function triggered by the comparation of OCR1B and TCNT1
ISR (TIMER1_COMPB_vect)
{
Tempo_interrupts::timer1_compB();
}



    //interrupt function triggered by the comparation of OCR1A and TCNT1
ISR (TIMER1_COMPA_vect)
{
Tempo_interrupts::timer1_compA();
}




int Tempo::getBpm() const
{
return bpm_obj;
}



void Tempo::operator ++ (int a)
{
setBpm(bpm_obj + 1);
}


void Tempo::operator -- (int a)
{
setBpm(bpm_obj - 1);
}
