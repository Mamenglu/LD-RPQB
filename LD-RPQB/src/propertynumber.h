//
// C++ Interface: PropertyNumber
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_NUMBER_H
#define PROPERTY_NUMBER_H

#include "property.h"
#include "document.h"
#include "volumemgr.h"

/**
Implements number property
*/
class PropertyNumber : public Property
{

public:
    PropertyNumber(RDFTriple *, unsigned, unsigned, unsigned);
    virtual ~PropertyNumber();

protected:
    virtual bool calc();

private:
    unsigned doctype, docid, year;
};

#endif // PROPERTY_NUMBER_H

