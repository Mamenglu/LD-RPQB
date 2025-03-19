//
// C++ Implementation: PropertyYear
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyyear.h"

PropertyYear::PropertyYear(RDFTriple *main_triple, unsigned _year) :
    Property(PROPERTY_YEAR, main_triple), year(_year), yr_str(0L)
{
unsigned ysl = 0;

    //calculating string length for year string...
    for(int f = 1; year/f > 0; f *= 10)
        ysl++;

    if(ysl == 0) ysl = 1; //even for year "0" string length is 1

    yr_str = new char[ysl + 1];
    
    //filling yr_str...
    yr_str[ysl] = 0; //terminator
    int pos = ysl -1;
    unsigned tmpnum = year;
    
    while(pos >= 0)
    {
        yr_str[pos] = tmpnum % 10 + 48;
        tmpnum /= 10;
        pos--;
    } //while

} //constructor


PropertyYear::~PropertyYear()
{
    delete[] yr_str;
}


/*!
    \fn PropertyYear::calc()
 */
bool PropertyYear::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dcterms", "issued");
    RDFObject *o3 = new RDFObject(yr_str,2);
    setObjs(o1, o2, o3);

    return true;
}
