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
