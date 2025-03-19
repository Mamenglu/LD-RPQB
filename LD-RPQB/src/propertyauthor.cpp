//
// C++ Implementation: PropertyAuthor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyauthor.h"

PropertyAuthor::PropertyAuthor(RDFTriple *main_triple,
    RDFTriple *author_triple) :
    Property(PROPERTY_AUTHOR, main_triple), author_uri(0L)
{
author_uri = new char[strlen(author_triple->getSubjectPtr()->getString()) + 1];

    strcpy(author_uri, author_triple->getSubjectPtr()->getString());
}


PropertyAuthor::~PropertyAuthor()
{
    delete[] author_uri;
}

/*!
    \fn PropertyAuthor::calc()
 */
bool PropertyAuthor::calc()
{
    #ifdef LOGMODE
    setLogId(LOGID_AUTHOR);
    #endif
    
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dc", "creator");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj, author_uri);
    setObjs(o1, o2, o3);

    return true;
}
