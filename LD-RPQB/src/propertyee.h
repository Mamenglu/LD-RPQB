//
// C++ Interface: PropertyEe
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_EE_H
#define PROPERTY_EE_H

#include "property.h"

/**
Implements EE property
*/
class PropertyEe : public Property
{

public:
    PropertyEe(RDFTriple *);
    virtual ~PropertyEe();

protected:
    virtual bool calc();
};

#endif // PROPERTY_EE_H

