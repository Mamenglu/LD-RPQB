//
// C++ Implementation: NamePoolMgr
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "namepoolmgr.h"

NamePoolMgr* NamePoolMgr::instance = 0L;

NamePoolMgr::NamePoolMgr()
{
    n[0] = new NamePool(NamePoolFile::givenNames,0,0);
    n[1] = new NamePool(NamePoolFile::familyNames,0,1);
    
    n[2] = new NamePool(NamePoolFile::titleWords,0,0);
    n[3] = new NamePool(NamePoolFile::titleWords,2,1);
    n[4] = new NamePool(NamePoolFile::titleWords,4,3);
    n[5] = new NamePool(NamePoolFile::titleWords,5,4);
}


NamePoolMgr::~NamePoolMgr()
{
    for(unsigned i = 0; i < 6; i++)
        delete n[i];
}

/**
 * Retrieves instance of singleton pattern class
 * @return singleton pattern instance
 */
NamePoolMgr * NamePoolMgr::getInstance()
{
    if(instance == 0L)
    {
        instance = new NamePoolMgr();
    }
    
    return instance;
    
} //getInstamce()


/*!
    \fn NamePoolMgr::getName()
    Retrieves a name. Please note that returned names will be used again and should therefore
    not get altered or deleted.
    @param type type of requested name
    @return pointer to an existing name of requested type (char *)
 */
char * NamePoolMgr::getName(NamePoolFile::nfTypes type)
{
    switch(type)
    {
        case NamePoolFile::givenNames:
			n[0]->cmpRealPos(n[1]);
            return n[0]->getName();
            break;
            
        case NamePoolFile::familyNames:
			n[1]->cmpRealPos(n[0]);
            return n[1]->getName();
            break;
            
        case NamePoolFile::titleWords:
            return n[2]->getName();
            break;
                
        default:
            cout << "name type error." << endl;
            exit(5);
            break;
    }
}

// returns the id of the current name
unsigned NamePoolMgr::getNameId(NamePoolFile::nfTypes type)
{
    switch(type)
    {
        case NamePoolFile::givenNames:
            return n[0]->getNameId();
            break;
            
        case NamePoolFile::familyNames:
            return n[1]->getNameId();
            break;
            
        case NamePoolFile::titleWords:
            return n[2]->getNameId();
            break;
                
        default:
            cout << "name type error." << endl;
            exit(5);
            break;
    }
}

// returns the pointer id points to (not a copy!)
char* NamePoolMgr::getNameById(NamePoolFile::nfTypes type, unsigned id)
{
    switch(type)
    {
        case NamePoolFile::givenNames:
            return n[0]->getNameById(id);
            break;
            
        case NamePoolFile::familyNames:
            return n[1]->getNameById(id);
            break;
            
        case NamePoolFile::titleWords:
            return n[2]->getNameById(id);
            break;
                
        default:
            cout << "name type error." << endl;
            exit(5);
            break;
    }
}


/*!
    \fn NamePoolMgr::getTWTriple()
    Retrieves three names of type titleword.
    Please note that returned names will be used again and should therefore
    not get altered or deleted.
    @return vector filled with three names
 */
vector<char *> NamePoolMgr::getTWTriple()
{
vector <char *> ret;

    ret.push_back(n[3]->getName());
    ret.push_back(n[4]->getName());
    ret.push_back(n[5]->getName());

    return ret;
}

/*!
    \fn NamePoolMgr::getNewJoinedTWTriple()
    Retrieves three names of type titleword, joined together in one string (separated
    by spaces).
    Please note that this returned string is a newly created copy of the names
    and NEEDS TO BE DELETED.
    @return joined string
 */
char * NamePoolMgr::getNewJoinedTWTriple()
{
char * ret;
vector <char *> strs = getTWTriple();

    ret = new char[strlen(strs[0]) + strlen(strs[1]) + strlen(strs[2]) + 3];
    
    strcpy(ret, strs[0]);
    ret[strlen(strs[0])] = ' ';
    
    strcpy(ret + (strlen(strs[0]) + 1) * sizeof(char), strs[1]);
    ret[strlen(strs[0]) + strlen(strs[1]) + 1] = ' ';
    
    strcpy(ret + (strlen(strs[0]) + strlen(strs[1]) + 2) * sizeof(char), strs[2]);

    return ret;
}
