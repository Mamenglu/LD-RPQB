//
// C++ Interface: PropertyUrl
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_URL_H
#define PROPERTY_URL_H

#include "property.h"

/**
Implements URL property
*/
class PropertyUrl : public Property
{

public:
    PropertyUrl(RDFTriple *);
    virtual ~PropertyUrl();

protected:
    virtual bool calc();
};

#endif // PROPERTY_URL_H

