//
// C++ Interface: PropertyMonth
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_MONTH_H
#define PROPERTY_MONTH_H

#include "property.h"
#include "randomnizer.h"

/**
Implements month property
*/
class PropertyMonth : public Property
{

public:
    PropertyMonth(RDFTriple *);
    virtual ~PropertyMonth();

private:

protected:
    bool calc();
};

#endif // PROPERTY_MONTH_H

