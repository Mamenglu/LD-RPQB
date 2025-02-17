//
// C++ Interface: PropertyPublisher
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_PUBLISHER_H
#define PROPERTY_PUBLISHER_H

#include "property.h"
#include "randomnizer.h"

/**
Implements publisher property
*/
class PropertyPublisher : public Property
{

public:
    PropertyPublisher(RDFTriple *);
    virtual ~PropertyPublisher();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_PUBLISHER_H

