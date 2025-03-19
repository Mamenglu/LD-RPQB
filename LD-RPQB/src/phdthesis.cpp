//
// C++ Implementation: Phdthesis 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "phdthesis.h"

Phdthesis::Phdthesis(unsigned num, unsigned year)
    : Document(DOCTYPE_PHDTHESIS, num, year)
{
}

Phdthesis::~Phdthesis()
{
}
