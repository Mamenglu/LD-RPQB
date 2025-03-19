//
// C++ Implementation: RDFTriplePool
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "rdftriplepool.h"

/*!
    \fn RDFTriplePool::RDFTriplePool()
    default constructor
 */
RDFTriplePool::RDFTriplePool()
{
}

/*!
    \fn RDFTriplePool::RDFTriplePool()
    constructor
 */
RDFTriplePool::RDFTriplePool(vector <RDFTriple *> initial_triples)
{
    for(unsigned i = 0; i < initial_triples.size(); i++)
        pool.push_back(initial_triples[i]);
}


/*!
    \fn RDFTriplePool::~RDFTriplePool()
    destructor
 */
RDFTriplePool::~RDFTriplePool()
{
}


/*!
    \fn RDFTriplePool::count()
    @return number of items in pool
 */
unsigned RDFTriplePool::count()
{
    return pool.size();
} //count()


/*!
    \fn RDFTriplePool::add()
    Inserts triple into pool
 */
void RDFTriplePool::add(RDFTriple *new_element)
{
    pool.push_back(new_element);
} //add()

void RDFTriplePool::change(int index ,RDFTriple* rdf){
    pool[index] = rdf;
}

/*!
    \fn RDFTriplePool::getElement()
    @return a pointer to one random element from the pool or 0L if pool is empty
 */
RDFTriple * RDFTriplePool::getElement()
{
    if(pool.size() == 0) return 0L;
    return pool[0];    
} //getElement()

/*!
    \fn RDFTriplePool::getAt(unsigned)
    @return a pointer to the element at specified position, or 0L
 */
RDFTriple * RDFTriplePool::getAt(unsigned pos)
{
    if(pool.size() <= pos) return 0L;
    return pool[pos];
} //getat()


/*!
    \fn RDFTriplePool::printAll()
    @return a vector of char *'s, containing print() lines for all elements in the pool.
    Please note, that print() line char *'s are new'ly created and need to get deleted
    by caller.
 */
vector<char *> RDFTriplePool::printAll()
{
vector <char *> ret;

    for(unsigned i = 0; i < pool.size(); i++)
        ret.push_back(pool[i]->print());

    return ret;
} //printAll()

/*!
    \fn RDFTriplePool::uncalcAll()
    unfolds all triples in the pool
*/
void RDFTriplePool::uncalcAll() {
    for(unsigned i = 0; i < pool.size(); i++)
        pool[i]->uncalc();
}

/*!
    \fn RDFTriplePool::removeElement()
    @return removes specified element from the pool
 */
void RDFTriplePool::removeElement(RDFTriple *rm_el)
{
    for(unsigned i = 0; i < pool.size(); i++)
        if(pool[i] == rm_el)
        {
            pool.erase(pool.begin() + i, pool.begin() + i+1);
            break;
        }
} //removeElement()

void RDFTriplePool::removeAllElement()
{

    // pool.erase(pool.begin(), pool.begin());
    pool.clear();

} //removeElement()


/*!
    \fn RDFTriplePool::totalSize()
    @return returns the expected size (in bytes) for the print() lines of all elements in the pool
 */
unsigned long RDFTriplePool::totalSize()
{
unsigned long ret = 0;

    for(unsigned i = 0; i < pool.size(); i++)
        ret += pool[i]->getSize() + 1;
    
    return ret;
} //totalSize()

/*!
    \fn RDFTriplePool::destroyElements()
    Deletes all elements in the pool (by deleting the objects
   they are pointing to)
 */
void RDFTriplePool::destroyElements()
{
    for(unsigned i = 0; i < pool.size(); i++)
        delete pool[i];
        
    pool.erase(pool.begin(), pool.end());
}

/**
 * adds all elements from specified pool into this pool
 */
void RDFTriplePool::addPool(RDFTriplePool *triple_pool)
{
vector <RDFTriple *> *v_ptr = triple_pool->vPtr();

    for(unsigned i = 0; i < v_ptr->size(); i++)
        pool.push_back((*v_ptr)[i]);
        
} //destroyElements()
