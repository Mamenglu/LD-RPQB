//
// C++ Interface: Property
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
#include "rdftriple.h"
#include "namepoolmgr.h"
#include "stringtools.h"

#define PROPERTY_ABSTRACT      0
#define PROPERTY_ADDRESS       1
#define PROPERTY_AUTHOR        2
#define PROPERTY_BOOKTITLE     3
#define PROPERTY_CDROM         4
#define PROPERTY_CHAPTER       5
#define PROPERTY_CITE          6
#define PROPERTY_CROSSREF      7
#define PROPERTY_EDITOR        8
#define PROPERTY_EE            9
#define PROPERTY_ISBN          10
#define PROPERTY_JOURNAL       11
#define PROPERTY_MONTH         12
#define PROPERTY_NOTE          13
#define PROPERTY_NUMBER        14
#define PROPERTY_PAGE          15
#define PROPERTY_PUBLISHER     16
#define PROPERTY_SCHOOL        17
#define PROPERTY_SERIES        18
#define PROPERTY_TITLE        19
#define PROPERTY_URL        20
#define PROPERTY_VOLUME        21
#define PROPERTY_YEAR        22
#define PROPERTY_AFFECT        23
#define PROPERTY_COAUTHOR      24
#define PROPERTY_RECORD 25

#define PROPERTY_AUTHORNAME    100

using namespace std;

/**
Base class for all document properties
*/
class Property : public RDFTriple
{

public:
    Property(unsigned _type, RDFTriple *);
    virtual ~Property();

protected:
    /**
     * Blind implementation of RDFTriple::calc(). To be reimplemented, default
     * implementation always fails.
     * @return false
     */
    virtual bool calc() {return false;}
    inline RDFTriple * mainTriple() { return main_triple; }

private:
    unsigned type;
    RDFTriple *main_triple;
    bool is_present;

};

#endif // PROPERTY_H
