//
// C++ Implementation: Incollection 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "incollection.h"

Incollection::Incollection(unsigned num, unsigned year)
    : Document(DOCTYPE_INCOLLECTION, num, year)
{
}

Incollection::~Incollection()
{
}
