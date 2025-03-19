//
// C++ Implementation: PropertyAuthorName 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyauthorname.h"

PropertyAuthorName::PropertyAuthorName(RDFTriple *main_triple, unsigned _given_name_id, unsigned _last_name_id) :
    Property(PROPERTY_AUTHORNAME, main_triple), given_name_id(_given_name_id), last_name_id(_last_name_id)
{}


PropertyAuthorName::~PropertyAuthorName()
{}

/**
 * Calculates property triple
 * @return success
 */
bool PropertyAuthorName::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
    const char *nme = StringTools::concatStrs(
                    npm->getNameById(NamePoolFile::givenNames,given_name_id),
                    " ",
                    npm->getNameById(NamePoolFile::familyNames,last_name_id));

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("foaf", "name");
    RDFObject *o3 = new RDFObject(nme);
    setObjs(o1, o2, o3);

    delete[] nme;
    
    return true;
} //calc()
