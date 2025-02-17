//
// C++ Interface: RandomMaster 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RANDOM_MASTER_H
#define RANDOM_MASTER_H

#include<vector>
#include "randomnizer.h"

#define MAXMASTER 10

using namespace std;

/*
 * Singleton
 */
class RandomMaster {

public:
    static RandomMaster* getInstance();
    virtual ~RandomMaster();

    unsigned getResultFromYear(unsigned year);

private:
    static RandomMaster* instance;
    RandomMaster();

    vector<unsigned> sequence;
    Randomnizer* r;

};

#endif // RANDOM_MASTER_H
