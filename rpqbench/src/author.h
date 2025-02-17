//
// C++ Interface: Author
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef AUTHOR_H
#define AUTHOR_H

#include <vector>
#include "rdftriple.h"
#include "stringtools.h"
#include "namepoolmgr.h"
#include "propertyauthor.h"
#include "propertyauthorname.h"

using namespace std;

/**
Implements authors

@author Michael Schmidt, Christoph Pinkel
*/
class Author : public RDFTriple
{
public:
    Author(unsigned);

    virtual ~Author();
    
    RDFTriple * createPublicationRelationTriple(RDFTriple *);
    
    bool haveCoAuthor(Author *);
    void addCoAuthor(Author *);
    void retireCoAuthor(Author *);
    vector <Author *> getCoAuthor();
    
    inline unsigned firstYear() { return first_year; };
    inline unsigned publications() { return publication_cnt; };
    inline unsigned coAuthors() { return coauth_cnt; };
    unsigned distinctCoAuthors();
    inline unsigned retiredDistinctCoAuthors() { return retired_dist_coauth_cnt; };
    
    inline void assignPublExp(unsigned cnt) { publ_expect = cnt; orig_publ_expect = cnt; };
    inline void assignCoauthExp(unsigned cnt) { coauth_expect = cnt; };
    inline void assignDCoauthExp(unsigned cnt) { dist_coauth_expect = cnt; };
    
    inline unsigned expectedPublications() { return publ_expect; };
    inline unsigned origExpectedPublications() { return orig_publ_expect; };
    inline unsigned expectedCoauths() { return coauth_expect; };
    inline unsigned expectedDCoauths() { return dist_coauth_expect; };
    
    void addPublication();
    
    inline unsigned getGivenName() { return given_name_id; }
    inline unsigned getLastName() { return last_name_id; }

    void setWithString(char* str);
    
protected:
    virtual bool calc();
    
    unsigned given_name_id;
    unsigned last_name_id;

    unsigned first_year;
    unsigned publication_cnt;
    unsigned coauth_cnt;
    unsigned retired_dist_coauth_cnt;
    
    unsigned publ_expect; //for current year (remaining)
    unsigned orig_publ_expect; //for current year (total)
    unsigned coauth_expect; //for current year (remaining)
    unsigned dist_coauth_expect; //for current year (remaining)
    
    vector <Author *> co_authors;
};

#endif
