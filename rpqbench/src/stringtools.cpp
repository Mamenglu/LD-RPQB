//
// C++ Implementation: StringTools 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "stringtools.h"

StringTools::StringTools()
{
}


StringTools::~StringTools()
{
}


/*!
    \fn StringTools::concatStrs(char *, char *, char *=0L, char *=0L)
    @return newly allocated string, concatenating up to four input strings
 */
char * StringTools::concatStrs(char *s1, char *s2, char *s3, char *s4)
{
char *ret;
unsigned len = strlen(s1) + strlen(s2) + 1;

    if(s3) len += strlen(s3);
    if(s4) len += strlen(s4);
    
    ret = new char[len];
    ret[len-1] = 0; //just in case
    
    strcpy(ret, s1);
    strcpy(ret + strlen(s1) * sizeof(char), s2);
    
    if(s3)
        strcpy(ret + (strlen(s1) +strlen(s2)) * sizeof(char), s3);
    
    if(s4)
        strcpy(ret + (strlen(s1) +strlen(s2) +strlen(s3)) * sizeof(char), s4);

    return ret;

} //concatStr()


/*!
    \fn StringTools::numStr(const char *in_str, unsigned num)
    @return a newly allocated string, concatenating copy of input string with number (as string)
 */
char * StringTools::numStr(const char *in_str, unsigned num)
{
unsigned nsl = 0;
char * ret;

    if(num == 0)
    {
        ret = new char[strlen(in_str)];
        strcpy(ret, in_str);
        ret[strlen(in_str)] = '0';
        ret[strlen(in_str)+1] = 0;
        
        return ret;
        
    } //if num == 0

    //calculating string length...
    for(int f = 1; num/f > 0; f *= 10)
        nsl++;

    ret = new char[strlen(in_str) + nsl + 1];
    
    //filling with prefix...
    strcpy(ret, in_str);
    
    //adding number...
    ret[nsl + strlen(in_str)] = 0; //terminator
    int pos = nsl +strlen(in_str) -1;
    unsigned tmpnum = num;
    
    while(pos >= (int)strlen(in_str))
    {
        ret[pos] = tmpnum % 10 + 48;
        tmpnum /= 10;
        pos--;
    } //while
    
    return ret;

} //numStr()
