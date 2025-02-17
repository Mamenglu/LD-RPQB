//
// C++ Implementation: ReferenceBagReference
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008 
// Copyright: See COPYING file that comes with this distribution
//
#include "referencebagreference.h"

ReferenceBagReference::ReferenceBagReference(char *uri1, char *uri2)
 : RDFTriple()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj, uri1);
    RDFObject *o2 = new RDFObject("dcterms", "references");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj, uri2);
    setObjs(o1, o2, o3);
}


ReferenceBagReference::~ReferenceBagReference()
{
}

bool ReferenceBagReference::calc()
{
    return true;
}

