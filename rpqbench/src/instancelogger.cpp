//
// C++ Implementation: InstanceLogger 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "instancelogger.h"

InstanceLogger *InstanceLogger::instance = 0L;

InstanceLogger::InstanceLogger() : logs()
{
}


InstanceLogger::~InstanceLogger()
{
}

InstanceLogger * InstanceLogger::getInstance()
{
    if(instance == 0L)
    {
        instance = new InstanceLogger();
    }
    
    return instance;
}

void InstanceLogger::inc(unsigned id)
{
    while(logs.size() <= id)
        logs.push_back(0);
        
    logs[id-1]++;
    
} //inc()

/**
 * stores all logged value to disk (log file) for specified year, resets all log values to 0
 * @param year year to write logs for
 */
void InstanceLogger::writeLogs(unsigned year)
{
char *fn = StringTools::numStr("log/rdftriplesums", year);

    FILE *f = fopen(fn, "w+");
    delete[] fn;
    
    for(unsigned i = 1; i <= logs.size(); i++)
    {
    char *idstr = StringTools::numStr("", i);
    char *cntstr = StringTools::numStr(" ", logs[i-1]);
    
        fputs(idstr, f);
        fputs(cntstr, f);
        fputs("\n", f);
        
        delete[] idstr;
        delete[] cntstr;
    }
    
    fclose(f);
    
} //writeLogs()

