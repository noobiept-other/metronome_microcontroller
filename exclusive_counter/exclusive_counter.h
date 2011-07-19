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
