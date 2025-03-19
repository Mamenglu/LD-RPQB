//
// C++ Implementation: PropertyCite
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertycite.h"

/**
 * Constructor; requires URI's to relate
 * @param main_uri URI of outgoing citation's document
 * @param target_uri URI of incoming citation's document
 * @return 
 */
PropertyCite::PropertyCite(char *main_uri, unsigned num, char *target_uri) :
    Property(PROPERTY_CITE, 0L)
{
uri1 = new char[strlen(main_uri)+1];
uri2 = new char[strlen(target_uri)+1];

    strcpy(uri1, main_uri);
    strcpy(uri2, target_uri);
    ref_num = StringTools::numStr("dcterms:cite", num);
}


PropertyCite::~PropertyCite()
{
    delete[] uri1;
    delete[] uri2;
    delete[] ref_num;
}


/**
 * Calculates the triple's contents
 * @return success
 */
bool PropertyCite::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj, uri1);
    // RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, ref_num);
    RDFObject *o2 = new RDFObject("dcterms", "cite");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj, uri2);
    setObjs(o1, o2, o3);

    return true;
} //calc()
