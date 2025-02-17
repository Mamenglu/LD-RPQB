//
// C++ Interface: Mastersthesis 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef MASTERSTHESIS_H
#define MASTERSTHESIS_H

#include "document.h"

/**
* Implements document type "masters thesis"
*/
class Mastersthesis : public Document
{

public:
    Mastersthesis(unsigned,unsigned);
    virtual ~Mastersthesis();

protected:
};

#endif // MASTERSTHESIS_H
