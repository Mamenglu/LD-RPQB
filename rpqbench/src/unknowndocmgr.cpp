//
// C++ Implementation: UnknownDocMgr
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "unknowndocmgr.h"

UnknownDocMgr* UnknownDocMgr::instance = 0L;

UnknownDocMgr * UnknownDocMgr::getInstance()
{
    if(instance)
        return instance;
    else
    {
        instance = new UnknownDocMgr();
        return instance;
    }
}

UnknownDocMgr::UnknownDocMgr()
    : next_num(0)
{
}

UnknownDocMgr::~UnknownDocMgr()
{
}

char * UnknownDocMgr::getNext()
{
char *uri = new char[45];

    char * tmp_uri = StringTools::numStr("<http://localhost/misc/UnknownDocument", ++next_num);
    
    strcpy(uri, tmp_uri);
    unsigned len = strlen(tmp_uri);
    
    uri[len + 1] = 0;
    uri[len] = '>';
    
    delete[] tmp_uri;
    
    return uri;
}
