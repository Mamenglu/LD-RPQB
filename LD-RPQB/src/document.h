//
// C++ Interface: Document  
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef DOCUMENT_H
#define DOCUMENT_H

#define DOCTYPE_JOURNAL         0
#define DOCTYPE_ARTICLE         1
#define DOCTYPE_PROCEEDINGS     2
#define DOCTYPE_INPROCEEDINGS   3
#define DOCTYPE_BOOK            4
#define DOCTYPE_INCOLLECTION    5
#define DOCTYPE_PHDTHESIS       6
#define DOCTYPE_MASTERSTHESIS   7
#define DOCTYPE_WWW             8

#include <vector>
#include "rdftriple.h"
#include "property.h"
#include "propertyabstract.h"
#include "propertyaddress.h"
#include "propertyauthor.h"
#include "propertyaffect.h"
#include "propertybooktitle.h"
#include "propertycdrom.h"
#include "propertychapter.h"
#include "propertycoauthor.h"
#include "propertycite.h"
#include "propertycrossref.h"
#include "propertyeditor.h"
#include "propertyee.h"
#include "propertyisbn.h"
#include "propertyjournal.h"
#include "propertymonth.h"
#include "propertynote.h"
#include "propertynumber.h"
#include "propertypage.h"
#include "propertypublisher.h"
#include "propertyrecord.h"
#include "propertyschool.h"
#include "propertyseries.h"
#include "propertytitle.h"
#include "propertyurl.h"
#include "propertyvolume.h"
#include "propertyyear.h"
#include "propertymanager.h"
#include "stringtools.h"

using namespace std;

/**
@author Michael Schmidt, Christoph Pinkel
Implements a base class for documents and events (as opposed to document attributes)
*/
class Document : public RDFTriple
{
public:
    Document(unsigned _doctype, unsigned _num, unsigned _year);
    virtual ~Document();
    
    // int getNumofTotalpage(){return numoftotalpage;}
    static int numoftotalpage;
    static int numoftotalabstract;
    static int numoftotalpartof;

    inline unsigned getDoctype() { return doctype; }

    /*!
        \fn Document::requireAuthor()
    */
    bool requireAuthor() { return require[0]; }

    /*!
        \fn Document::requireEditor()
    */
    bool requireEditor() { return require[1]; }

    /*!
        \fn Document::requireCite()
    */
    bool requireCite() { return require[2]; }

    /*!
        \fn Document::requireJournal()
    */
    bool requireJournal() { return require[3]; }
    
        /*!
        \fn Document::requireCrossRef()
    */
    bool requireCrossRef() { return require[4]; }
    

protected:
    virtual bool calc();
    virtual void init();
    unsigned doctype;
    bool is_initialized;
    unsigned num;
    char * numstr;
    unsigned year;
    
    
};



#endif // DOCUMENT_H
