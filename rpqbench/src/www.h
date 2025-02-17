//
// C++ Interface: Www 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef WWW_H
#define WWW_H

#include "document.h"

/**
Implements document type for web publications
*/
class Www : public Document
{

public:
    Www(unsigned,unsigned);
    virtual ~Www();

protected:

};

#endif // WWW_H
