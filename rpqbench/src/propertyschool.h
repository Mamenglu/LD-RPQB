//
// C++ Interface: PropertySchool
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_SCHOOL_H
#define PROPERTY_SCHOOL_H

#include "property.h"

/**
Implements school property
*/
class PropertySchool : public Property
{

public:
    PropertySchool(RDFTriple *);
    virtual ~PropertySchool();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_SCHOOL_H

