//
// C++ Implementation: Document 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "document.h"

int Document::numoftotalpage = 0;
int Document::numoftotalabstract = 0;
int Document::numoftotalpartof = 0;

Document::Document(unsigned _doctype, unsigned _num, unsigned _year) :
    doctype(_doctype), num(_num), numstr(StringTools::numStr("", num)), year(_year)
{
        if(1 || (doctype != DOCTYPE_PROCEEDINGS
            && doctype != DOCTYPE_INPROCEEDINGS))
        {
            init();
        }
}


Document::~Document()
{
    delete[] numstr;
}


/**
 * Calculates contents for main ("is a" type) triple
 * @return success; may fail, if relevant information about this documents type are still missing
 */
bool Document::calc()
{
const char *dtpe = 0L;
char *nme = 0L;
const char *typed = 0L;
char *ys = StringTools::numStr("", year);

    if(! is_inited)
            init();

    switch(doctype)
    {
        case DOCTYPE_JOURNAL:
            dtpe = "http://localhost/publications/journals";
            nme = StringTools::concatStrs("Journal", numstr, "/", ys);
            typed = "Journal";
            #ifdef LOGMODE
            setLogId(LOGID_JOURNAL);
            #endif
            break;

        case DOCTYPE_ARTICLE:
            return false; //should not reach this point, as reimplemented for article
            break;
            
        case DOCTYPE_PROCEEDINGS:
            dtpe = "http://localhost/publications/procs";
            nme = StringTools::concatStrs("Proceeding", numstr, "/", ys);
            typed = "Proceedings";
            #ifdef LOGMODE
            setLogId(LOGID_PROCEEDING);
            #endif
            break;
            
        case DOCTYPE_INPROCEEDINGS:
            return false; //should not reach this point, as reimplemented for inproceedings
            break;
            
        case DOCTYPE_BOOK:
            dtpe = "http://localhost/publications/books";
            nme = StringTools::concatStrs(ys, "/Book", numstr);
            typed = "Book";
            #ifdef LOGMODE
            setLogId(LOGID_BOOK);
            #endif
            break;
            
        case DOCTYPE_INCOLLECTION:
            dtpe = "http://localhost/publications/incolls";
            nme = StringTools::concatStrs(ys, "/Incollection", numstr);
            typed = "Incollection";
            #ifdef LOGMODE
            setLogId(LOGID_INCOLLECTION);
            #endif
            break;
            
        case DOCTYPE_PHDTHESIS:
            dtpe = "http://localhost/publications/phds";
            nme = StringTools::concatStrs(ys, "/PhDThesis", numstr);
            typed = "PhDThesis";
            #ifdef LOGMODE
            setLogId(LOGID_PHD);
            #endif
            break;
            
        case DOCTYPE_MASTERSTHESIS:
            dtpe = "http://localhost/publications/masters";
            nme = StringTools::concatStrs(ys, "/MastersThesis", numstr);
            typed = "MastersThesis";
            #ifdef LOGMODE
            setLogId(LOGID_MASTERS);
            #endif
            break;
            
        case DOCTYPE_WWW:
            dtpe = "http://localhost/publications/wwws";
            nme = StringTools::concatStrs(ys, "/WebDoc", numstr);
            typed = "Www";
            #ifdef LOGMODE
            setLogId(LOGID_WWW);
            #endif
            break;

        default:
            cout << "error: unknown document type" << endl;
            exit(3);
            break;
    }

    RDFObject *o1 = new RDFObject(dtpe, nme, false);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("bench", typed);
    setObjs(o1, o2, o3);

    delete[] nme;
    delete[] ys;
    
    return true;

} //calc()


