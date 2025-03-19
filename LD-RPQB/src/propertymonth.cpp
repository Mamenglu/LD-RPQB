//
// C++ Implementation: PropertyMonth
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertymonth.h"

PropertyMonth::PropertyMonth(RDFTriple *main_triple) :
    Property(PROPERTY_MONTH, main_triple)
{
}


PropertyMonth::~PropertyMonth()
{
}

bool PropertyMonth::calc()
{
Randomnizer *r = Randomnizer::getInstance();
char * month;

    month = StringTools::numStr("", r->getRandomValue(12)+1);
    
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "swrc:month");
    RDFObject *o3 = new RDFObject(month,1);
    setObjs(o1, o2, o3);
    
    delete[] month;

    return true;

} //calc()
