//
// C++ Interface: Editor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef EDITOR_H
#define EDITOR_H

#include "author.h"
#include "propertyeditor.h"

/**
Implements editors
@author Michael Schmidt, Christoph Pinkel
*/
class Editor
{
public:
    Editor(Author *, bool=false);

    virtual ~Editor();
    
    RDFTriple *getRelationTriple(RDFTriple *);
    //char* getEditorName();
    
protected:
    char *person_uri;
    Author *dummy_author;
};

#endif
