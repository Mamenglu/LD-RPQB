//
// C++ Interface: PropertyRecord
//
// Author:WangHui
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_RECORD_H
#define PROPERTY_RECORD_H

#include "property.h"

/**
Implements RECORD
*/
class PropertyRecord : public Property
{

public:
    PropertyRecord(RDFTriple *, RDFObject *);
    virtual ~PropertyRecord();

protected:
    virtual bool calc();
    RDFObject *parent_obj;

};

#endif // PROPERTY_AFFECT_H

