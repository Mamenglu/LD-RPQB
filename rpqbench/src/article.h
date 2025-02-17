//
// C++ Interface: Article
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef ARTICLE_H
#define ARTICLE_H

#include "document.h"

/**
Implements document type article
*/
class Article : public Document
{

public:
    Article(unsigned,unsigned,int);
    virtual ~Article();
    int getjnum();

protected:
    virtual bool calc();
    int jnum;
};

#endif // ARTICLE_H
