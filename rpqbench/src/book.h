//
// C++ Interface: Book 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef BOOK_H
#define BOOK_H

#include "document.h"

/**
Implements document type book
*/
class Book : public Document
{

public:
    Book(unsigned, unsigned);
    virtual ~Book();

protected:    
};

#endif // BOOK_H
