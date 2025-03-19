//
// C++ Implementation: ReferenceBagMgr
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "referencebagmgr.h"

ReferenceBagMgr* ReferenceBagMgr::instance = 0L;

ReferenceBagMgr * ReferenceBagMgr::getInstance()
{
    if(instance)
        return instance;
    else
    {
        instance = new ReferenceBagMgr();
        return instance;
    }
}

ReferenceBagMgr::ReferenceBagMgr()
    : next_num(0)
{
}

ReferenceBagMgr::~ReferenceBagMgr()
{
}

unsigned ReferenceBagMgr::getNext()
{
    return ++next_num;
}

