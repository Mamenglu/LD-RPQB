//
// C++ Implementation: PropertyPublisher
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertypublisher.h"
#include "publishers.h"

PropertyPublisher::PropertyPublisher(RDFTriple *main_triple) :
    Property(PROPERTY_PUBLISHER, main_triple)
{
}


PropertyPublisher::~PropertyPublisher()
{
}


/*!
    \fn PropertyPublisher::calc()
 */
bool PropertyPublisher::calc()
{
    RDFObject *o1 = new RDFObject(RDFObject::URIObj,
        mainTriple()->getSubjectPtr()->getString());
    RDFObject *o2 = new RDFObject("dc", "publisher");
    RDFObject *o3 = new RDFObject(
        Publishers::getInstance()->getRandomPublisher());
    setObjs(o1, o2, o3);

    return true;
}
