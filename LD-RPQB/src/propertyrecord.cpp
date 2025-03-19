//
// C++ Implementation: PropertyRecord
//
// Author:WangHui
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyrecord.h"

PropertyRecord::PropertyRecord(RDFTriple *main_triple,
    RDFObject *_parent_obj):
    Property(PROPERTY_RECORD, main_triple),
    parent_obj(_parent_obj)
{
}


PropertyRecord::~PropertyRecord()
{
}

/*!
    \fn PropertyEe::calc()
 */
bool PropertyRecord::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dcterms", "record");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj,
        parent_obj->getString());
    setObjs(o1, o2, o3);

    return true;

} //calc()
