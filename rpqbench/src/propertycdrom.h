//
// C++ Interface: PropertyCdrom
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_CDROM_H
#define PROPERTY_CDROM_H

#include "property.h"

/**
Implements CD ROM property
*/
class PropertyCdrom : public Property
{

public:
    PropertyCdrom(RDFTriple *);
    virtual ~PropertyCdrom();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_CDROM_H

