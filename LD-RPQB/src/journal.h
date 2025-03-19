//
// C++ Interface: Journal
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef JOURNAL_H
#define JOURNAL_H

#include "document.h"

/**
Implements document type journal

@author Michael Schmidt, Christoph Pinkel
*/
class Journal : public Document
{
public:
    Journal(unsigned,unsigned);

    virtual ~Journal();
};

#endif
