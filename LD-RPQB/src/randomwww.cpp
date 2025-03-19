//
// C++ Implementation: RandomWww
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "randomwww.h"

RandomWww* RandomWww::instance=NULL;

RandomWww* RandomWww::getInstance() {
    if (instance==NULL) {
        instance=new RandomWww();
    }
    return instance;
}

RandomWww::RandomWww()
    : r(Randomnizer::getInstance()) {
}

RandomWww::~RandomWww() {
}

unsigned RandomWww::getResultFromYear(unsigned year) {
    while (sequence.size()<=year) {
        sequence.push_back(r->getRandomValue(MAXWWW+1));
    }
    return sequence[year];
}
