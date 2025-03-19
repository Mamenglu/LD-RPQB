//
// C++ Interface: ReferenceBagReference
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef REFERENCEBAGREFERENCE_H
#define REFERENCEBAGREFERENCE_H

#include "rdftriple.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class ReferenceBagReference : public RDFTriple
{
public:
    ReferenceBagReference(char *, char *);

    virtual ~ReferenceBagReference();
    virtual bool calc();

};

#endif
