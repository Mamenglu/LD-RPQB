//
// C++ Implementation: ReferenceBag
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "referencebag.h"

ReferenceBag::ReferenceBag()
 : RDFTriple()
{
ReferenceBagMgr *rbm = ReferenceBagMgr::getInstance();

    num = rbm->getNext();
}


ReferenceBag::~ReferenceBag()
{
}

bool ReferenceBag::calc()
{
char * uri = StringTools::numStr("_:references", num);

    RDFObject *o1 = new RDFObject(RDFObject::URIObj, uri);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject(RDFObject::AbbrObj, "rdf:Bag");
    setObjs(o1, o2, o3);
    
    delete[] uri;

    return true;
}

