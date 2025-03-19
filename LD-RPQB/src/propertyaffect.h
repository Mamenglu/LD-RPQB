//
// C++ Interface: PropertyAffect
//
// Author:WangHui
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_AFFECT_H
#define PROPERTY_AFFECT_H

#include "property.h"

/**
Implements affect
*/
class PropertyAffect : public Property
{

public:
    PropertyAffect(RDFTriple *, RDFTriple *);
    virtual ~PropertyAffect();

protected:
    virtual bool calc();
    RDFTriple *parent_triple;

};

#endif // PROPERTY_AFFECT_H

