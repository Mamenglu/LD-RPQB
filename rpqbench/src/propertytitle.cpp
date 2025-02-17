//
// C++ Implementation: PropertyTitle
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertytitle.h"

PropertyTitle::PropertyTitle(RDFTriple *main_triple, unsigned _doctype,
    unsigned _docnum, unsigned _year) :
    Property(PROPERTY_TITLE, main_triple), doctype(_doctype),
    docnum(_docnum), year(_year)
{
}


PropertyTitle::~PropertyTitle()
{
}


/*!
    \fn PropertyTitle::calc()
 */
bool PropertyTitle::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *rndtitle = npm->getNewJoinedTWTriple();

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dc", "title");
    
    RDFObject *o3 = 0L;
    char *nstr1 = 0L;
    char *nstr2 = 0L;
    char *nme = 0L;

    switch(doctype)
    {
        case DOCTYPE_JOURNAL:
            nstr1 = StringTools::numStr("Journal ", docnum);
            nstr2 = StringTools::numStr("", year);
            nme = StringTools::concatStrs(nstr1, " (", nstr2, ")");
            o3 = new RDFObject(nme);
            break;

        case DOCTYPE_PROCEEDINGS:
            nstr1 = StringTools::numStr("Proceeding ", docnum);
            nstr2 = StringTools::numStr("", year);
            nme = StringTools::concatStrs(nstr1, " (", nstr2, ")");
            o3 = new RDFObject(nme);
            break;

        default:
            o3 = new RDFObject(rndtitle);
            break;
    }
    
    setObjs(o1, o2, o3);
    
    delete[] rndtitle;

    if(nstr1)
        delete[] nstr1;
        
    if(nstr2)
        delete[] nstr2;
        
    if(nme)
        delete[] nme;

    return true;
}
