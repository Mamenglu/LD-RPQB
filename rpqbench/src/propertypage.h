//
// C++ Interface: PropertyPage
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_PAGE_H
#define PROPERTY_PAGE_H

#include "property.h"
#include "randomnizer.h"

/**
Implements page property
*/
class PropertyPage : public Property
{

public:
    PropertyPage(RDFTriple *);
    virtual ~PropertyPage();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_PAGE_H

