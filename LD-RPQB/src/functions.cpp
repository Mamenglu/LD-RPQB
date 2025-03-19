//
// C++ Implementation: Functions
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "functions.h"

Functions::Functions() {}

Functions::~Functions() {}

// static
double Functions::pi=3.141592653589;

/*!
    \fn Functions::proc(unsigned year)
    @return number of proceedings in specified year
 */
unsigned Functions::proc(unsigned year)
{
    return doubleToUnsigned(logisticCurve(year,5502.31,1250.26,0.14,0,1965));
}

/*!
    \fn Functions::journal(unsigned year)
    @return number of proceedings in specified year
 */
unsigned Functions::journal(unsigned year)
{
    return doubleToUnsigned(logisticCurve(year,740.43,426.28,0.12,0,1950));
}

/*!
    \fn Functions::inproc(unsigned year)
    @return number of "InProceedings" in specified year
 */
unsigned Functions::inproc(unsigned year)
{
    if (proc(year)>0) {
        return doubleToUnsigned(logisticCurve(year,337132.34,1901.05,0.15,0,1965));
    }
    return 0; // in case there is no proceeding
}

/*!
    \fn Functions::article(unsigned year)
    @return total number of articles in specified year
 */
unsigned Functions::article(unsigned year)
{
    if (journal(year)>0) {
        return doubleToUnsigned(logisticCurve(year,58519.12,876.80,0.12,0,1950));
    }
    return 0; // in case there is no journal
}

/*!
    \fn Functions::book(unsigned year)
    @return number of books in specified year
 */
unsigned Functions::book(unsigned year)
{
    return doubleToUnsigned(logisticCurve(year,52.97,40739.38,0.32,0,1950));
}

/*!
    \fn Functions::incoll(unsigned year)
    @return number of "InCollections" in specified year
 */
unsigned Functions::incoll(unsigned year)
{
    return doubleToUnsigned(logisticCurve(year,3577.31,196.49,0.091,0,1980));
}

/*!
    \fn Functions::phd(unsigned year)
    @return number of phd theses in specified year
 */
unsigned Functions::phd(unsigned year)
{
    if (year<1980) {
        return 0;
    }
    return RandomPhD::getInstance()->getResultFromYear(year);
}

/*!
    \fn Functions::master(unsigned year)
    @return number of master theses in specified year
 */
unsigned Functions::master(unsigned year)
{
    if (year<1980) {
        return 0;
    }
    return RandomMaster::getInstance()->getResultFromYear(year);
}

/*!
    \fn Functions::www(unsigned year)
    @return number of www documents in specified year

    // ATTENTION: only call once for each year (random)
 */
unsigned Functions::www(unsigned year)
{
    if (year<1980) {
        return 0;
    }
    return RandomWww::getInstance()->getResultFromYear(year);
}


/*!
    \fn Functions::nrTotalAuthors(unsigned year)
    @return total number of authors in year
 */
unsigned Functions::nrTotalAuthors(unsigned year) {

    // get individual number of document class instances
    unsigned nr_proc=proc(year);
    unsigned nr_inproc=inproc(year);
    unsigned nr_article=article(year);
    unsigned nr_book=book(year);
    unsigned nr_incoll=incoll(year);
    unsigned nr_phd=phd(year);
    unsigned nr_master=master(year);
    unsigned nr_www=www(year);

    PropertyManager* pman=PropertyManager::getInstance();
    unsigned nr_authors_proc=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_PROCEEDINGS)*nr_proc);
    unsigned nr_authors_inproc=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_INPROCEEDINGS)*nr_inproc);
    unsigned nr_authors_article=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_ARTICLE)*nr_article);
    unsigned nr_authors_book=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_BOOK)*nr_book);
    unsigned nr_authors_incoll=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_INCOLLECTION)*nr_incoll);
    unsigned nr_authors_phd=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_PHDTHESIS)*nr_phd);
    unsigned nr_authors_master=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_MASTERSTHESIS)*nr_master);
    unsigned nr_authors_www=doubleToUnsigned(
        pman->getAuthorProbability(DOCTYPE_WWW)*nr_www);
    
    double expected_authors=(nr_authors_proc+nr_authors_inproc+
                                nr_authors_article+nr_authors_incoll+
                                nr_authors_book+nr_authors_phd+
                                nr_authors_master+nr_authors_www)
                                *probAuthExpectation(year);
    return doubleToUnsigned(expected_authors);
}

