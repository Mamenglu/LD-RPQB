//
// C++ Interface: PropertyEditor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_EDITOR_H
#define PROPERTY_EDITOR_H

#include "property.h"

/**
Implements editor property
*/
class PropertyEditor : public Property
{

public:
    PropertyEditor(RDFTriple *, char *);
    virtual ~PropertyEditor();

protected:
    virtual bool calc();

    char *person_uri;
};

#endif // PROPERTY_EDITOR_H

