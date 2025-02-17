//
// C++ Implementation: PropertyEe
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyee.h"

PropertyEe::PropertyEe(RDFTriple *main_triple) :
    Property(PROPERTY_EE, main_triple)
{
}


PropertyEe::~PropertyEe()
{
}


/*!
    \fn PropertyEe::calc()
 */
bool PropertyEe::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
vector <char *> names = npm->getTWTriple();
char *path = StringTools::concatStrs("http://www.", names[0], ".tld/", names[1]);
char *doc = StringTools::concatStrs(path, "/", names[2], ".html");

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("rdfs", "seeAlso");
    RDFObject *o3 = new RDFObject(doc);
    setObjs(o1, o2, o3);

    delete[] path;
    delete[] doc;
    
    return true;

} //calc()
