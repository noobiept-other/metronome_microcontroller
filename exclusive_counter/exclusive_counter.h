#ifndef EXCLUSIVE_COUNTER_GUARD
#define EXCLUSIVE_COUNTER_GUARD

/*
    Counts a number of consecutive occurrences from the same identifier
    If there's another identifier counting, the counter is cleared

    If it reaches the countLimit, the counter is cleared and count() returns true
    otherwise it returns always false

    countLimit has to be > 1
        check for Error::wrongInit if you need to check this

 */

class ExclusiveCounter
{
    public:

        ExclusiveCounter (unsigned int countLimit);


        bool count (int identifier);


    private:

        unsigned int counter_obj;
        unsigned int countLimit_obj;

        int previousIdentifier_obj;

};



#endif //EXCLUSIVE_COUNTER_GUARD
