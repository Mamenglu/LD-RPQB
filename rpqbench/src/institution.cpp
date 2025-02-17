//
// C++ Implementation: Anstitution
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "institution.h"

Institution::Institution(unsigned _num, unsigned _year) :
    num(_num), numstr(StringTools::numStr("", num)), year(_year)
{
}

Institution::~Institution()
{
}


/**
 * Calculates contents for main ("is a" type) triple
 * @return success; may fail, if relevant information about this documents type are still missing
 */
bool Institution::calc()
{
const char *dtpe = "http://localhost/institution";
char *nme = 0L;
char *jid_str = 0L;
char *jidy_str = 0L;
            
    nme = StringTools::concatStrs("Institution", numstr, "/", StringTools::numStr("", year));
    RDFObject *o1 = new RDFObject(dtpe, nme, false);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("bench", "Institution");
    setObjs(o1, o2, o3);
        
        
    delete[] nme;
    delete[] jidy_str;
    
    return true;

} //calc()
