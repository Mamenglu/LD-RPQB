//
// C++ Implementation: GaussianDistribution 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "gaussiandistribution.h"

#define OFFSET_VALUE 0.00001        // y-value where cut is set

GaussianDistribution::GaussianDistribution(unsigned _x_limit_left,double _mu,
                                            double _sigma) :
    mu(_mu), sigma(_sigma), x_limit_left(_x_limit_left), 
    r(Randomnizer::getInstance()), RANGE(0) {

    if (mu<x_limit_left) {
        exit(4); // this is not allows for this curve type
    }

    double sum=0;
    unsigned num=x_limit_left;
    // sum<=0.5 makes sure that we do not break too early
    while (sum<=0.5 || probability(num)>OFFSET_VALUE) {
        sum+=probability(num++);
        bucket.push_back(Functions::doubleToUnsigned(sum*ACCURACY));
    }
    sum+=probability(num);
    bucket.push_back(Functions::doubleToUnsigned(sum*ACCURACY));
    RANGE=bucket[bucket.size()-1];

    // this is the right bucket limit
    x_limit_right=num;
}

GaussianDistribution::~GaussianDistribution() {
}

unsigned GaussianDistribution::getRandomnizedValue() {

    unsigned random_value=r->getRandomValue(RANGE);

    // compute position in bucket vector
    unsigned position=0;
    while (random_value>bucket[position++]) {}

    unsigned ret=position-1+x_limit_left;
    return ret;
}

/**
 * calculates the average number for the distribution;
 * note that this average is larger than the expectation value,
 * since curves are limited to the left by x-value 1
*/
double GaussianDistribution::getAverage() {
   double sum1=0;
   double sum2=0;
   for (unsigned i=x_limit_left;i<=x_limit_right;i++) {
       sum1+=i*probability(i);
       sum2+=probability(i);
   }

   return sum1/sum2;
}

double GaussianDistribution::probability(unsigned num) {
    return Functions::probGauss(num,mu,sigma);
} 
