//
// C++ Implementation: Randomnizer 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "randomnizer.h"

#define MT_IA           397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)

Randomnizer* Randomnizer::instance=NULL;

Randomnizer* Randomnizer::getInstance() {
    if (instance==NULL) {
        instance=new Randomnizer();
    }

    return instance;
}

Randomnizer::Randomnizer() {
    int i;
    for (i = 0; i < MT_LEN; i++)
        mt_buffer[i] = i; // fixed seed -> create same data in each run!
    mt_index = 0;
}

Randomnizer::~Randomnizer() {
}

unsigned Randomnizer::getRandomValue(unsigned max)
{
    unsigned long * b = mt_buffer;
    int idx = mt_index;
    unsigned long s;
    int i;
    
    if (idx == MT_LEN*sizeof(unsigned long))
    {
        idx = 0;
        i = 0;
        for (; i < MT_IB; i++) {
            s = TWIST(b, i, i+1);
            b[i] = b[i + MT_IA] ^ (s >> 1) ^ MAGIC(s);
        }
        for (; i < MT_LEN-1; i++) {
            s = TWIST(b, i, i+1);
            b[i] = b[i - MT_IB] ^ (s >> 1) ^ MAGIC(s);
        }
        
        s = TWIST(b, MT_LEN-1, 0);
        b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ MAGIC(s);
    }
    mt_index = idx + sizeof(unsigned long);
    return (*(unsigned long *)((unsigned char *)b + idx))%max;
}
