//
// C++ Interface: Publishers 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PUBLISHERS_H
#define PUBLISHERS_H

/**
Class containing a list of publishers (Singleton)
*/
class Publishers 
{
public:
    static Publishers* getInstance();
    virtual ~Publishers();

    const char* getRandomPublisher();

private:
    static Publishers* instance;
    Publishers();

    static char* publishers[];

};

#endif // PUBLISHERS_H
