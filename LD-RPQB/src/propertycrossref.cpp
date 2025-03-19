//
// C++ Implementation: PropertyCrossref
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertycrossref.h"

PropertyCrossref::PropertyCrossref(RDFTriple *main_triple,
    RDFTriple *_parent_triple):
    Property(PROPERTY_CROSSREF, main_triple),
    parent_triple(_parent_triple)
{
}


PropertyCrossref::~PropertyCrossref()
{
}

/*!
    \fn PropertyEe::calc()
 */
bool PropertyCrossref::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dcterms", "partOf");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj,
        parent_triple->getSubjectPtr()->getString());
    setObjs(o1, o2, o3);

    return true;

} //calc()
