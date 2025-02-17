//
// C++ Implementation: PropertyAbstract 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertyabstract.h"

PropertyAbstract::PropertyAbstract(RDFTriple *main_triple) :
    Property(PROPERTY_ABSTRACT, main_triple)
{
}


PropertyAbstract::~PropertyAbstract()
{
}


/*!
    \fn PropertyAbstract::calc()
 */
bool PropertyAbstract::calc()
{
GaussianDistribution g(1,150,30);
unsigned words = g.getRandomnizedValue();
vector <char *> word_vec;
unsigned total_size = 1;
NamePoolMgr *npm = NamePoolMgr::getInstance();
char *abstract = 0L;

    //calculating abstract...
    for(unsigned i = 0; i < words; i++)
    {
    char *w = npm->getName(NamePoolFile::titleWords);
    
        word_vec.push_back(w);
        word_vec.push_back(" ");
        total_size += strlen(w) + 1;
    } //for
    
    abstract = new char[total_size];
    unsigned pos = 0;
    
    for(unsigned i = 0; i < word_vec.size() -1; i++)
    {
        strcpy(abstract + pos * sizeof(char), word_vec[i]);
        pos += strlen(word_vec[i]);
    } //for
    
    //updating...
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("bench", "abstract");
    RDFObject *o3 = new RDFObject(abstract);
    setObjs(o1, o2, o3);

    delete[] abstract;
    return true;
}
