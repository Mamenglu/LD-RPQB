//
// C++ Interface: NamePool 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef NAMEPOOL_H
#define NAMEPOOL_H

#include <iostream>
#include "namepoolfile.h"

using namespace std;

/**
Manages name lists, allows access to virtually random words

@author Michael Schmidt, Christoph Pinkel
*/
class NamePool
{
public:    
    NamePool(NamePoolFile::nfTypes,unsigned,unsigned);

    ~NamePool();
    char * getName();
    unsigned getNameId();
    char * getNameById(unsigned id);
	void cmpRealPos(NamePool *);
	unsigned getPos();
    
private:
    NamePoolFile::nfTypes type;
    unsigned pos;
    unsigned offset_inc;
    unsigned offset;
    NamePoolFile *npfi;
	unsigned run;

};

#endif
