//
// C++ Interface: GaussianDistribution 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef GAUSSIAN_DISTRIBUTION_H
#define GAUSSIAN_DISTRIBUTION_H

#include <iostream>
#include "functions.h"
#include "randomnizer.h"
#include <vector>


#define ACCURACY    10000


using namespace std;

class GaussianDistribution {

public:
    GaussianDistribution(unsigned _x_limit_left,double _mu,double _sigma);
    virtual ~GaussianDistribution();

    unsigned getRandomnizedValue();
    double getAverage();

private:

    // passed parameters
    double mu;                // expectation value
    double sigma;            // variance
    unsigned x_limit_left;    // starting integer, either 0 or 1

    // calculated values:
    unsigned x_limit_right;        // limit to the right

    // functions
    double probability(unsigned num);    // probability wo. x_limit_right

    Randomnizer* r;
    vector<unsigned> bucket;

    unsigned RANGE;
};


#endif // GAUSSIAN_DISTRIBUTION_H

