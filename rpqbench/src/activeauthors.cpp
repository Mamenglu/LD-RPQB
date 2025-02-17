//
// C++ Implementation: ActiveAuthors
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "activeauthors.h"

ActiveAuthors::ActiveAuthors() : pool(new vector <Author *>), retired(0), retired_pubs(0),
    retired_coauth_sum(0), retired_d_coauth_sum(0)
{
}


ActiveAuthors::~ActiveAuthors()
{
    for(unsigned i = 0; i < pool->size(); i++)
        delete (*pool)[i];
    delete pool;
}

/**
 * Draws num existing authors from pool.
 * @param num number of Author objects to retrieve
 * @return vector of Author objects
 */
vector<Author *> ActiveAuthors::draw(unsigned num)
{
vector <Author *> ret;
Randomnizer *r = Randomnizer::getInstance();

    //making sure that we won't draw more authors than we have
    if(num > pool->size())
        num = pool->size();

    //can return right now if we're looking for 0 new authors...
    if(num == 0) return ret;
    
    //drawing exisiting authors with some randomized aspects...
    unsigned offset = r->getRandomValue(pool->size());
    unsigned max_spacing = pool->size()/(num+1);
    unsigned spacing = r->getRandomValue(max_spacing+1); //returns max value input_param-1
    unsigned cnt = 0;
    
    for(unsigned i = offset; cnt < num; i+= spacing + 1)
    {
        //rotating (could be needed when using high offset)
        if(i >= pool->size()) i = i % pool->size();
        
        ret.push_back((*pool)[i]);
    
        cnt++;
    } //for
    
    return ret;

} //newAuths()

/**
 * Creates a new Author object, adds it to the pool of existing authors of all
 * and returns a copy of the new object.
 * @param year the current year (year of 1st publication of new author)
 * @return vector of Author objects
 */
Author * ActiveAuthors::newAuthor(unsigned year)
{
Author *ret = new Author(year);

    pool->push_back(ret);
    return ret;
} //newAuths()

/**
 * Adds num new authors into Author vector reference
 * @param num number of authors to add into vector
 * @param vec_ref reference to vector of authors (to complement)
 */
void ActiveAuthors::insertNew(unsigned num, vector<Author *> &vec_ref, unsigned year)
{
    for(unsigned i = 0; i < num; i++)
        vec_ref.push_back(newAuthor(year));
} //insertNew()


/**
 * Lets cnt authors retire.
 * @param cnt number of authors to retire
 */
void ActiveAuthors::retire(unsigned cnt)
{
    //make sure we don't let retire more authors than we have ;-)
    if(cnt > pool->size())
        cnt = pool->size();

    for(unsigned i = 0; i < cnt; i++)
    {
        #ifdef LOGMODE
        retired_coauth_sum += (*pool)[i]->coAuthors();
        retired_d_coauth_sum += (*pool)[i]->distinctCoAuthors();
        #endif
        
        retired_pubs += (*pool)[i]->publications();
        delete (*pool)[i];
        retired++;
    } //for
    
    if(cnt) pool->erase(pool->begin(), pool->begin() + cnt);
    
} //retire()



/**
 * Returns a vector of pointers to Author objects with the specified count of publications
 * each. If not enough authors with the desired criteria are known among the active authors,
 * a smaller number will be returned.
 * @param auth_num number of authors to return in vector
 * @param publication_num number of publications for each of those authors
 * @return vector containing the retrieved Author objects
 */
vector<Author *> ActiveAuthors::getMAuthorsWithNPublications(unsigned auth_num,
    unsigned publication_num)
{
vector<Author *> ret;
//strcmp
    for(unsigned i = 0; i < pool->size() && ret.size() < auth_num; i++)
        if((*pool)[i]->publications() == publication_num)
            ret.push_back((*pool)[i]);

    /*
    cout << "###############DEBUG" << endl;
    for (unsigned i=0;i<ret.size();i++) {
        cout << "author=" << ret[i] << endl;
    }
    */
    return ret;
    
} //getMAuthorsWithNPublications

void ActiveAuthors::uncalc() {
    for (unsigned i=0;i<pool->size();i++) {
        (*pool)[i]->uncalc();
    }
}


#ifdef LOGMODE
/*
 * Returns the average of co authors for all active authors (life time numbers,
 * including authors that already have retired)
 * @return avg number of co authors
 */
float ActiveAuthors::averageCoAuthors()
{
unsigned cnt =  retired + count();
unsigned ca_sum = retired_coauth_sum;

    //for
    for(unsigned i = 0; i < count(); i++)
        ca_sum += (*pool)[i]->coAuthors();
        
    return (float)((double)ca_sum / (double)cnt);

} //averageCoAuthors()
    

/**
 * Returns the average of distinct co authors for all active authors (life time numbers,
 * including those authors that already have retired)
 * @return avg number of distinct co authors
 */
float ActiveAuthors::averageDistinctCoAuthors()
{
unsigned cnt =  retired + count();
unsigned dca_sum = retired_d_coauth_sum;

    //for
    for(unsigned i = 0; i < count(); i++)
        dca_sum += (*pool)[i]->distinctCoAuthors();
        
    return (float)((double)dca_sum / (double)cnt);
} //averageDistinctCoAuthors()

#endif
