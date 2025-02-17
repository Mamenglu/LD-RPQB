//
// C++ Interface: OutputLimitMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef OUTPUTLIMITMGR_H
#define OUTPUTLIMITMGR_H

#include "stdio.h"
#include <iostream>
#include <unistd.h>
#include "default.h"
#include "version.h"
#include "cmdline.h"
#include "stringtools.h"

using namespace std;

/**
@author Michael Schmidt, Christoph Pinkel
*/
class OutputLimitMgr{
public:
    OutputLimitMgr(CmdLine *);

    virtual ~OutputLimitMgr();
    bool outputComplete(unsigned long int=0, unsigned long int=0);
    void add(int,int);
    inline unsigned long int getTotalTriples() { return triples; }
    inline unsigned long int getTotalKB() { return full_kb; }

protected:
    CmdLine * cmd;
    unsigned long int triples;
    unsigned long int full_kb;
    int mod_bytes;
};

#endif
