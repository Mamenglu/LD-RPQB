//
// C++ Implementation: RDFTriple
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "rdftriple.h"

RDFTriple::RDFTriple()
    : is_inited(false), is_changed(false), is_complete(false),
        is_printed(false), t_size(-1)
{
    for(unsigned i = 0; i < 5; i++)
        require[i] = false;
        
    #ifdef LOGMODE
    logid = 0;
    #endif
} //constructor


RDFTriple::~RDFTriple()
{
    for(unsigned i = 0; i < explicit_relations.size(); i++)
        if(existential_relations[i])
            delete explicit_relations[i];
            
    while(t_obj.size() > 0)
    {
        delete t_obj[t_obj.size()-1];
        t_obj.pop_back();
    }
}

int RDFTriple::getSize()
{
    if(is_changed || !is_complete)
        update();

    return t_size;
}

/*!
    \fn RDFTriple::print()
    This method produces the RDF triple output for this object.
    Please note, that a fresh char array is being allocated, so the
    returned pointer needs to be deleted later...
    @return a new string, containing the triple code.
 */
char * RDFTriple::print()
{
    if(is_changed || !is_complete)
        update();
        
    if(!is_complete || is_printed)
    { //still nothing/update failed?

        char * ret = new char[1];
        ret[0] = 0;
        return ret;
    }

    char * ret = new char[t_size + 1];
    
    int startpos = 0;

    strncpy(ret + startpos * sizeof(char),
        t_obj[0]->getString(), t_obj[0]->size());
    startpos += t_obj[0]->size();

    ret[startpos] = ' ';
    startpos++;

    strncpy(ret + startpos * sizeof(char),
        t_obj[1]->getString(), t_obj[1]->size());
    startpos += t_obj[1]->size();
    
    ret[startpos] = ' ';
    startpos++;
    
    strncpy(ret + startpos * sizeof(char),
        t_obj[2]->getString(), t_obj[2]->size());
    startpos += t_obj[2]->size();
    
    ret[startpos] = '.';
    startpos++;
    
    ret[startpos] = 0; //0 terminator

    is_printed = true;
    
    #ifdef LOGMODE
    if(logid)
    {
        InstanceLogger *l = InstanceLogger::getInstance();
        l->inc(logid);
    }
    #endif
    
    return ret;

} //print()

/**
 * Sets the RDF objects (URI's etc) as specified (requires new RDFObject's which
 * will get deleted whith this object instance
 * @param o1 
 * @param o2 
 * @param o3 
 */
void RDFTriple::setObjs(RDFObject *o1, RDFObject *o2, RDFObject *o3)
{
    while(t_obj.size() > 0)
    {
        delete t_obj[t_obj.size()-1];
        t_obj.pop_back();
    }
    
    t_obj.push_back(o1);
    t_obj.push_back(o2);
    t_obj.push_back(o3);
    is_changed = 1;
}


/*!
    \fn RDFTriple::update()
 */
void RDFTriple::update()
{
    if(! calc() )
        return;

    is_complete = 1;
    is_changed = 0;
    t_size = 3;

    for(int i = 0; i < 3; i++)
    {
        t_size += t_obj[i]->size();
    }
    
} //update()

/*!
    \fn RDFTriple::uncalc()
    folds the triple again (i.e. removes its objects etc)
 */
void RDFTriple::uncalc() {

    // uncalculate related triples
    for (unsigned i=0;i<explicit_relations.size(); i++) {
        explicit_relations[i]->uncalc();
    }

    // uncalculate this triple
    for (unsigned i=0;i<t_obj.size();i++) {
        delete t_obj[i];
    }
    t_obj.clear();
    t_size=0;

    is_complete=0; // ???
}


/*!
    \fn RDFTriple::getRelated()
    @return a pointer to the vector of explicitly related triples (usually attributes)
 */
vector <RDFTriple *> * RDFTriple::getRelated()
{
    return &explicit_relations;
} //getRelated()

void RDFTriple::removeRelated(unsigned i)
{
    explicit_relations.erase(explicit_relations.begin()+i);
    // return &explicit_relations;
} //getRelated()

/*!
    \fn RDFTriple::recursivePool()
    Recursively finds pointers to this triple and all explicitly related triples that
    have not yet been printed
    @return 0L terminated array of RDFTriple pointers
 */
vector <RDFTriple *> RDFTriple::recursivePool()
{
vector <RDFTriple *> ret;

    if(! is_printed)
    {
        ret.push_back(this);
    }
    
    if(! is_inited)
            init();

    for(unsigned i = 0; i < explicit_relations.size(); i++)
    {
        vector <RDFTriple *> sub_vec = explicit_relations[i]->recursivePool();
        for(unsigned ii = 0; ii < sub_vec.size(); ii++)
            ret.push_back(sub_vec[ii]);
    } //for
    
    return ret;
}

/**
 * Adds a related triple
 * @param new_relation 
 * @param is_existential 
 */
void RDFTriple::addRelated(RDFTriple *new_relation, bool is_existential)
{
    explicit_relations.push_back(new_relation);
    existential_relations.push_back(is_existential);
} //addRelated()


/*!
    \fn RDFTriple::getSubjectPtr()
 */
RDFObject * RDFTriple::getSubjectPtr()
{
    if(is_changed || !is_complete)
        update();

    return t_obj[0];
}

//获得谓语
RDFObject * RDFTriple::getPrePtr()
{
    if(is_changed || !is_complete)
        update();

    return t_obj[1];
}

//获得宾语
RDFObject * RDFTriple::getObjPtr()
{
    if(is_changed || !is_complete)
        update();

    return t_obj[2];
}
