//
// C++ Interface: Functions
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "math.h"
#include "randomwww.h"
#include "randomphd.h"
#include "randommaster.h"
#include "propertymanager.h"

/**
@author Michael Schmidt, Christoph Pinkel
*/
class Functions
{
public:
    Functions();
    ~Functions();
    
    ///////////////////////////////////////////////////////////////////
    // INTERFACE FUNCTIONS
    
    // number of document class instances per year
    static unsigned proc(unsigned year);    // f_{proc}
    static unsigned journal(unsigned year); // f_{journal}     
    static unsigned inproc(unsigned year);  // f_{inproc}     
    static unsigned article(unsigned year); // f_{article}     
    static unsigned book(unsigned year);    // f_{book}           
    static unsigned incoll(unsigned year);  // f_{incoll}
    static unsigned phd(unsigned year);     // f_{phd}        
    static unsigned master(unsigned year);  // f_{master}
    static unsigned www(unsigned year);     // f_{www}
    static unsigned publ(unsigned year);    // f_{publ}
    
    // rough estimates for authors, distinct authors, new authors, and retiring authors 
    static unsigned nrTotalAuthors(unsigned year);      // derived from document counts and
                                                        // average number of coauthors in year 
    static unsigned nrDistinctAuthors(unsigned year); 
    static unsigned nrNewAuthors(unsigned year);
    static unsigned nrRetiringAuthors(unsigned year, unsigned nr_cur_authors); 

    // authors and their number of publications
    static double fitAuthorsWithNumPublicationsParameter(unsigned year);
    static unsigned authorsWithNumPublications(unsigned num,unsigned year,double param); // f_{awp}

    // rough estimates for coauthor 
    static double muCoauth(unsigned x); 
    static double muDistCoauth(unsigned x);

    // number of editors in a year and publication relation
    static unsigned nrTotalEditors(unsigned year);
    static unsigned editorPublications(unsigned x,unsigned year);

    // citations
    static double fitNrIncomingCitationsParameter(unsigned year,unsigned est_total_ref);
    static unsigned nrIncomingCitations(unsigned x,unsigned year,double param);
    static unsigned countIncomingCitations(unsigned year,double param);
    static unsigned estimateNrOutgoingReferencesUpTo(unsigned year,
                unsigned nr_inproceedings_yr_before,unsigned nr_proceedings_yr_before,
                unsigned nr_articles_yr_before,unsigned nr_journals_yr_before,
                unsigned nr_incollections_yr_before,unsigned nr_books_yr_before,
                unsigned nr_wwws_yr_before,unsigned nr_masterstheses_yr_before,
                unsigned nr_phdtheses_yr_before,double avg_citations); 
    static unsigned estimateNrOutgoingReferencesIn(unsigned year,double avg_citations); 

    ///////////////////////////////////////////////////////////////////
    // NON-INTERFACE FUNCTIONS
    static double probAuthExpectation(unsigned year);
    static double probAuthVariance(unsigned year);
    static double probEditExpectation(unsigned year);
    static double probEditVariance(unsigned year);
    static double probCiteVariance(unsigned year);
    static double probCiteExpectation(unsigned year);

    // general function families 
    static double probGauss(unsigned num,double mu,double sigma);
    static double logisticCurve(unsigned num,double a,double b,double c,
                                double d,unsigned offset);
    static double powerLaw(unsigned num,double a,double b, double c);

    // round positive double to unsigned int
    static unsigned doubleToUnsigned(double x);


private:
    static double pi;

    // helper functions authorsWithNumPublications() and its fitting function
    static unsigned expectedAuthors(unsigned year,double param);
    static double authorsWithNumPublications1(unsigned year,double param);
    static double authorsWithNumPublications2(unsigned year);

    // helper functions editors
    static double editorPublications1(unsigned year);

    // citation
    static double nrIncomingCitations1(unsigned year,double param);
    static double nrIncomingCitations2(unsigned year);

};

#endif
