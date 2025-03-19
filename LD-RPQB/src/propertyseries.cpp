//
// C++ Implementation: PropertySeries
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyseries.h"

PropertySeries::PropertySeries(RDFTriple *main_triple) :
    Property(PROPERTY_SERIES, main_triple)
{
}


PropertySeries::~PropertySeries()
{
}


/*!
    \fn PropertySeries::calc()
 */
bool PropertySeries::calc()
{
Randomnizer *r = Randomnizer::getInstance();
unsigned series = 1000 + r->getRandomValue(1000);
char *series_str = StringTools::numStr("", series);

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "series");
    RDFObject *o3 = new RDFObject(series_str,1);
    setObjs(o1, o2, o3);

    delete[] series_str;
    return true;
}
