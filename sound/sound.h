#ifndef SOUND_GUARD
#define SOUND_GUARD


class Sound
{
    public:

        /*
            uses timer/counter 2 in PWM mode (digital pin 11 - PB3/OC2A)

            Arguments:
                strongBeat : if there's a strong beat, and from how many beats if should occur
                             1 -> no strong beat
                             2 -> 1 strong beat... 1 normal beat... 1 strong beat...
                             3 -> 1 strong beat... 2 normal beats.. 1 strong beat...
                                (and so on..)
         */

        Sound(unsigned int strongBeat = 1);

        ~Sound();

        void turnOn();
        void turnOff();

            //true for when its playing, false for when its not
        bool isPlaying();

        unsigned int getStrongBeat() const;
        void setStrongBeat(unsigned int strongBeat);

            //goes 1, 2, 3, 4, 1, 2, ...
        void nextStrongBeat();

    private:

        unsigned int strongBeat_obj;
        unsigned int countBeats_obj;
        bool isPlaying_obj;
};




#endif //SOUND_GUARD
