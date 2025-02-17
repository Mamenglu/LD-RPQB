//
// C++ Interface: VolumeMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef VOLUMEMGR_H
#define VOLUMEMGR_H

#include <cstdlib>
#include <vector>
using namespace std;

/**
Singleton pattern class to generate subsequent volume numbers

@author Michael Schmidt, Christoph Pinkel
*/

class VolumeMgr
{
public:
    static VolumeMgr * getInstance();

    virtual ~VolumeMgr();
    
    unsigned getVol(unsigned,unsigned,unsigned);
    unsigned nextNumber(unsigned,unsigned,unsigned);

private:
    static VolumeMgr *instance;
    VolumeMgr();
    
    vector<unsigned> cnt[3], last_vol_yr[3], vol_num[3];
};

#endif
