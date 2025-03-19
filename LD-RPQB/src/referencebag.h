//
// C++ Interface: ReferenceBag
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef REFERENCEBAG_H
#define REFERENCEBAG_H

#include "rdftriple.h"
#include "referencebagmgr.h"
#include "stringtools.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class ReferenceBag : public RDFTriple
{
public:
    ReferenceBag();

    virtual ~ReferenceBag();

    virtual bool calc();

private:
    unsigned num;
};

#endif