unsigned Functions::nrTotalEditors(unsigned year) {

    // get individual number of document class instances
    unsigned nr_proc=proc(year);
    unsigned nr_inproc=inproc(year);
    unsigned nr_article=article(year);
    unsigned nr_book=book(year);
    unsigned nr_incoll=incoll(year);
    unsigned nr_phd=phd(year);
    unsigned nr_master=master(year);
    unsigned nr_www=www(year);

    PropertyManager* pman=PropertyManager::getInstance();
    unsigned nr_editors_proc=doubleToUnsigned(
            pman->getEditorProbability(DOCTYPE_PROCEEDINGS)*nr_proc);
    unsigned nr_editors_inproc=doubleToUnsigned(
            pman->getEditorProbability(DOCTYPE_INPROCEEDINGS)*nr_inproc);
    unsigned nr_editors_article=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_ARTICLE)*nr_article);
    unsigned nr_editors_book=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_BOOK)*nr_book);
    unsigned nr_editors_incoll=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_INCOLLECTION)*nr_incoll);
    unsigned nr_editors_phd=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_PHDTHESIS)*nr_phd);
    unsigned nr_editors_master=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_MASTERSTHESIS)*nr_master);
    unsigned nr_editors_www=doubleToUnsigned(
        pman->getEditorProbability(DOCTYPE_WWW)*nr_www);
    
    double expected_editors=(nr_editors_proc+nr_editors_inproc+
                                nr_editors_article+nr_editors_incoll+
                                nr_editors_book+nr_editors_phd+
                                nr_editors_master+nr_editors_www)
                                *probEditExpectation(year);
    return doubleToUnsigned(expected_editors);
}

/*!
    \fn Functions::nrDistinctAuthors(unsigned year)
    @return number of distinct authors in year
 */
unsigned Functions::nrDistinctAuthors(unsigned year) {
    return doubleToUnsigned(
            logisticCurve(year,-0.667,169.41,0.0714,0.84,1936)*
            nrTotalAuthors(year));
}

/*!
    \fn Functions::nrNewAuthors(unsigned year)
    @return number of new authors in year
 */
unsigned Functions::nrNewAuthors(unsigned year) {
    return doubleToUnsigned(
            logisticCurve(year,-0.293,1740,0.136,0.628,1936)*
            nrDistinctAuthors(year));
}

/*!
    \fn Functions::nrRetiringAuthors(unsigned year)
    @return number of retiring authors in year
 */
unsigned Functions::nrRetiringAuthors(unsigned year,unsigned nr_cur_authors) {
    // retiring is done at the end of the year;
    // in the next year, we need at most nrTotalAuthors(year+1).
    int nr_retired_authors=
        nrNewAuthors(year+1)-
        ((int)nrTotalAuthors(year+1)-(int)nr_cur_authors);
    if (nr_retired_authors<0) {
        return 0;
    } else {
        return (unsigned)nr_retired_authors;
    }
}

/*!
    \fn Functions::fitAuthorsWithNumPublicationsParameter(unsigned num,unsigned year)
    @return number of authors with publication count num in year 
 */
