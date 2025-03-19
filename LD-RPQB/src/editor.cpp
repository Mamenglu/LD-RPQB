//
// C++ Implementation: Editor
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "editor.h"

Editor::Editor(Author *author, bool is_dummy_author)
    : person_uri(0L), dummy_author(0L)
{
person_uri = new char[strlen(author->getSubjectPtr()->getString())+1];

    strcpy(person_uri, author->getSubjectPtr()->getString());
    
    if(is_dummy_author) //dummy authors must be deleted with destructor
        //and require a triple relation to each relation triple created from this editor
        dummy_author = author;
}


Editor::~Editor()
{
    delete[] person_uri;
    
    if(dummy_author)
        delete dummy_author;
}


/**
 * Calculates a new triple (from PropertyEditor) which relates specified document to editor
 * @param main_triple RDFTriple representing the document to relate with the editor
 * @return triple containing relation to editor
 */
RDFTriple * Editor::getRelationTriple(RDFTriple *main_triple)
{
PropertyEditor *ret = new PropertyEditor(main_triple, person_uri);

    if(dummy_author)
        ret->addRelated(dummy_author, false);
    
    return ret;

} //getRelationTriple()


// msc
//char*  Editor::getEditorName() {
//    return dummy_author->getAuthorName();
//}
