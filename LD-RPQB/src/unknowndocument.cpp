//
// C++ Implementation: UnknownDocument 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "unknowndocument.h"

UnknownDocument::UnknownDocument()
    : RDFTriple()
{
UnknownDocMgr *udm = UnknownDocMgr::getInstance();

    uri = udm->getNext();
}


UnknownDocument::~UnknownDocument()
{
    delete[] uri;
}

bool UnknownDocument::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj, uri);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject(RDFObject::AbbrObj, "rdf:document");
    setObjs(o1, o2, o3);
    
    return true;
}
