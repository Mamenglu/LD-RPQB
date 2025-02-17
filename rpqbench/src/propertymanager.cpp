//
// C++ Implementation: PropertyManager
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "propertymanager.h"

PropertyManager* PropertyManager::instance=NULL;

/**
 * Retrieves singleton pattern class instance
 * @return singleton pattern instance
 */
PropertyManager* PropertyManager::getInstance()
{
    
    if (instance==NULL)
    {
        instance=new PropertyManager();
    }

    return instance;
}

PropertyManager::PropertyManager()
    : r(Randomnizer::getInstance())
{
    for(unsigned i = 0; i < PROPERTY_YEAR+1; i++)
        as[i] = false;

    fillProbabilityArray();
}

PropertyManager::~PropertyManager()
{
}


void PropertyManager::freshAttributeSet(unsigned document_class)
{
const unsigned properties[] = {
    PROPERTY_ABSTRACT,
    PROPERTY_ADDRESS,
    PROPERTY_AUTHOR,
    PROPERTY_BOOKTITLE,
    PROPERTY_CDROM,
    PROPERTY_CHAPTER,
    PROPERTY_CITE,
    PROPERTY_CROSSREF,
    PROPERTY_EDITOR,
    PROPERTY_EE,
    PROPERTY_ISBN,
    PROPERTY_JOURNAL,
    PROPERTY_MONTH,
    PROPERTY_NOTE,
    PROPERTY_NUMBER,
    PROPERTY_PAGE,
    PROPERTY_PUBLISHER,
    PROPERTY_SCHOOL,
    PROPERTY_SERIES,
    PROPERTY_TITLE,
    PROPERTY_URL,
    PROPERTY_VOLUME,
    PROPERTY_YEAR
    };

    //filling attribute set...
    for(unsigned i = 0; i < PROPERTY_YEAR+1; i++)
    {
        if((unsigned) (10000 * probabilities[document_class][properties[i]])
            > r->getRandomValue(10000))
            as[properties[i]] = true;
        else
            as[properties[i]] = false;
    } //for

} //freshAttributeSet()

double PropertyManager::getAuthorProbability(unsigned document_class) {
    return probabilities[document_class][PROPERTY_AUTHOR];
}

double PropertyManager::getEditorProbability(unsigned document_class) {
    return probabilities[document_class][PROPERTY_EDITOR];
}

double PropertyManager::getCiteProbability(unsigned document_class) {
	return probabilities[document_class][PROPERTY_CITE];
}

bool PropertyManager::containsAttribute(unsigned attribute)
{
    return as[attribute];
}

/**
 * Initialize properties for document class types according to the values
 * extracted from the DBLP database 
 */
