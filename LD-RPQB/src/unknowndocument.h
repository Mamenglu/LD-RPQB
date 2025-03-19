//
// C++ Interface: UnknownDocument 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef UNKNOWNDOCUMENT_H
#define UNKNOWNDOCUMENT_H

#include "rdftriple.h"
#include "unknowndocmgr.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class UnknownDocument : public RDFTriple
{
public:
    UnknownDocument();

    virtual ~UnknownDocument();

protected:
    bool calc();
    
private:
    char * uri;
};

#endif
