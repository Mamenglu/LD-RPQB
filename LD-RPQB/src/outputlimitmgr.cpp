//
// C++ Implementation: OutputLimitMgr 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
//
#include "outputlimitmgr.h"
#include <time.h>
#include <sys/time.h>

OutputLimitMgr::OutputLimitMgr(CmdLine *_cmd)
    : cmd(_cmd), triples(0), full_kb(0), mod_bytes(0)
{
}


OutputLimitMgr::~OutputLimitMgr()
{
}

/*!
    \fn OutputLimitMgr::outputComplete(unsigned long int=0, unsigned long int=0)
 */
bool OutputLimitMgr::outputComplete(unsigned long int additional_triples,
    unsigned long int additional_bytes)
{
    if(cmd->getSizeType() == SIZE_TYPE_TRIPLES)
    {
        if(cmd->getSizeValue() > triples + additional_triples)
            return false;
        else
            return true;
    }
    else
    {
        if(cmd->getSizeValue() > full_kb + additional_bytes / 1024)
            return false;
        else
            return true;
        return false;
    }
}


/*!
    \fn OutputLimitMgr::add(int,int)
 */
void OutputLimitMgr::add(int _triples, int bytes)
{
    bytes += mod_bytes;
    full_kb += bytes/1024;
    mod_bytes = bytes % 1024;
    
    triples += _triples;
}
