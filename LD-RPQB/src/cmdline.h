//
// C++ Interface: CmdLine 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef CMDLINE_H
#define CMDLINE_H

#include "default.h"
#include <iostream>

using namespace std;

class CmdLine {

public:
    CmdLine();
    virtual ~CmdLine();

    bool parse(int, char **);
    inline int getSizeType()  { return size_type;  }
    inline unsigned long int getSizeValue() { return size_value; }
    inline const char* getOutFileName() { return out_file.c_str(); }

private:
    int size_type;
    unsigned long int size_value;
    std::string out_file;
};

#endif // CMDLINE_H
