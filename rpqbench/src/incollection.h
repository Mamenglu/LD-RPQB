//
// C++ Interface: Incollection
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef INCOLLECTION_H
#define INCOLLECTION_H

#include "document.h"

/**
Implements document type InCollection
*/
class Incollection : public Document
{

public:
    Incollection(unsigned, unsigned);
    virtual ~Incollection();

protected:
};

#endif // INCOLLECTION_H
