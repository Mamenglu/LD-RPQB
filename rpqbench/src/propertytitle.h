//
// C++ Interface: PropertyTitle
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_TITLE_H
#define PROPERTY_TITLE_H

#include "property.h"
#include "document.h"

/**
Implements document property "title"
*/
class PropertyTitle : public Property
{

public:
    PropertyTitle(RDFTriple *, unsigned, unsigned, unsigned);
    virtual ~PropertyTitle();

protected:
    virtual bool calc();

private:
    unsigned doctype, docnum, year;
};

#endif // PROPERTY_TITLE_H

