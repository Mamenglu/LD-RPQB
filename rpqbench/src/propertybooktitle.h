//
// C++ Interface: PropertyBooktitle
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_BOOKTITLE_H
#define PROPERTY_BOOKTITLE_H

#include "property.h"

/**
Implements book title property
*/
class PropertyBooktitle : public Property
{

public:
    PropertyBooktitle(RDFTriple *);
    virtual ~PropertyBooktitle();

protected:
    virtual bool calc();
};

#endif // PROPERTY_BOOKTITLE_H

