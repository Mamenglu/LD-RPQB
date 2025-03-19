//
// C++ Implementation: RandomMaster
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "randommaster.h"

RandomMaster* RandomMaster::instance=NULL;

RandomMaster* RandomMaster::getInstance() {
    if (instance==NULL) {
        instance=new RandomMaster();
    }
    return instance;
}

RandomMaster::RandomMaster()
    : r(Randomnizer::getInstance()) {
}

RandomMaster::~RandomMaster() {
}

unsigned RandomMaster::getResultFromYear(unsigned year) {
    while (sequence.size()<=year) {
        sequence.push_back(r->getRandomValue(MAXMASTER+1));
    }
    return sequence[year];
}
