//
// C++ Interface: PropertyManager
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef PROPERTY_MANAGER_H
#define PROPERTY_MANAGER_H

#include <iostream>
#include "property.h"
#include "document.h"
#include "randomnizer.h"

using namespace std;

/**
* Singleton pattern class, implementing property (attribute) management for documents
*/
class PropertyManager
{
public:
    static PropertyManager* getInstance();
    virtual ~PropertyManager();

    void freshAttributeSet(unsigned document_class);
    bool containsAttribute(unsigned attribute);

    // probabilities for fixed attributes
    double getAuthorProbability(unsigned document_class);
    double getEditorProbability(unsigned document_class);
    double getCiteProbability(unsigned document_class);

protected:
    void fillProbabilityArray();

private:
    static PropertyManager* instance;
    PropertyManager();

    double probabilities[DOCTYPE_WWW+1][PROPERTY_YEAR+1];
    bool as[PROPERTY_YEAR+1];
    
    Randomnizer *r;

};


#endif // PROPERTY_MANAGER_H
