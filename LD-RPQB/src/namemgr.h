//
// C++ Interface: NameMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef NAMEMGR_H
#define NAMEMGR_H

#include <iostream>
#include <cstdlib>


using namespace std;

/*
 * Singleton class for generating unique names
 * (assuming that the name associated with the indices are unique)
*/
class NameMgr {
public:
    static NameMgr* getInstance();
    static void initializeInstance(unsigned _list_size_firstnames,
                                unsigned _list_size_familynames);
    virtual ~NameMgr();

    void getFreshNameIds(unsigned& first_name_id,unsigned& family_name_id);
    inline unsigned long getNrUsedNames() { return name_ctr; }

private:
    static NameMgr* instance;
    NameMgr(unsigned _list_size_firstnames,
            unsigned _list_size_familynames);

    unsigned list_size;
    unsigned cur_first_name_id;
    unsigned cur_family_name_id;
    unsigned offset;

    bool consumed; // set to true if all ids have been consumed
    unsigned long int name_ctr; // current number of generated names
};

#endif // NAMEMGR_H
