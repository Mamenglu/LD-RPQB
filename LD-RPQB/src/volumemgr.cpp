//
// C++ Implementation: VolumeMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "volumemgr.h"

VolumeMgr* VolumeMgr::instance = 0L;

/**
 * Retrieves singleton pattern class instance
 * @return singleton pattern instance
 */
VolumeMgr* VolumeMgr::getInstance()
{
    
    if(instance == 0L)
        instance = new VolumeMgr();

    return instance;
}

VolumeMgr::VolumeMgr()
{
}


VolumeMgr::~VolumeMgr()
{
}

/**
 * @param type type of document to get volume for (0 = journal, 1 = conference, 2 = book)
 * @param id id (number) of document to retrieve the active (or next) volume number for
 * @param year the current year
 * @return active (could be: next) volume number for specified document
 */
unsigned VolumeMgr::getVol(unsigned type, unsigned id, unsigned year)
{
    if(type != 0 && type != 1 && type != 2) abort();
    
    //making sure, vector is extended at least as far as the journal in question;
    //initializing new elements with pre-initial volume number 0, current year 0,
    //pre-first number in volume to 0
    while(cnt[type].size() <= id)
    {
        cnt[type].push_back(0);
        last_vol_yr[type].push_back(0);
        vol_num[type].push_back(0);
    }
    
    if(last_vol_yr[type][id] < year)
    { //new year, need new vol number
        cnt[type][id]++;
        last_vol_yr[type][id] = year;
        vol_num[type][id] = 0;
    }
    
    return cnt[type][id];
    
} //getVol()


/**
 * Calculates the next number within a volume.
 * @param type type of document to get a number for (0 = journal, 1 = conference)
 * @param id id (number) of document to retrieve the number
 * @param year the current year
 * @return next number
 */
unsigned VolumeMgr::nextNumber(unsigned type, unsigned id, unsigned year)
{
    if(type != 0 && type != 1) abort();
    
    getVol(type, id, year); //make sure that array is well initialized
    return ++vol_num[type][id];
} //nextNumber()
