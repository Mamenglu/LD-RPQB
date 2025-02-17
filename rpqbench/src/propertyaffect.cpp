//
// C++ Implementation: PropertyAffect
//
// Author:WangHui
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyaffect.h"

PropertyAffect::PropertyAffect(RDFTriple *main_triple,
    RDFTriple *_parent_triple):
    Property(PROPERTY_AFFECT, main_triple),
    parent_triple(_parent_triple)
{
}


PropertyAffect::~PropertyAffect()
{
}

/*!
    \fn PropertyEe::calc()
 */
bool PropertyAffect::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("rel", "predecessor");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj,
        parent_triple->getSubjectPtr()->getString());
    setObjs(o1, o2, o3);

    return true;

} //calc()
