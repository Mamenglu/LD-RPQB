#ifndef INSTITUTION_H
#define INSTITUTION_H

#include "rdftriple.h"
#include "stringtools.h"

/**
Implements document type Institution
*/
class Institution : public RDFTriple
{

public:
    Institution(unsigned,unsigned);
    virtual ~Institution();

protected:
    virtual bool calc();
    unsigned num;
    char * numstr;
    unsigned year;
};

#endif // Institution_H