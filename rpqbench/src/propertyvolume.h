//
// C++ Interface: PropertyVolume
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_VOLUME_H
#define PROPERTY_VOLUME_H

#include "property.h"
#include "document.h"
#include "volumemgr.h"

/**
Implements volume property
*/
class PropertyVolume : public Property
{

public:
    PropertyVolume(RDFTriple *, unsigned, unsigned, unsigned);
    virtual ~PropertyVolume();

protected:
    virtual bool calc();

private:
    unsigned doctype, docid, year;
};

#endif // PROPERTY_VOLUME_H

