//
// C++ Implementation: Article
//
// Author: WangHui
// Copyright: See COPYING file that comes with this distribution
//
#include "article_inpro.h"

Article_Inpro::Article_Inpro(char* _str)
    : str(_str)
{
}

Article_Inpro::~Article_Inpro()
{
}



/**
 * Calculates contents for main ("is a" type) triple
 * @return success; may fail, if relevant information about this documents type are still missing
 */
bool Article_Inpro::calc()
{
    
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,str);
    RDFObject *o2 = new RDFObject(RDFObject::AbbrObj, "rdf:type");
    RDFObject *o3 = new RDFObject("bench", "Article_Inpro");
    setObjs(o1, o2, o3);
    
    return true;

} //calc()
