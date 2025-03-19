//
// C++ Interface: RDFTripleProol
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RDFTRIPLEPOOL_H
#define RDFTRIPLEPOOL_H

#include <vector>
#include <iostream>
#include "rdftriple.h"

using namespace std;

/**
Implements a list of RDFTriple objects

@author Michael Schmidt, Christoph Pinkel
*/
class RDFTriplePool
{
public:
    RDFTriplePool();
    RDFTriplePool(vector <RDFTriple *>);

    virtual ~RDFTriplePool();
    
    void add(RDFTriple *);
    void change(int index ,RDFTriple* rdf);
    void addPool(RDFTriplePool *);
    unsigned count();
    RDFTriple * getElement();
    RDFTriple * getAt(unsigned);
    vector<char *> printAll();
    void removeElement(RDFTriple *);
    void removeAllElement();
    unsigned long totalSize();
    void destroyElements();
    inline vector <RDFTriple *> * vPtr() { return &pool; }
    void uncalcAll();
    

private:
    vector <RDFTriple *> pool;
};

#endif
