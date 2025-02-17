//
// C++ Implementation: Inproceedings 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "inproceedings.h"

Inproceedings::Inproceedings(unsigned num, unsigned year, unsigned proceeding_num)
    : Document(DOCTYPE_INPROCEEDINGS, num, year), pnum(proceeding_num)
{
}

Inproceedings::~Inproceedings()
{
}

/**
 * Calculates contents for main ("is a" type) triple
 * @return success; may fail, if relevant information about this documents type are still missing
 */
bool Inproceedings::calc()
{
const char *dtpe = "http://localhost/publications/inprocs";
char *nme = 0L;
char *pid_str = 0L;
char *pidy_str = 0L;

    pid_str = StringTools::numStr("Proceeding", pnum);
    pidy_str = StringTools::numStr("/", year);
    
    nme = StringTools::concatStrs(pid_str, pidy_str, "/Inproceeding", numstr);
    
    delete[] pid_str;
    delete[] pidy_str;

    #ifdef LOGMODE
    setLogId(LOGID_INPROCEEDING);
    #endif
            
    RDFObject *o1 = new RDFObject(dtpe, nme, false);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("bench", "Inproceedings");
    setObjs(o1, o2, o3);
    
    delete[] nme;
    
    return true;

} //calc()