void Document::init()
{
    PropertyManager* pman=PropertyManager::getInstance();
    pman->freshAttributeSet(getDoctype());

    //abstract
    if (pman->containsAttribute(PROPERTY_ABSTRACT))
    {
        numoftotalabstract++;
        addRelated(new PropertyAbstract(this));
    }
    
    //address
    if (pman->containsAttribute(PROPERTY_ADDRESS))
    {
        addRelated(new PropertyAddress(this));
    }
    
    //author(s)
    if (pman->containsAttribute(PROPERTY_AUTHOR))
    {
        require[0] = true;
    }
    
    //book title
    if (pman->containsAttribute(PROPERTY_BOOKTITLE))
    {
        addRelated(new PropertyBooktitle(this));
    }
    
    //CD
    if (pman->containsAttribute(PROPERTY_CDROM))
    {
        addRelated(new PropertyCdrom(this));
    }
    
    //chapter
    if (pman->containsAttribute(PROPERTY_CHAPTER))
    {
        addRelated(new PropertyChapter(this));
    }
    
    //cite(s)
    if (pman->containsAttribute(PROPERTY_CITE))
    {
        require[1] = true;
    }
    
    //crossref(s)
    if (pman->containsAttribute(PROPERTY_CROSSREF))
    {
        numoftotalpartof++;
        require[4] = true;
    }
    
    //editor(s)
    if (pman->containsAttribute(PROPERTY_EDITOR))
    {
        require[2] = true;
    }
    
    //some kind of links/URL's...
    if (pman->containsAttribute(PROPERTY_EE))
    {
        addRelated(new PropertyEe(this));
    }
    
    //book ISBN
    if (pman->containsAttribute(PROPERTY_ISBN))
    {
        addRelated(new PropertyIsbn(this));
    }
    
    //journal
    if (pman->containsAttribute(PROPERTY_JOURNAL))
    {
        require[3] = true;
    }
    
    //month
    if (pman->containsAttribute(PROPERTY_MONTH))
    {
        addRelated(new PropertyMonth(this));
    }
    
    //note
    if (pman->containsAttribute(PROPERTY_NOTE))
    {
        addRelated(new PropertyNote(this));
    }
    
    /*number - usually numbers are sub information to volumes;
      however, following the observations from dblp data, this does not
      hold for the recorded data for document types other than journals (articles)
      and proceedings; for other document types, those information is largely
      unrelated in the recorded data; therefore only use this information
      for journals, proceedings, where we also modified the probabilities
      accordingly (knowing that numbers for items without a volume will
      be discarded)*/
    if (pman->containsAttribute(PROPERTY_NUMBER)
        && (pman->containsAttribute(PROPERTY_VOLUME)
            || (doctype != DOCTYPE_ARTICLE && doctype != DOCTYPE_PROCEEDINGS)))
    {
        addRelated(new PropertyNumber(this, doctype, num, year));
    }
    
    //page
    if (pman->containsAttribute(PROPERTY_PAGE))
    {
        numoftotalpage++;
        addRelated(new PropertyPage(this));
    }
    
    //publisher(s)
    if (pman->containsAttribute(PROPERTY_PUBLISHER))
    {
        addRelated(new PropertyPublisher(this));
    }
    
    //school (as publisher)
    if (pman->containsAttribute(PROPERTY_SCHOOL))
    {
        addRelated(new PropertySchool(this));
    }
    
    //series
    if (pman->containsAttribute(PROPERTY_SERIES))
    {
        addRelated(new PropertySeries(this));
    }
    
    //title
    if (pman->containsAttribute(PROPERTY_TITLE))
    {
        addRelated(new PropertyTitle(this, doctype, num, year));
    }
    
    //url
    if (pman->containsAttribute(PROPERTY_URL))
    {
        addRelated(new PropertyUrl(this));
    }
    
    //#volume
    if (pman->containsAttribute(PROPERTY_VOLUME))
    {
        addRelated(new PropertyVolume(this, doctype, num, year));
    }
    
    //year
    if (pman->containsAttribute(PROPERTY_YEAR))
    {
        addRelated(new PropertyYear(this, year));
    }

    is_inited = true;

} //init()

