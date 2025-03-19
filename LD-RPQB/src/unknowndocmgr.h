//
// C++ Interface: UnknownDocMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef UNKNOWNDOCMGR_H
#define UNKNOWNDOCMGR_H

#include "stringtools.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class UnknownDocMgr
{
public:
    ~UnknownDocMgr();

    static UnknownDocMgr * getInstance();
    
    char * getNext();
    
private:
    UnknownDocMgr();
    static UnknownDocMgr *instance;
    
    unsigned next_num;
};

#endif
