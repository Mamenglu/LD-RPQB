// C++ Implementation: Author
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "author.h"
#include "namemgr.h"

/**
 * Constructor
 * @param year year of first publication for this author
 */
Author::Author(unsigned year)
    : RDFTriple(), first_year(year), publication_cnt(0), coauth_cnt(0),
        retired_dist_coauth_cnt(0), publ_expect(0), orig_publ_expect(0),
        coauth_expect(0), dist_coauth_expect(0), co_authors()
{
	NameMgr::getInstance()->getFreshNameIds(given_name_id,last_name_id);
    addRelated(new PropertyAuthorName(this, given_name_id, last_name_id), true);
}


Author::~Author()
{
    for(unsigned i = 0; i < co_authors.size(); i++)
        co_authors[i]->retireCoAuthor(this);
}

/**
 * calculates author dc:creator triple
 */
bool Author::calc()
{
NamePoolMgr *npm = NamePoolMgr::getInstance();
const char *sstr = StringTools::concatStrs("_:",
            npm->getNameById(NamePoolFile::givenNames,given_name_id),
            "_",
            npm->getNameById(NamePoolFile::familyNames,last_name_id));

    RDFObject *o1 = new RDFObject(RDFObject::URIObj, sstr);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("foaf", "Person");
    setObjs(o1, o2, o3);
    
    delete[] sstr;

    return true;
}

void Author::setWithString(char* str)
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj, str);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("foaf", "Person");
    setObjs(o1, o2, o3);
    
    delete[] str;
}

/**
 * Creates and returns a pointer to a new RDFTriple, connecting the specified publication with
 * the author represented by this object.
 * @param publication publication triple
 * @return new triple connecting publication with author
 */
RDFTriple * Author::createPublicationRelationTriple(RDFTriple *publication)
{
RDFTriple *ret = new PropertyAuthor(publication,this);

    return ret;
} //createPublicationRelationTriple()


/**
 * Returns the total number of distinct co authors of this author
 * @return number of distinct co authors
 */
unsigned Author::distinctCoAuthors()
{
    return co_authors.size() + retired_dist_coauth_cnt;
    
} //distinctCoAuthors()

/**
 * Checks whether some other author is a co author of the author represented by
 * this Author object
 * @param test_author pointer to Author object to test
 * @return true if the tested author is already a co author, otherwise false
 */
bool Author::haveCoAuthor(Author *test_author)
{
    for(unsigned i = 0; i < co_authors.size(); i++)
        if(co_authors[i] == test_author)
            return true;

    return false;
} //haveCoAuthor()


/**
 * Adds specified author as co-author; whether this new author is a distinct co-author,
 * will be decided automatically
 * @param new_author pointer to Author object, representing the new co author
 */
void Author::addCoAuthor(Author *new_author)
{
    if(new_author == this)
        exit(10); //no cheating, please ;-)
        
    //check whether co author already exists...
    if(! haveCoAuthor(new_author))
    {
        co_authors.push_back(new_author);

        if(dist_coauth_expect)
            dist_coauth_expect--;
    }
    
    coauth_cnt++;

    if(coauth_expect)
        coauth_expect--;

} //addCoAuthor()


/**
 * Removes co author from list of (active) distinct co authors and adds one to the counter of
 * retired co authors of this author. This method is fail-safe and will do nothing if there is
 * no such co author listed.
 * @param retiring_author pointer to the Author object of the retiring author
 */
void Author::retireCoAuthor(Author *retiring_author)
{
    //finding author:
    for(unsigned i = 0; i < co_authors.size(); i++)
        if(co_authors[i] == retiring_author)
        {
            co_authors.erase(co_authors.begin() + i);
            retired_dist_coauth_cnt++;
        } //if

} //retireCoAuthor()


vector <Author *> Author::getCoAuthor()
{
    vector <Author *> ret;
    for(unsigned i = 0; i < co_authors.size(); i++)
        ret.push_back(co_authors[i]);
    return ret;

} //getCoAuthor()


/**
 * Adds a publication and decreases the number of remaining expected publications
 */
void Author::addPublication()
{
    publication_cnt++;
    if(publ_expect)
        publ_expect--;
} //retireCoAuthor()
