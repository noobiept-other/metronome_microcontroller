#include "exclusive_counter.h"
#include "../error/error.h"


ExclusiveCounter::ExclusiveCounter(unsigned int counterLimit)

    : counter_obj (0),
      countLimit_obj (counterLimit),
      previousIdentifier_obj (0)

{
if (counterLimit < 2)
    {
    Error::wrongInit = true;
    }
}




bool ExclusiveCounter::count (int identifier)
{
if (identifier == previousIdentifier_obj)
    {
    counter_obj++;

        //returning true tells us that the limit has been reached
    if (counter_obj == countLimit_obj)
        {
        counter_obj = 0;

        return true;
        }
    }

    //a new identifier used - reset counter
else
    {
    previousIdentifier_obj = identifier;
    counter_obj = 1;
    }

return false;
}
