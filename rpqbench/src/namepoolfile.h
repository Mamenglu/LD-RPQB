//
// C++ Interface: NamePoolFile 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef NAMEPOOLFILE_H
#define NAMEPOOLFILE_H

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/**
Singleton pattern class to handle access to data from some names file

@author Michael Schmidt, Christoph Pinkel
*/
class NamePoolFile
{
public:
    enum nfTypes
    {
        givenNames = 0,
        familyNames = 1,
        titleWords = 2
    };

    static NamePoolFile *getInstance(nfTypes);
    ~NamePoolFile();
    
    char *getLine(unsigned);
    unsigned getSize() { return names.size(); }

private:
    static NamePoolFile *instance0;
    static NamePoolFile *instance1;
    static NamePoolFile *instance2;
    
    NamePoolFile(nfTypes);
    
    vector<char *> names;
};

#endif
