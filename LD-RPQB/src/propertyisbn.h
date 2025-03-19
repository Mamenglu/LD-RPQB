//
// C++ Interface: PropertyIsbn
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_ISBN_H
#define PROPERTY_ISBN_H

#include "property.h"
#include "randomnizer.h"
#include "stringtools.h"

/**
Implements ISBN property
*/
class PropertyIsbn : public Property
{

public:
    PropertyIsbn(RDFTriple *);
    virtual ~PropertyIsbn();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_ISBN_H

