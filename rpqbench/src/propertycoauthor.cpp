//
// C++ Implementation: PropertyCoauthor
//
// Author:WangHui
// Copyright: See COPYING file that comes with this distribution
//
#include "propertycoauthor.h"

PropertyCoauthor::PropertyCoauthor(RDFTriple *main_triple,
    RDFTriple *_another_triple):
    Property(PROPERTY_COAUTHOR, main_triple),
    another_triple(_another_triple)
{
}


PropertyCoauthor::~PropertyCoauthor()
{
}

/*!
    \fn PropertyEe::calc()
 */
bool PropertyCoauthor::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("rel", "coauthor");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj,
        another_triple->getSubjectPtr()->getString());
    setObjs(o1, o2, o3);

    return true;

} //calc()
