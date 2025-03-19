//
// C++ Implementation: RandomPhD
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "randomphd.h"

RandomPhD* RandomPhD::instance=NULL;

RandomPhD* RandomPhD::getInstance() {
    if (instance==NULL) {
        instance=new RandomPhD();
    }
    return instance;
}

RandomPhD::RandomPhD()
    : r(Randomnizer::getInstance()) {
}

RandomPhD::~RandomPhD() {
}

unsigned RandomPhD::getResultFromYear(unsigned year) {
    while (sequence.size()<=year) {
        sequence.push_back(r->getRandomValue(MAXPHD+1));
    }
    return sequence[year];
}
