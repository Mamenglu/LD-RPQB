//
// C++ Implementation: PropertyIsbn
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyisbn.h"

PropertyIsbn::PropertyIsbn(RDFTriple *main_triple) :
    Property(PROPERTY_ISBN, main_triple)
{
}


PropertyIsbn::~PropertyIsbn()
{
}


/*!
    \fn PropertyIsbn::calc()
 */
bool PropertyIsbn::calc()
{
Randomnizer *r = Randomnizer::getInstance();
unsigned publisher = 1000 + r->getRandomValue(9000);
unsigned item = 1000 + r->getRandomValue(9000);
char *p_str = StringTools::numStr("", publisher);
char *i_str = StringTools::numStr("-", item);
char *isbn = StringTools::concatStrs("0-", p_str, i_str, "-0");
    
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "isbn");
    RDFObject *o3 = new RDFObject(isbn);
    setObjs(o1, o2, o3);

    delete[] p_str;
    delete[] i_str;
    delete[] isbn;

    return true;
}
