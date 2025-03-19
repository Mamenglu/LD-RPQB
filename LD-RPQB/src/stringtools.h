//
// C++ Interface: StringTools 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include "string.h"

/**
Implementing some string manipulation functions

@author Michael Schmidt, Christoph Pinkel
*/
class StringTools
{
public:
    StringTools();

    virtual ~StringTools();
    
    static char * concatStrs(char *, char *, char * = 0L, char * = 0L);
    static char * numStr(const char *, unsigned);

};

#endif
