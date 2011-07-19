#ifndef ERROR_GUARD
#define ERROR_GUARD

/*
    To tell if there were any errors, check these flags
    They should be checked right after an operation, and if there was an error,
    please clear the flag (Error::whateverFlag = false;)
 */

namespace Error
{
extern bool wrongPin;
extern bool wrongPort;
extern bool wrongInit;
}




#endif //ERROR_GUARD
