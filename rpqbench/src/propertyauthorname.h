//
// C++ Interface: PropertyAuthorName 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTYAUTHORNAME_H
#define PROPERTYAUTHORNAME_H

#include "property.h"

/**
Implements name property for authors
@author Michael Schmidt, Christoph Pinkel
*/
class PropertyAuthorName : public Property
{
public:
    PropertyAuthorName(RDFTriple *, unsigned, unsigned);

    virtual ~PropertyAuthorName();

protected:
    virtual bool calc();
    unsigned given_name_id;
    unsigned last_name_id;
};

#endif
