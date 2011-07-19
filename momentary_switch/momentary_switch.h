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
