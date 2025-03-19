//
// C++ Interface: RandomWww
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RANDOM_WWW_H
#define RANDOM_WWW_H

#include<vector>
#include "randomnizer.h"

#define MAXWWW 10

using namespace std;

/*
 * Singleton
 */
class RandomWww {

public:
    static RandomWww* getInstance();
    virtual ~RandomWww();

    unsigned getResultFromYear(unsigned year);

private:
    static RandomWww* instance;
    RandomWww();

    vector<unsigned> sequence;
    Randomnizer* r;

};


#endif // RANDOM_WWW_H
