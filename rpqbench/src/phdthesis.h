//
// C++ Interface: Phdthesis 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PHDTHESIS_H
#define PHDTHESIS_H

#include "document.h"

/**
Implements document type Phd thesis
*/
class Phdthesis : public Document
{

public:
    Phdthesis(unsigned,unsigned);
    virtual ~Phdthesis();

protected:    
};

#endif // PHDTHESIS_H