double Functions::fitAuthorsWithNumPublicationsParameter(unsigned year) {

    // simply using "year" as a parameter for authorsWithNumPublications
    // gives a slight overestimation (i.e. the approximation depends on
    // the total number of authors, and thus should be fitted); for this
    // reason, we try to find a parameter that gives a distribution close to
    // nrTotalAuthors(year)
    unsigned exp_total_authors=Functions::nrTotalAuthors(year);
    double d_exp_total_authors=(double) exp_total_authors;

    // we start with param year
    double param=1.5; // start approximation
    double scale=0.1; // increase/decrease param by this value

    // first make sure we have an overestimation
    while (Functions::expectedAuthors(year,param)<exp_total_authors
            && Functions::expectedAuthors(year,param)!=0) {
        param+=scale;
    }

    // in this case, no fitting is possible/necessary
    if (Functions::expectedAuthors(year,param)==0) {
        return param;
    }

    bool finished=false;
    do {
        // this is what we expect for the current parameter
        unsigned exp_authors=Functions::expectedAuthors(year,param);

        if (((int)exp_authors)-((int) exp_total_authors) < 0) {
            // if we have an underestimation correct and adapt scaling factor
            param+=scale; 
            scale/=10;
        } else {
            double d_exp_authors=(double)exp_authors;
            // break if the overestimation is in range of about 5% 
            if (d_exp_authors/d_exp_total_authors<1.05) {
                finished=true;
            } else {
                // lower by scaling factor
                param-=scale;
            }
        }
    } while (!finished || scale<=0.000001); // make sure that we eventually break
    return param;
}

/*!
    \fn Functions::authorsWithNumPublications(unsigned num,double param)
    @return number of authors with publication count num in year for
            a given parameter (fix param with fitAuthorsWithPublicationsParameter)
 */
unsigned Functions::authorsWithNumPublications(unsigned num,unsigned year,double param) {
    // function as estimated
    return doubleToUnsigned(powerLaw(num,authorsWithNumPublications1(year,param),
                                    authorsWithNumPublications2(year),-5));
}


unsigned Functions::expectedAuthors(unsigned year,double param) {
    unsigned sum=0;
    for (unsigned i=1;;i++) {
        unsigned add=i*Functions::authorsWithNumPublications(i,year,param);
        if (add==0) {
            return sum; // stop
        } else {
            sum+=add;
        }
    }
}

// expectation value of coauthors for x publications
double Functions::muCoauth(unsigned x) {
    return 2.12*x;
}

// expectation value of distinct coauthors for x authors 
double Functions::muDistCoauth(unsigned x) {
    return pow(x,0.811);
}

// number of editors with given publication count
unsigned Functions::editorPublications(unsigned x,unsigned year) {
    return doubleToUnsigned(
            2*nrTotalEditors(year)*probGauss(x,0,editorPublications1(year)));
}

/*!
    \fn Functions::fitAuthorsWithNumPublicationsParameter(unsigned num,unsigned year)
    @return number of authors with publication count num in year 
 */
double Functions::fitNrIncomingCitationsParameter(unsigned year,
                                                    unsigned est_total_ref) {
    // est_total_ref denotes the total number of outgoing references in year
    // -> according to DBLP, about 65% of these citations are also incoming
    //    references (all other point to an unknown document/are left unspecified) 
    unsigned desired_incoming_references=(unsigned)(0.65*est_total_ref);

    // break if no incoming references are expected
    if (desired_incoming_references==0) {
        return 0; // param 0 will not create any incoming references
    }

    // we now fit the parameter such that about desired_incoming_references
    // (+/-3%) incoming references will be generated
    double param=0.02; // start parameter (this is a good choice)
    double scale=0.1; // increase/decrease param by this value

    // first make sure we have an overestimation
    while (Functions::countIncomingCitations(year,param)<=desired_incoming_references
            && Functions::countIncomingCitations(year,param)!=0) {
        param+=scale;
    }

    // in this case, no fitting is possible/necessary
    if (Functions::countIncomingCitations(year,param)==0) {
        return param;
    }

    // now adapt param until good approximation found
    do {
        // this is what we expect for the current parameter
        unsigned exp_incoming_references=
            Functions::countIncomingCitations(year,param);

        // check for approximation being ok (about 3% or less)
        if (((double)exp_incoming_references/(double)desired_incoming_references<1.03 &&
             (double)exp_incoming_references/(double)desired_incoming_references>0.97)
            || scale<0.000001) { // second cond. asserts that we will eventually break
            return param;
        }

        // estimation not quite good, so adapt parameter (shift curve)
        bool expected_to_high=
            ((int)exp_incoming_references-(int)desired_incoming_references)>0;
        if (expected_to_high) {
            param-=scale;
        } else {
            // if we have an underestimation correct and adapt scaling factor
            param+=scale; 
            scale/=10;
        }
    } while (true); // return inside
}


