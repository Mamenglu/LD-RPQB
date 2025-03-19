//
// C++ Interface: Inproceedings 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef INPROCEEDINGS_H
#define INPROCEEDINGS_H

#include "document.h"

/**
Implements document type InProceedings
*/
class Inproceedings : public Document
{

public:
    Inproceedings(unsigned,unsigned,unsigned);
    virtual ~Inproceedings();

protected:
    virtual bool calc();
    int pnum;
};

#endif // INPROCEEDINGS_H
