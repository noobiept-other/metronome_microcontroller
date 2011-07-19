//avrdude -p m328p -c arduino -P /dev/ttyACM0 -U flash:w:metronome_controller.elf.hex

#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

#include "./sound/sound.h"
#include "./tempo/tempo.h"
#include "PCD8544_lib/PCD8544.h"
#include "./led/led.h"
#include "./momentary_switch/momentary_switch.h"
#include "./exclusive_counter/exclusive_counter.h"


/*
    variables that are going to be used in the interruption functions

    it would be nice if they weren't global variables
    still trying to come up with a nicer way to do this
 */

    //LED -> digital pin 8 (PB0)
Led led(8);

Sound sound (4);





    //functions that are called in the interruptions
    //this is called first, so we turn on the led/sound
void firstCompare()
{
    //light the led
led.turnOn();

    //turn on the sound
sound.turnOn();
}

    //this is called after (the duration is defined in the 'tempo' object)
    //we turn off the led/sound
void secondCompare()
{
    //turn off the led
led.turnOff();

    //turn off the sound
sound.turnOff();
}





int main(void)
{
MomentarySwitch increaseTempo (10, false, true);

MomentarySwitch decreaseTempo (12, false, true);


MomentarySwitch changeStrongBeat ('c', 0, false, true);


ExclusiveCounter exclusiveCounter (3);


    //start with 100 bpm, and 20ms of duration
Tempo tempo(100, 20);
tempo.setInterrupts(firstCompare, secondCompare);


    //set the global interrupt bit, to allow interruptions to occur
SREG |= 0x80;


    //setup the lcd
PCD8544 lcd;

lcd.begin(84, 48);


    //position on the first column, first line
lcd.setCursor(0, 0);

    //some random message
lcd.print("1, 2, 3, 4..!");


const int lineForBpm = 1;   //second line
lcd.printInt(lineForBpm, tempo.getBpm());   //uses the whole line


    //in milliseconds, the delay after we press a switch
const int normalDelay = 150;

    //the delay when we're increasing/decreasing faster the tempo
const int fastDelay = 50;

while(1)
    {
    /*
        changes the sequence of strong/normal beats - for example:
            with 1 -> 1.. 1.. 1.. 1..
            with 2 -> 1!.. 2.. 1!.. 2..
            with 3 -> 1!.. 2.. 3.. 1!.. 2.. 3..
            with 4 -> 1!.. 2.. 3.. 4.. 1!.. 2.. 3..
     */

    if (changeStrongBeat.isPressed() == true)
        {
        _delay_ms(20);

            //confirm it
        if (changeStrongBeat.isPressed() == true)
            {
            sound.nextStrongBeat();

            _delay_ms(normalDelay);
            }
        }


    else if (increaseTempo.isPressed() == true)
        {
            //give it some time for the switch to stabilize
        _delay_ms(10);

            //if it's still set, then we consider a valid press
        if (increaseTempo.isPressed() == true)
            {
                //sometimes when changing the tempo, you get the sound going 'piiiii'
                //so lets turn if off first
                //we could do the same for the led, but it isn't has annoying :)
            if (sound.isPlaying() == true)
                {
                sound.turnOff();
                }

                //increase the tempo
            tempo++;

                //update the lcd
            lcd.printInt(lineForBpm, tempo.getBpm());

                 //1 -> increaseTempo identifier
                 //if we reached the count limit, we increase the tempo faster
            if (exclusiveCounter.count (1) == true)
                {
                while (increaseTempo.isPressed() == true)
                    {
                    _delay_ms(fastDelay);
                    tempo++;

                        //update the lcd
                    lcd.printInt(lineForBpm, tempo.getBpm());
                    }
                }

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

                //update the lcd
            lcd.printInt(lineForBpm, tempo.getBpm());

                 //-1 -> decreaseTempo identifier
                 //if we reached the count limit, we decrease the tempo faster
            if (exclusiveCounter.count (-1) == true)
                {
                while (decreaseTempo.isPressed() == true)
                    {
                    _delay_ms(fastDelay);
                    tempo--;

                        //update the lcd
                    lcd.printInt(lineForBpm, tempo.getBpm());
                    }
                }


            _delay_ms(normalDelay);
            }
        }

    else
        {
            //if there's no switch been press, lets cancel the counter
            //(otherwise you could press the same switch with some interval between the press
            //   and after whatever times you defined, it would go for the fast speed
            //we only want that to happen when you keep the switch been pressed)
        exclusiveCounter.count (0);
        }
    }


return 0;
}
