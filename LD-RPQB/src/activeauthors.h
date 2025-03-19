//
// C++ Interface: ActiveAuthors
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef ACTIVEAUTHORS_H
#define ACTIVEAUTHORS_H

#include "author.h"
#include "randomnizer.h"

/**
Pool of active authors (authors that published at least one document of any kind and have not yet retired)

@author Michael Schmidt, Christoph Pinkel
*/
class ActiveAuthors
{
public:
    ActiveAuthors();

    virtual ~ActiveAuthors();
    
    vector<Author *> draw(unsigned);
    Author * newAuthor(unsigned);
    void insertNew(unsigned, vector<Author *> &, unsigned);
    void retire(unsigned);
    void uncalc();

    /**
     * returns number of active authors
     * @return number of active authors
     */
    unsigned count() { return pool->size(); }
    
    vector<Author *> getMAuthorsWithNPublications(unsigned, unsigned);
    
    #ifdef LOGMODE
    float averageCoAuthors();
    float averageDistinctCoAuthors();
    #endif

protected:
    vector <Author *>* pool;
    
    unsigned long retired;
    unsigned long retired_pubs;
    unsigned long retired_coauth_sum;
    unsigned long retired_d_coauth_sum;
};

#endif
