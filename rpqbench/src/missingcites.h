//
// C++ Interface: MissingCites 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef MISSINGCITES_H
#define MISSINGCITES_H

#include <vector>
#include <iostream>
#include <cstring>


#include "randomnizer.h"

using namespace std;

/**
Implements list of URI's with still missing expected incoming citations
@author Michael Schmidt, Christoph Pinkel
*/
class MissingCites
{
public:
    MissingCites();

    virtual ~MissingCites();
    
    vector<char *> citeSomeURIs(unsigned);
    void request(char *, unsigned);
    
    unsigned historicPapersWithCites(unsigned);
    inline unsigned getOutstandingL() { return list.size(); }
    inline unsigned getOutstandingC() { return cnt.size(); }
    
    #ifdef LOGMODE
    vector <unsigned> getIncomingCiteCounts();
    #endif

private:
    vector<char *> list;
    vector<unsigned> cnt;
    
    vector<unsigned> orig_cnt;
    vector<unsigned> completed_cnts;
};

#endif
