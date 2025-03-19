//
// C++ Interface: NamePoolMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef NAMEPOOLMGR_H
#define NAMEPOOLMGR_H

#include "namepool.h"

/**
Singleton pattern class to allow global access to randomly combined names and titles from diverse name files

@author Michael Schmidt, Christoph Pinkel
*/
class NamePoolMgr
{
public:
    static NamePoolMgr *getInstance();
    ~NamePoolMgr();
    char * getName(NamePoolFile::nfTypes);
    unsigned getNameId(NamePoolFile::nfTypes);
    char * getNameById(NamePoolFile::nfTypes,unsigned id);
    vector<char *> getTWTriple();
    char * getNewJoinedTWTriple();
    
private:
    static NamePoolMgr *instance;
    NamePoolMgr();
    
    NamePool *n[6];

};

#endif
