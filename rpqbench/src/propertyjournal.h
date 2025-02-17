//
// C++ Interface: PropertyJournal
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_JOURNAL_H
#define PROPERTY_JOURNAL_H

#include "property.h"

/**
Implements journal property
*/
class PropertyJournal : public Property
{

public:
    PropertyJournal(RDFTriple *, RDFTriple *);
    virtual ~PropertyJournal();

protected:
    virtual bool calc();

private:
    RDFTriple *journal_triple;
};

#endif // PROPERTY_JOURNAL_H