// distribution of incoming citations
unsigned Functions::nrIncomingCitations(unsigned x,unsigned year,double param) {
    return doubleToUnsigned(
            powerLaw(x,
                    nrIncomingCitations1(year,param),
                    1.6,
                    -nrIncomingCitations2(year)));
}

// estimate the total number of outgoing references up to year
// (these typically include references to the unknown document)
unsigned Functions::estimateNrOutgoingReferencesUpTo(unsigned year,
        unsigned nr_inproceedings_yr_before,unsigned nr_proceedings_yr_before,
        unsigned nr_articles_yr_before,unsigned nr_journals_yr_before,
        unsigned nr_incollections_yr_before,unsigned nr_books_yr_before,
        unsigned nr_wwws_yr_before,unsigned nr_masterstheses_yr_before,
        unsigned nr_phdtheses_yr_before,double avg_citations) {
    double nr_inproceedings=(double)(nr_inproceedings_yr_before+Functions::inproc(year));
    double nr_proceedings=(double)(nr_proceedings_yr_before+Functions::proc(year));
    double nr_articles=(double)(nr_articles_yr_before+Functions::article(year));
    double nr_journals=(double)(nr_journals_yr_before+Functions::journal(year));
    double nr_incollections=(double)(nr_incollections_yr_before+Functions::incoll(year));
    double nr_books=(double)(nr_books_yr_before+Functions::book(year));
    double nr_wwws=(double)(nr_wwws_yr_before+Functions::www(year));
    double nr_masterstheses=(double)(nr_masterstheses_yr_before+Functions::master(year));
    double nr_phdtheses=(double)(nr_phdtheses_yr_before+Functions::phd(year));

    PropertyManager* pman=PropertyManager::getInstance();
    // we first calculate the estimated nr of objects with references
    double est_nr_objects_with_references=
        pman->getCiteProbability(DOCTYPE_INPROCEEDINGS)*nr_inproceedings +
        pman->getCiteProbability(DOCTYPE_PROCEEDINGS)*nr_proceedings +
        pman->getCiteProbability(DOCTYPE_ARTICLE)*nr_articles +
        pman->getCiteProbability(DOCTYPE_JOURNAL)*nr_journals +
        pman->getCiteProbability(DOCTYPE_INCOLLECTION)*nr_incollections +
        pman->getCiteProbability(DOCTYPE_BOOK)*nr_books +
        pman->getCiteProbability(DOCTYPE_WWW)*nr_wwws +
        pman->getCiteProbability(DOCTYPE_MASTERSTHESIS)*nr_masterstheses +
        pman->getCiteProbability(DOCTYPE_PHDTHESIS)*nr_phdtheses;
    // and then the estimated total number of references; this is important, because
    // objects in average have about 18 outgoing reference attributes, so we
    // have to multiply with this average value
    double est_nr_references=est_nr_objects_with_references*avg_citations;
    return (unsigned)est_nr_references;
}

// estimate the number of outgoing citations in a given year (for debug purposes only)
unsigned Functions::estimateNrOutgoingReferencesIn(unsigned year,double avg_citations) {
    double nr_inproceedings=Functions::inproc(year);
    double nr_proceedings=Functions::proc(year);
    double nr_articles=article(year);
    double nr_journals=journal(year);
    double nr_incollections=Functions::incoll(year);
    double nr_books=Functions::book(year);
    double nr_wwws=Functions::www(year);
    double nr_masterstheses=Functions::master(year);
    double nr_phdtheses=Functions::phd(year);

    PropertyManager* pman=PropertyManager::getInstance();
    // we first calculate the estimated nr of objects with references
    double est_nr_objects_with_references=
        pman->getCiteProbability(DOCTYPE_INPROCEEDINGS)*nr_inproceedings +
        pman->getCiteProbability(DOCTYPE_PROCEEDINGS)*nr_proceedings +
        pman->getCiteProbability(DOCTYPE_ARTICLE)*nr_articles +
        pman->getCiteProbability(DOCTYPE_JOURNAL)*nr_journals +
        pman->getCiteProbability(DOCTYPE_INCOLLECTION)*nr_incollections +
        pman->getCiteProbability(DOCTYPE_BOOK)*nr_books +
        pman->getCiteProbability(DOCTYPE_WWW)*nr_wwws +
        pman->getCiteProbability(DOCTYPE_MASTERSTHESIS)*nr_masterstheses +
        pman->getCiteProbability(DOCTYPE_PHDTHESIS)*nr_phdtheses;
    // and then the estimated total number of references; this is important, because
    // objects in average have about 18 outgoing reference attributes, so we
    // have to multiply with this average value
    double est_nr_references=est_nr_objects_with_references*avg_citations;
    return (unsigned)est_nr_references;
}

