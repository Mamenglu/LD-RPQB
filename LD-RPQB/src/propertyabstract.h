//
// C++ Interface: PropertyAbstract 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_ABSTRACT_H
#define PROPERTY_ABSTRACT_H

#include "property.h"
#include "gaussiandistribution.h"

/**
Implements abstract property
*/
    class PropertyAbstract : public Property
{

public:
    PropertyAbstract(RDFTriple *);
    virtual ~PropertyAbstract();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_ABSTRACT_H
