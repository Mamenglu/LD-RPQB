//
// C++ Interface: PropertyAuthor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_AUTHOR_H
#define PROPERTY_AUTHOR_H

#include "property.h"

/**
Implements author property
*/
class PropertyAuthor : public Property
{

public:
    PropertyAuthor(RDFTriple *, RDFTriple *);
    virtual ~PropertyAuthor();

protected:
    virtual bool calc();
    char *author_uri;
};

#endif // PROPERTY_AUTHOR_H