// count the total number of incoming citations in a year for fixed parameter
unsigned Functions::countIncomingCitations(unsigned year,double param) {
    unsigned sum=0;
    bool finished=false;
    for (unsigned i=1;!finished;i++) {
        unsigned d=nrIncomingCitations(i,year,param);
        if (d==0) {
            finished=true;
        } else {
            sum+=i*d;
        }
    }
    return sum;
}

/*!
    \fn Functions::probAuthExpectation(unsigned year)
    @return expected number of authors in year
 */
double Functions::probAuthExpectation(unsigned year)
{
    return logisticCurve(year,2.05,17.59,0.11,1.05,1975);
}

/*!
    \fn Functions::probAuthVariance(unsigned year)
    @return author variance in year
 */
double Functions::probAuthVariance(unsigned year)
{
    return logisticCurve(year,1.00,6.46,0.10,0.50,1975);
}

// editor expectation value
double Functions::probEditExpectation(unsigned year)
{
    return 2.15;
}

// editor variance
double Functions::probEditVariance(unsigned year)
{
    return 1.18;
}

double Functions::probCiteExpectation(unsigned year)
{
    return 16.82;
}

double Functions::probCiteVariance(unsigned year)
{
    return 10.07;
}

/*!
    \fn Functions::paperCount(unsigned num, unsigned year)
    @return number of authors with given paper count up to year (publication date <= year)
 */


/*!
    \fn Functions::probGauss(double mu,double sigma,double offset)
    @return implements a standard Gaussian distribution with expectation value mu, variance sigma and offset
 */
double Functions::probGauss(unsigned num,double mu,double sigma) {
    return (1/(sigma*sqrt(2*pi)))*exp(-0.5*(pow((num-mu)/sigma,2)));
}

/*!
    \fn Functions::logisticCurve(double a,double b,double c,double d,unsigned offset)
    @return implements a logistic curve with offset 
 */
double Functions::logisticCurve(unsigned num,double a, double b, double c, 
                                double d,unsigned offset) {
    return a/(1+b*exp(-c*((int)num-(int)offset)))+d;
}

/*!
    \fn Functions::powerLaw(unsigned num,double a,double b,double c)
    @return power law function a*num^-b+c 
 */
double Functions::powerLaw(unsigned num,double a,double b, double c) {
    double f_x=a*pow(num,-b)+c;
    return f_x<0?0:doubleToUnsigned(f_x);
}

/*!
    \fn Functions::doubleToUnsigned(double d)
    @return convert positive double to unsigned (also rounds)
 */
unsigned Functions::doubleToUnsigned(double d) {
    return (unsigned)(d<0?d-.5:d+.5);
}

// sum of non-randomnized publications in year
unsigned Functions::publ(unsigned year) {
    return inproc(year)+article(year)+book(year)+incoll(year)
            +www(year)+phd(year)+master(year);

}

double Functions::authorsWithNumPublications1(unsigned year,double param) {
    return param*(double)publ(year);
}

double Functions::authorsWithNumPublications2(unsigned year) {
    return logisticCurve(year,-0.6,216223,0.196,3.078,1936);
}

double Functions::editorPublications1(unsigned year) {
    return logisticCurve(year,139,32.8,0.082,0,1975);
}

double Functions::nrIncomingCitations1(unsigned year,double param) {
    return param*(double)publ(year);
    //return logisticCurve(year,9939,1818140,0.262,0,1936);
}

double Functions::nrIncomingCitations2(unsigned year) {
    return logisticCurve(year,5.563,9.32,0.0474,0,1936);
}

