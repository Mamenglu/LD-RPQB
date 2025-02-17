//
// C++ Implementation: PropertyEditor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyeditor.h"

/**
 * Constructor
 * @param main_triple RDFTriple pointer to document
 * @param person_uri string containing the URI of the related person (editor)
 */
PropertyEditor::PropertyEditor(RDFTriple *main_triple, char *_person_uri) :
    Property(PROPERTY_EDITOR, main_triple), person_uri(0L)
{
person_uri = new char[strlen(_person_uri)+1];

    strcpy(person_uri, _person_uri);
}


PropertyEditor::~PropertyEditor()
{
    delete[] person_uri;
}

/**
 * Calculates the editor relation triple
 * @return success
 */
bool PropertyEditor::calc()
{
    #ifdef LOGMODE
    setLogId(LOGID_AUTHOR);
    #endif

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "editor");
    RDFObject *o3 = new RDFObject(RDFObject::URIObj, person_uri);
    setObjs(o1, o2, o3);

    return true;
} //calc()
