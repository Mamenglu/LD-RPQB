//
// C++ Interface: Article
//
// Author: WangHui
// Copyright: See COPYING file that comes with this distribution
//
#ifndef ARTICLE_INPRO_H
#define ARTICLE_INPRO_H

#include "rdftriple.h"

/**
Implements document type article
*/
class Article_Inpro : public RDFTriple
{

public:
    Article_Inpro(char*);
    virtual ~Article_Inpro();

protected:
    virtual bool calc();
    char* str;
};

#endif // ARTICLE_INPRO_H
