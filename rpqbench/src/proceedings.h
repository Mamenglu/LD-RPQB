//
// C++ Interface: Proceedings 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROCEEDINGS_H
#define PROCEEDINGS_H

#include "document.h"

/**
@author Michael Schmidt, Christoph Pinkel
Implements proceeding/conference d
*/
class Proceedings : public Document
{

public:
    Proceedings(unsigned,unsigned);
    virtual ~Proceedings();

protected:
};

#endif // PROCEEDINGS_H
