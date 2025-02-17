//
// C++ Interface: PropertyCrossref
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_CROSSREF_H
#define PROPERTY_CROSSREF_H

#include "property.h"

/**
Implements cross ref property
*/
class PropertyCrossref : public Property
{

public:
    PropertyCrossref(RDFTriple *, RDFTriple *);
    virtual ~PropertyCrossref();

protected:
    virtual bool calc();
    RDFTriple *parent_triple;

};

#endif // PROPERTY_CROSSREF_H

