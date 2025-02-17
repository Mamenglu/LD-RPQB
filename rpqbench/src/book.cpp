//
// C++ Implementation: Book 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "book.h"

Book::Book(unsigned num, unsigned year)
    : Document(DOCTYPE_BOOK, num, year)
{
}

Book::~Book()
{
}
