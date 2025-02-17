//
// C++ Interface: PropertyYear
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_YEAR_H
#define PROPERTY_YEAR_H

#include "property.h"

/**
Implements year property
*/
class PropertyYear : public Property
{

public:
    PropertyYear(RDFTriple *, unsigned);
    virtual ~PropertyYear();

protected:
    virtual bool calc();

private:
    unsigned year;
    char * yr_str;
};

#endif // PROPERTY_YEAR_H

