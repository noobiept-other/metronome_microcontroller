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
