//
// C++ Implementation: Journal
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "journal.h"

Journal::Journal(unsigned num, unsigned year)
    : Document(DOCTYPE_JOURNAL, num, year)
{
}


Journal::~Journal()
{
}

