//
// C++ Interface: InstanceLogger
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef INSTANCELOGGER_H
#define INSTANCELOGGER_H

#include "stringtools.h"

#include <vector>
#include <iostream>
#include <cstdio>


using namespace std;

/**
Singleton pattern class to help logging certain print-outs
@author Michael Schmidt, Christoph Pinkel
*/
class InstanceLogger
{
public:
    static InstanceLogger *getInstance();
    virtual ~InstanceLogger();

    void inc(unsigned);
    void writeLogs(unsigned);
    
private:
    static InstanceLogger *instance;
    InstanceLogger();
    
    vector <unsigned> logs;

};

#endif
