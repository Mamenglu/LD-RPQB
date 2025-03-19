//
// C++ Implementation: MissingCites
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
//
#include "missingcites.h"

/**
 * Constructor
 */
MissingCites::MissingCites() : list(), cnt()
{
} //constructor

MissingCites::~MissingCites()
{
    for(unsigned i = 0; i < list.size(); i++)
        delete[] list[i];
} //destructor


/**
 * Returns a new copy of N URI's to cite and decreases their expected citation counts by one
 * @return newly created copies of URI (must get deleted, when used)
 */
vector <char *> MissingCites::citeSomeURIs(unsigned num)
{
vector <char *> ret;
unsigned idx = 0;
unsigned shift_step = 1; //step size in vector, when iterating
    //(possibly skipping items to get a mix of papers from every place in the pool)

    //now calculating a random shift step (if there is room for steps greater than 1):
    if(list.size())
    {
    int max_shift_step = list.size() / num - 1;

        if(max_shift_step > 1)
        {
            Randomnizer *rnd = Randomnizer::getInstance();
            shift_step = rnd->getRandomValue(max_shift_step - 1) + 1;
        }
    }
    
    while(num > 0 && list.size() > idx)
    {
    char * new_uri = new char[strlen(list[idx])+1];
    
        strcpy(new_uri, list[idx]);
        ret.push_back(new_uri);
        
        num--;
        cnt[idx]--;
    
        if(!cnt[idx]) //all expected cites are now in place
        {
            delete[] list[idx];
            list.erase(list.begin() + idx);
            cnt.erase(cnt.begin() + idx);

            while(completed_cnts.size() < orig_cnt[idx])
                completed_cnts.push_back(0);
            completed_cnts[orig_cnt[idx]-1]++;
            orig_cnt.erase(orig_cnt.begin() + idx);

        } //if
        
        idx += shift_step;
    
    } //while

    return ret;
    
} //citeSomeURI()

/**
 * Requests _cnt future incoming cites to _uri
 * @param _uri URI where the future cites should point to
 * @param _cnt number of expected citations
 */
void MissingCites::request(char *_uri, unsigned _cnt)
{
    if(! _cnt) return; //requests == 0 are invalid

    char *uri = new char[strlen(_uri) + 1];

    strcpy(uri, _uri);

    list.push_back(uri);
    cnt.push_back(_cnt);
    orig_cnt.push_back(_cnt);

} //request()

/**
 * Returns the number of papers that have received all their expected
 * (requested) incoming cites in the past, for those papers that have
 * requested cite_cnt incoming citations.
 * @param cite_cnt number of citations
 * @return number of papers with COMPLETE incoming citations and number of cites == cite_cnt
*/
unsigned MissingCites::historicPapersWithCites(unsigned cite_cnt)
{
    if(!cite_cnt || !completed_cnts.size() || cite_cnt>completed_cnts.size())
        return 0;

    return completed_cnts[cite_cnt-1];
} //historicPapersWithCites()

#ifdef LOGMODE
vector <unsigned> MissingCites::getIncomingCiteCounts()
{
vector <unsigned> ret = completed_cnts; //starting with historic figures

    //adding active ones:
    for(unsigned i = 0; i < cnt.size(); i++)
    {
    unsigned cite_num = orig_cnt[i] - cnt[i];
    
        if(cite_num > 0)
        {
            while(ret.size() < cite_num)
                ret.push_back(0);
                
            ret[cite_num-1]++;
        }

    } //for
    
    return ret;
    
} //getIncomingCiteCounts()
#endif
