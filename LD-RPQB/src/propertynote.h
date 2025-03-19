//
// C++ Interface: PropertyNote
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_NOTE_H
#define PROPERTY_NOTE_H

#include "property.h"
#include "gaussiandistribution.h"

/**
Implements note property
*/
class PropertyNote : public Property
{

public:
    PropertyNote(RDFTriple *);
    virtual ~PropertyNote();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_NOTE_H

