//
// C++ Implementation: Property
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "namemgr.h"

// the one and only instance
NameMgr* NameMgr::instance=0L;

/*
 * get an instance (must have been initialized before)
*/
NameMgr* NameMgr::getInstance() {
    if (instance==0L) {
        cout << "Name Manager not initialized, please call the "
                << "NameMgr::initializeInstance(unsigned,unsigned) before"
                << "using the class for the first time!" << endl;
        abort();
    }
    return instance;
}

/*
 * initialize an instance of the name mgr,
 * requires the size of the first and family name lists;
 * these list must be of equal length (checked internally)
*/
void NameMgr::initializeInstance(unsigned _list_size_firstnames,
                                    unsigned _list_size_familynames) {
    if (instance!=0L) {
        cout << "Name Manager already initialized!";
        abort();
    } else {
        instance=new NameMgr(_list_size_firstnames,_list_size_familynames);
    }
}

/*
 * destructor
*/
NameMgr::~NameMgr() {
    delete instance;
}

/*
 * Constructor
*/
NameMgr::NameMgr(unsigned _list_size_firstnames,
                    unsigned _list_size_familynames)
    : list_size(0), cur_first_name_id(0), cur_family_name_id(0),
        offset(0), consumed(false), name_ctr(0) {
    if (_list_size_firstnames!=_list_size_familynames ||
        _list_size_firstnames==0) {
        cout << "First and family names lists must be of equal length "
                << "and larger than 0, you passed: firstnames="
                << _list_size_firstnames << ", familynames="
                << _list_size_familynames << "!" << endl;
        abort();
    }
    list_size=_list_size_firstnames;
}

/*
 * compute a fresh pair of name ids
*/
void NameMgr::getFreshNameIds(unsigned& first_name_id,    
                                unsigned& family_name_id) {
    if (consumed) {
        cout << "All names have been consumed. Please increase "
                << "length of first and family name lists (by the same "
                << "number of) unique names to generate larger documents"
                << " (number of generated names=" << name_ctr << ")!"
                << endl;
        abort();
    }

    first_name_id=cur_first_name_id;
    family_name_id=cur_family_name_id;
    name_ctr++;

    if (cur_first_name_id==list_size-1) {
        offset++;
        offset%=list_size;
        if (offset==0) {
            consumed=true;
        }
        cur_first_name_id=0;
        cur_family_name_id=offset;
    } else {
        cur_first_name_id++;
        cur_family_name_id++;
        cur_family_name_id%=list_size;
    }
}
