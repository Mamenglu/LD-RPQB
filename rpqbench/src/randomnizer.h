//
// C++ Interface: Randomnizer 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
// We build upon the public domain implementation from Michael Brundage,
// see "http://qbrundage.com/michaelb/pubs/essays/random_number_generation"
//
#ifndef RANDOMNIZER_H
#define RANDOMNIZER_H

#include <cstdlib>
#include <iostream>

#define MT_LEN       624

using namespace std;

/**
 * Implementation of the Mersenne Twister RNG algorithm
*/
class Randomnizer
{

public:
    static Randomnizer* getInstance();
    virtual ~Randomnizer();
    
    unsigned getRandomValue(unsigned max);

private:
    Randomnizer();
    static Randomnizer* instance;

    int mt_index;
    unsigned long mt_buffer[MT_LEN];

};


#endif // RANDOMNIZER_H

