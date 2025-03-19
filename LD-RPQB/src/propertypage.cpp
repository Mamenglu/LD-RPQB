//
// C++ Implementation: PropertyPage
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertypage.h"

PropertyPage::PropertyPage(RDFTriple *main_triple) :
    Property(PROPERTY_PAGE, main_triple)
{
}


PropertyPage::~PropertyPage()
{
}


/*!
    \fn PropertyPage::calc()
 */
bool PropertyPage::calc()
{
Randomnizer *r = Randomnizer::getInstance();
unsigned page = 1 + r->getRandomValue(200);
char *page_str = StringTools::numStr("", page);

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "pages");
    RDFObject *o3 = new RDFObject(page_str,1);
    setObjs(o1, o2, o3);

    delete[] page_str;
    
    return true;
}
