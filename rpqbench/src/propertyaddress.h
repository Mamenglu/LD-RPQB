//
// C++ Interface: PropertyAddress
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_ADDRESS_H
#define PROPERTY_ADDRESS_H

#include "property.h"

/**
Implementing address document property
*/
class PropertyAddress : public Property
{
public:
    PropertyAddress(RDFTriple *);
    virtual ~PropertyAddress();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_ADDRESS_H

