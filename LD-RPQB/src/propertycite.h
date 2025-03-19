//
// C++ Interface: PropertyCite
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_CITE_H
#define PROPERTY_CITE_H

#include "property.h"
#include "stringtools.h"

/**
Implements cite property
*/
class PropertyCite : public Property
{

public:
    PropertyCite(char *, unsigned, char *);
    virtual ~PropertyCite();

protected:
    virtual bool calc();
    char *uri1, *uri2, *ref_num;

};

#endif // PROPERTY_CITE_H

