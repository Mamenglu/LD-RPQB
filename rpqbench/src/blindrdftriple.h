//
// C++ Interface: BlindRDFTriple
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef BLINDRDFTRIPLE_H
#define BLINDRDFTRIPLE_H

#include "rdftriple.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class BlindRDFTriple : public RDFTriple
{
public:
    BlindRDFTriple(char *, char *, char *);

    virtual ~BlindRDFTriple();
    
protected:
    virtual bool calc();
};

#endif
