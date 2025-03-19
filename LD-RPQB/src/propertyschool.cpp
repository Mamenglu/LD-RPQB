//
// C++ Implementation: PropertySchool
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyschool.h"

PropertySchool::PropertySchool(RDFTriple *main_triple) :
    Property(PROPERTY_SCHOOL, main_triple)
{
}


PropertySchool::~PropertySchool()
{
}


/*!
    \fn PropertySchool::calc()
 */
bool PropertySchool::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *school_nme = npm->getName(NamePoolFile::titleWords);

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dc", "publisher");
    RDFObject *o3 = new RDFObject(school_nme);
    setObjs(o1, o2, o3);

    return true;
}
