//
// C++ Implementation: PropertyNote
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertynote.h"

PropertyNote::PropertyNote(RDFTriple *main_triple) :
    Property(PROPERTY_NOTE, main_triple)
{
}


PropertyNote::~PropertyNote()
{
}


/*!
    \fn PropertyNote::calc()
 */
bool PropertyNote::calc()
{
GaussianDistribution g(1,10,1);
unsigned words = g.getRandomnizedValue();
vector <char *> word_vec;
unsigned total_size = 1;
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *note = 0L;

    //calculating note...
    for(unsigned i = 0; i < words; i++)
    {
    char *w = npm->getName(NamePoolFile::titleWords);
    
        word_vec.push_back(w);
        word_vec.push_back(" ");
        total_size += strlen(w) + 1;
    } //for
    
    note = new char[total_size];
    unsigned pos = 0;
    
    for(unsigned i = 0; i < word_vec.size() -1; i++)
    {
        strcpy(note + pos * sizeof(char), word_vec[i]);
        pos += strlen(word_vec[i]);
    } //for

    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("swrc", "note");
    RDFObject *o3 = new RDFObject(note);
    setObjs(o1, o2, o3);
    
    delete[] note;

    return true;
}
