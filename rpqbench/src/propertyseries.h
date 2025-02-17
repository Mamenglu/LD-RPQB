//
// C++ Interface: PropertySeries
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_SERIES_H
#define PROPERTY_SERIES_H

#include "property.h"
#include "randomnizer.h"

/**
Implements series property
*/
class PropertySeries : public Property
{

public:
    PropertySeries(RDFTriple *);
    virtual ~PropertySeries();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_SERIES_H

