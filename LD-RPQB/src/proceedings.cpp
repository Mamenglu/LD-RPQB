//
// C++ Implementation: Proceedings 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "proceedings.h"

Proceedings::Proceedings(unsigned num, unsigned year)
    : Document(DOCTYPE_PROCEEDINGS, num, year)
{
}

Proceedings::~Proceedings()
{
}
