//
// C++ Implementation: PropertyChapter
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertychapter.h"

PropertyChapter::PropertyChapter(RDFTriple *main_triple) :
    Property(PROPERTY_CHAPTER, main_triple)
{
}


PropertyChapter::~PropertyChapter()
{
}


/*!
    \fn PropertyChapter::calc()
 */
bool PropertyChapter::calc()
{
Randomnizer *r = Randomnizer::getInstance();
unsigned chap = 1 + r->getRandomValue(20);
char *chap_str = StringTools::numStr("", chap);

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "chapter");
    RDFObject *o3 = new RDFObject(chap_str,1);
    setObjs(o1, o2, o3);

    delete[] chap_str;
    return true;
}
