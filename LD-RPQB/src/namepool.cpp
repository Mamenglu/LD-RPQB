//
// C++ Implementation: NamePool
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "namepool.h"


/**
 * Constructor
 * @param _type
 * @param start_offset
 * @param rep_offset
 */
NamePool::NamePool(NamePoolFile::nfTypes _type, unsigned start_offset, unsigned rep_offset)
    : type(_type), pos(start_offset), offset_inc(rep_offset),
        offset(0), npfi(NamePoolFile::getInstance(type)), run(0)
{
} //constructor


NamePool::~NamePool()
{
}

/*!
    \fn NamePool::getName()
    Returns a new word as char *. Please note that the char * could be needed
    later and should therefore neither be altered nor deleted.
    @return next word from (infinitely rotating) list
 */
char * NamePool::getName()
{
char *ret = npfi->getLine(pos);

    pos++;
    if(pos >= npfi->getSize())
    {
        offset += offset_inc;
        pos = offset % npfi->getSize(); /*restarting from beginning,
            shifted by increased offset (using % in case that the increased offset
            might have exeeded the end of the list)*/

		run++;
    }

    return ret;
}

/*!
    \fn NamePool::getNameId()
    Returns the current pos.
    @return pos of next word from (infinitely rotating) list
 */
unsigned NamePool::getNameId()
{
unsigned ret = pos;

    pos++;
    if(pos >= npfi->getSize())
    {
        offset += offset_inc;
        pos = offset % npfi->getSize(); /*restarting from beginning,
            shifted by increased offset (using % in case that the increased offset
            might have exeeded the end of the list)*/
		run++;
    }

    return ret;
}

/*!
    \fn NamePool::getNameById()
    Returns the word associated with position id as char *.
    @return corresponding char* (no copy)
 */
char* NamePool::getNameById(unsigned id)
{
    return npfi->getLine(id); // we assume id to be valid
}

void NamePool::cmpRealPos(NamePool *n)
{
	if(pos == n->getPos()) // && run > 0)
	{
		cout << "Name pool is too small. Please add more names to the input "
			<< "name pools." << endl;
		abort();
	}
}

unsigned NamePool::getPos()
{
	return pos;
}

