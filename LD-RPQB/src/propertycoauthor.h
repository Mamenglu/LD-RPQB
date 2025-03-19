//
// C++ Interface: PropertyCOAUTHOR
//
// Author: Wanghui
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_COAUTHOR_H
#define PROPERTY_COAUTHOR_H

#include "property.h"

/**
Implements Coauthor
*/
class PropertyCoauthor : public Property
{

public:
    PropertyCoauthor(RDFTriple *, RDFTriple *);
    virtual ~PropertyCoauthor();

protected:
    virtual bool calc();
    RDFTriple *another_triple;

};

#endif // PROPERTY_COAUTHOR_H

