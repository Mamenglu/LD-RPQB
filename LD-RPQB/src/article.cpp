//
// C++ Implementation: Article
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "article.h"

Article::Article(unsigned num, unsigned year, int _jnum)
    : Document(DOCTYPE_ARTICLE, num, year), jnum(_jnum)
{
}

Article::~Article()
{
}

int Article::getjnum(){
    return jnum;
}


/**
 * Calculates contents for main ("is a" type) triple
 * @return success; may fail, if relevant information about this documents type are still missing
 */
bool Article::calc()
{
const char *dtpe = "http://localhost/publications/articles";
char *nme = 0L;
char *jid_str = 0L;
char *jidy_str = 0L;

    jidy_str = StringTools::numStr("/", year);
    
    if(jnum < 1 && requireJournal())
    {
        //no valid journal num, but need one - this won't work
        cout << "fatal error: trying to force article into unspecified journal" << endl;
        exit(9);
    }
    else if(! requireJournal())
    { //no related journal should be set
        nme = StringTools::concatStrs("Unknown_Journal", jidy_str, "/Article", numstr);
    }
    else
    { //std case; journal required and set

        jid_str = StringTools::numStr("Journal", jnum);
        nme = StringTools::concatStrs(jid_str, jidy_str, "/Article", numstr);
    
        delete[] jid_str;
    }

    #ifdef LOGMODE
    setLogId(LOGID_ARTICLE);
    #endif
    
    RDFObject *o1 = new RDFObject(dtpe, nme, false);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("bench", "Article");
    setObjs(o1, o2, o3);
        
        
    delete[] nme;
    delete[] jidy_str;
    
    return true;

} //calc()
