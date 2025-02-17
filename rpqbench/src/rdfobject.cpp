//
// C++ Implementation: RDFObject 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "rdfobject.h"

/**
 * Constructor; builds object from type and full descriptive string
 * @param _type type of object
 * @param _str full property/descriptive string
 */
RDFObject::RDFObject(oType _type, const char * _str)
    : type(_type), str(0), str_length(0)
{
    if(type == ConstObj)
    { //special case because of quotes
        str = new char[strlen(_str) + 3];
        str[0] = '"';
        strcpy(str + sizeof(char), _str);
        str[(strlen(_str)+1) * sizeof(char)] = '"';
        str[(strlen(_str)+2) * sizeof(char)] = 0;
        str_length = strlen(str);
    }
    else
    {
        str = new char[strlen(_str) + 1];
        strcpy(str, _str);
        str_length = strlen(str);
    }
    
} //constructor

/**
 * Constructor for URI objects; builds URI object from URI prefix/base URL and identifier.
 * The prefix type can be switched between a real prefix (causing the object string to be
 * in prefix notation) and a non-prefix (base URL) which causes the object to hold a full
 * URI in URI notation.
 * @param prefix URI prefix
 * @param _str URI identifier
 */
RDFObject::RDFObject(const char * prefix, const char * _str, bool is_prefix)
    : type(URIObj), str(0), str_length(0)
{
    if(is_prefix)
    { //prefix notation
        str = new char[strlen(prefix) + strlen(_str) + 3];
        strcpy(str, prefix);
        strcpy(str + strlen(prefix) * sizeof(char), ":/");
        strcpy(str + (strlen(prefix)+2) * sizeof(char), _str);
        str_length = strlen(prefix) + strlen(_str) + 2;
    }
    else
    { //full URI notation
        str = new char[strlen(prefix) + strlen(_str) + 4];
        str[0] = '<';
        strcpy(str + sizeof(char), prefix);
        strcpy(str + (strlen(prefix)+1) * sizeof(char), "/");
        strcpy(str + (strlen(prefix)+2) * sizeof(char), _str);
        str[strlen(prefix) + strlen(_str) + 2] = '>';
        str[strlen(prefix) + strlen(_str) + 3] = 0; //terminator
        str_length = strlen(prefix) + strlen(_str) + 3;
    }
} //constructor

/**
 * Constructor for abbreviation/prefix objects; builds an abbreviation object from
 * prefix and identifier.
 * @param pref 
 * @param ident 
 */
RDFObject::RDFObject(const char * pref, const char * ident)
    : type(AbbrObj), str(0), str_length(0)
{
    str = new char[strlen(pref) + strlen(ident) + 2];
    strcpy(str, pref);
    str[strlen(pref)] = ':';
    strcpy(str + (strlen(pref)+1) * sizeof(char), ident);
    str_length = strlen(pref) + strlen(ident) + 1;
} //constructor

/**
 * Constructor for typed const objects; builds a constant object with type from
 * const value and type identifier.
 * @param val constant value
 * @param ident type identifier; 0 == string (default), 1 == int, 2 == year
 */
RDFObject::RDFObject(const char * val, unsigned ident)
    : type(ConstObj), str(0), str_length(0)
{
const char *type_string = "\"^^xsd:string";
const char *type_integer = "\"^^xsd:integer";
const char *type_year = "\"^^xsd:integer";
const char *tstr = 0L;

#ifdef NO_CONST_TYPES
    tstr = "\"";
#else
    switch(ident)
    {
        case 1:
            tstr = type_integer;
            break;

        case 2:
            tstr = type_year;
            break;

        default:
            tstr = type_string;
            break;
    }
#endif //else of NO_CONST_TYPES

    str = new char[strlen(val) + strlen(tstr) + 2];

    str[0] = '"';
    strcpy(str + sizeof(char), val);
    strcpy(str + (strlen(val)+1) * sizeof(char), tstr);
    
    str_length = strlen(str);

} //constructor

RDFObject::~RDFObject()
{
    delete[] str;
}