void PropertyManager::fillProbabilityArray()
{
    //probability tables:
    probabilities[DOCTYPE_JOURNAL][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_AUTHOR]    =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_BOOKTITLE] =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_CDROM]     =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_CITE]      =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_CROSSREF]  =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_EDITOR]    =0.7; // missing in DBLP, estimated
    probabilities[DOCTYPE_JOURNAL][PROPERTY_EE]        =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_ISBN]      =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_MONTH]     =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_NUMBER]    =0.9224; // fw from article
    probabilities[DOCTYPE_JOURNAL][PROPERTY_PAGE]      =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_PUBLISHER] =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_SERIES]    =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_URL]       =0;
    probabilities[DOCTYPE_JOURNAL][PROPERTY_VOLUME]    =0.9982; // fw from article
    probabilities[DOCTYPE_JOURNAL][PROPERTY_YEAR]      =1; // fw from article

    probabilities[DOCTYPE_ARTICLE][PROPERTY_ABSTRACT]  =0.0100; // user-defined 
    probabilities[DOCTYPE_ARTICLE][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_AUTHOR]    =0.9895;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_BOOKTITLE] =0.0006;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_CDROM]     =0.0112;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_CITE]      =0.0048; // 0.0048
    probabilities[DOCTYPE_ARTICLE][PROPERTY_CROSSREF]  =0.0006;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_EDITOR]    =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_EE]        =0.6781;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_ISBN]      =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_JOURNAL]   =0.9994;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_MONTH]     =0.0065;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_NOTE]      =0.0297;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_NUMBER]    =0;    // fw to journal
    probabilities[DOCTYPE_ARTICLE][PROPERTY_PAGE]      =0.9261;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_PUBLISHER] =0.0006;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_SERIES]    =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_URL]       =0.9986;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_VOLUME]    =0;
    probabilities[DOCTYPE_ARTICLE][PROPERTY_YEAR]      =0;    // fw to journal

    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_ABSTRACT]  =0.0100; // user-defined 
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_AUTHOR]    =0.997;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_BOOKTITLE] =1;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_CDROM]     =0.0162;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_CITE]      =0.0104; // 0.0104
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_CROSSREF]  =0.8003;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_EDITOR]    =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_EE]        =0.6519;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_ISBN]      =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_MONTH]     =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_NUMBER]    =0.0001;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_PAGE]      =0.9489;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_PUBLISHER] =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_SERIES]    =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_URL]       =1;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_VOLUME]    =0;
    probabilities[DOCTYPE_INPROCEEDINGS][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_ADDRESS]   =0.0004;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_AUTHOR]    =0.0001;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_BOOKTITLE] =0.9579;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_CDROM]     =0;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_CITE]      =0.0001;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_CROSSREF]  =0.0016;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_EDITOR]    =0.7992;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_EE]        =0.0019;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_ISBN]      =0.8592;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_JOURNAL]   =0.0004;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_MONTH]     =0.0001;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_NOTE]      =0.0002;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_NUMBER]    =0.0009;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_PAGE]      =0;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_PUBLISHER] =0.9737;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_SERIES]    =0.5791;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_URL]       =0.9860;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_VOLUME]    =0.5670;
    probabilities[DOCTYPE_PROCEEDINGS][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_BOOK][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_AUTHOR]    =0.8937;
    probabilities[DOCTYPE_BOOK][PROPERTY_BOOKTITLE] =0.0183;
    probabilities[DOCTYPE_BOOK][PROPERTY_CDROM]     =0.0032;
    probabilities[DOCTYPE_BOOK][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_CITE]      =0.0079;
    probabilities[DOCTYPE_BOOK][PROPERTY_CROSSREF]  =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_EDITOR]    =0.1040;
    probabilities[DOCTYPE_BOOK][PROPERTY_EE]        =0.0079;
    probabilities[DOCTYPE_BOOK][PROPERTY_ISBN]      =0.9294;
    probabilities[DOCTYPE_BOOK][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_MONTH]     =0.0008;
    probabilities[DOCTYPE_BOOK][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_NUMBER]    =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_PAGE]      =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_PUBLISHER] =0.9992;
    probabilities[DOCTYPE_BOOK][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_BOOK][PROPERTY_SERIES]    =0.5365;
    probabilities[DOCTYPE_BOOK][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_BOOK][PROPERTY_URL]       =0.2373;
    probabilities[DOCTYPE_BOOK][PROPERTY_VOLUME]    =0.5024;
    probabilities[DOCTYPE_BOOK][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_AUTHOR]    =0.8459;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_BOOKTITLE] =1;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_CDROM]     =0.0138;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_CHAPTER]   =0.0005;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_CITE]      =0.0047;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_CROSSREF]  =0.6951;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_EDITOR]    =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_EE]        =0.361;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_ISBN]      =0.0073;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_MONTH]     =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_NUMBER]    =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_PAGE]      =0.6849;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_PUBLISHER] =0.0237;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_SCHOOL]    =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_SERIES]    =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_URL]       =0.9992;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_VOLUME]    =0;
    probabilities[DOCTYPE_INCOLLECTION][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_AUTHOR]    =1;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_BOOKTITLE] =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_CDROM]     =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_CITE]      =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_CROSSREF]  =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_EDITOR]    =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_EE]        =0.1444;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_ISBN]      =0.0222;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_MONTH]     =0.0333;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_NUMBER]    =0.0333;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_PAGE]      =0;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_PUBLISHER] =0.0444;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_SCHOOL]    =1;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_SERIES]    =0.0222;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_URL]       =0.0222;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_VOLUME]    =0.0111;
    probabilities[DOCTYPE_PHDTHESIS][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_ABSTRACT]  =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_ADDRESS]   =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_AUTHOR]    =1;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_BOOKTITLE] =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_CDROM]     =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_CHAPTER]   =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_CITE]      =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_CROSSREF]  =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_EDITOR]    =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_EE]        =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_ISBN]      =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_JOURNAL]   =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_MONTH]     =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_NOTE]      =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_NUMBER]    =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_PAGE]      =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_PUBLISHER] =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_SCHOOL]    =1;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_SERIES]    =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_TITLE]     =1;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_URL]       =0.3750;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_VOLUME]    =0;
    probabilities[DOCTYPE_MASTERSTHESIS][PROPERTY_YEAR]      =1;

    probabilities[DOCTYPE_WWW][PROPERTY_ABSTRACT]   =0;
    probabilities[DOCTYPE_WWW][PROPERTY_ADDRESS]    =0;
    probabilities[DOCTYPE_WWW][PROPERTY_AUTHOR]     =0.9973;
    probabilities[DOCTYPE_WWW][PROPERTY_BOOKTITLE]  =0.0001;
    probabilities[DOCTYPE_WWW][PROPERTY_CDROM]      =0;
    probabilities[DOCTYPE_WWW][PROPERTY_CHAPTER]    =0;
    probabilities[DOCTYPE_WWW][PROPERTY_CITE]       =0;
    probabilities[DOCTYPE_WWW][PROPERTY_CROSSREF]   =0;
    probabilities[DOCTYPE_WWW][PROPERTY_EDITOR]     =0.0004;
    probabilities[DOCTYPE_WWW][PROPERTY_EE]         =0;
    probabilities[DOCTYPE_WWW][PROPERTY_ISBN]       =0;
    probabilities[DOCTYPE_WWW][PROPERTY_JOURNAL]    =0;
    probabilities[DOCTYPE_WWW][PROPERTY_MONTH]      =0;
    probabilities[DOCTYPE_WWW][PROPERTY_NOTE]       =0.0273;
    probabilities[DOCTYPE_WWW][PROPERTY_NUMBER]     =0;
    probabilities[DOCTYPE_WWW][PROPERTY_PAGE]       =0;
    probabilities[DOCTYPE_WWW][PROPERTY_PUBLISHER]  =0;
    probabilities[DOCTYPE_WWW][PROPERTY_SCHOOL]     =0;
    probabilities[DOCTYPE_WWW][PROPERTY_SERIES]     =0;
    probabilities[DOCTYPE_WWW][PROPERTY_TITLE]      =1;
    probabilities[DOCTYPE_WWW][PROPERTY_URL]        =0.9624;
    probabilities[DOCTYPE_WWW][PROPERTY_VOLUME]     =0;
    probabilities[DOCTYPE_WWW][PROPERTY_YEAR]       =0.0011;
}
