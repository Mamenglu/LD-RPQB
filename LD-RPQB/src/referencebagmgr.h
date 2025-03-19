//
// C++ Interface: ReferenceBagMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef REFERENCEBAGMGR_H
#define REFERENCEBAGMGR_H

/**
@author Michael Schmidt, Christoph Pinkel
*/
class ReferenceBagMgr
{
public:
    ~ReferenceBagMgr();

    static ReferenceBagMgr * getInstance();
    
    unsigned getNext();
    
private:
    ReferenceBagMgr();
    static ReferenceBagMgr *instance;
    
    unsigned next_num;
};

#endif
