//
// C++ Interface: RandomPhD
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RANDOM_PHD_H
#define RANDOM_PHD_H

#include<vector>
#include "randomnizer.h"

#define MAXPHD 20

using namespace std;

/*
 * Singleton
 */
class RandomPhD {

public:
    static RandomPhD* getInstance();
    virtual ~RandomPhD();

    unsigned getResultFromYear(unsigned year);

private:
    static RandomPhD* instance;
    RandomPhD();

    vector<unsigned> sequence;
    Randomnizer* r;

};


#endif // RANDOM_PHD_H
