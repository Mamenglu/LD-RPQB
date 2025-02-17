//
// C++ Interface: PropertyChapter
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_CHAPTER_H
#define PROPERTY_CHAPTER_H

#include "property.h"
#include "randomnizer.h"

/**
Implements chapter property
*/
class PropertyChapter : public Property
{

public:
    PropertyChapter(RDFTriple *);
    virtual ~PropertyChapter();

private:

protected:
    virtual bool calc();
};

#endif // PROPERTY_CHAPTER_H

