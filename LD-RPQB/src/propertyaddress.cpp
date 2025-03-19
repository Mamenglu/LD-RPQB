//
// C++ Implementation: PropertyAddress
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyaddress.h"

PropertyAddress::PropertyAddress(RDFTriple *main_triple) :
    Property(PROPERTY_ADDRESS, main_triple)
{
}


PropertyAddress::~PropertyAddress()
{
}


/*!
    \fn PropertyAddress::calc()
 */
bool PropertyAddress::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *address = npm->getNewJoinedTWTriple();

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "address");
    RDFObject *o3 = new RDFObject(address, 3);

    setObjs(o1, o2, o3);
    
    delete[] address;

    return true;
}
