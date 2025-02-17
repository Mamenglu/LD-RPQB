//
// C++ Implementation: BlindRDFTriple 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "blindrdftriple.h"

BlindRDFTriple::BlindRDFTriple(char *c1, char *c2, char *c3)
 : RDFTriple()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj, c1);
    RDFObject *o2 = new RDFObject(RDFObject::ConstObj, c2);
    RDFObject *o3 = new RDFObject(RDFObject::ConstObj, c3);
    
    setObjs(o1, o2, o3);
}


BlindRDFTriple::~BlindRDFTriple()
{
}

bool BlindRDFTriple::calc()
{
    return true; //calculation done in constructor
}
