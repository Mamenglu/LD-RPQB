//
// C++ Implementation: PropertyBooktitle
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertybooktitle.h"

PropertyBooktitle::PropertyBooktitle(RDFTriple *main_triple) :
    Property(PROPERTY_BOOKTITLE, main_triple)
{
}


PropertyBooktitle::~PropertyBooktitle()
{
}


/*!
    \fn PropertyBooktitle::calc()
 */
bool PropertyBooktitle::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *title = npm->getNewJoinedTWTriple();

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("bench", "booktitle");
    RDFObject *o3 = new RDFObject(title);
    setObjs(o1, o2, o3);

    delete[] title;

    return true;
}
