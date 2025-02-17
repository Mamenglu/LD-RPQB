//
// C++ Interface: RDFObject
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RDFOBJECT_H
#define RDFOBJECT_H

#include <string.h>

/**
@author Michael Schmidt, Christoph Pinkel
*/
class RDFObject
{
public:
    enum oType
    {
        URIObj = 0,
        AbbrObj = 1,
        ConstObj = 2
    };
    
    RDFObject(oType, const char *);
    RDFObject(const char *, const char *, bool);
    RDFObject(const char *, const char *);
    RDFObject(const char *, unsigned=0);
    
    virtual ~RDFObject();
    
    /**
     * @return object information as string (char *)
     */
    inline char * getString() { return str; }

    /*!
    \fn RDFObject::size()
    */
    unsigned size() { return str_length; }
    
    
private:
    oType type;
    char *str;
    unsigned str_length;
};

#endif
