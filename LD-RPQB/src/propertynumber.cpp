//
// C++ Implementation: PropertyNumber
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertynumber.h"

PropertyNumber::PropertyNumber(RDFTriple *main_triple,
unsigned _doctype, unsigned _docid, unsigned _year) :
    Property(PROPERTY_NUMBER, main_triple), doctype(_doctype),
    docid(_docid), year(_year)
{
}


PropertyNumber::~PropertyNumber()
{
}


/*!
    \fn PropertyNumber::calc()
 */
bool PropertyNumber::calc()
{
VolumeMgr * vm = VolumeMgr::getInstance();

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "number");
    RDFObject *o3 = 0L;
    
    unsigned vnum = 0;

    switch(doctype)
    {
        case DOCTYPE_JOURNAL:
            vnum = vm->nextNumber(0, docid, year);
            break;
            
        case DOCTYPE_PROCEEDINGS:
            vnum = vm->nextNumber(1, docid, year);
            break;

        default:
            break;
    }
    
    if(vnum)
    {
    char *nstr = StringTools::numStr("", vnum);
        o3 = new RDFObject(nstr,1);
        delete[] nstr;
    }
    else
        o3 = new RDFObject("1",1);

    setObjs(o1, o2, o3);
    
    return true;
}
