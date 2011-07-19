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

#ifndef TEMPO_GUARD
#define TEMPO_GUARD


/*

    Uses timer/counter 1 (16 bits)

    Sets an tempo with two interrupts, one to start the sound/led (whatever) and the other
    to stop it (for more info check the tempo.cpp file)

 */

class Tempo
{
    public:

        /*
            bpm      : refers to the interval between the beats
            duration : refers to the duration of the sound/led - whatever is defined
                       basically, the time between the two interruptions
            freqOsc  : the frequency of the microcontroller (default: 16 MHz)
         */

        Tempo (unsigned int bpm, unsigned int duration, long int freqOsc = 16000000);

            //turns off the interruptions
        ~Tempo();

        void setBpm(int bpm);

        int getBpm () const;

        void operator ++ (int); //increase +1 the tempo
        void operator -- (int); //decrease -1 the tempo


            //sets the functions that are executed in the interruptions
        void setInterrupts (void (*firstCompare)(), void (*secondCompare)());


    private:

        const long int freqOsc_obj;

        int duration_obj;

        int bpm_obj;
        int prescaler_obj;
};



#endif //TEMPO_GUARD
