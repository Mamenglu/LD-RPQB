//
// C++ Interface: Generator 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef GENERATOR_H
#define GENERATOR_H

#include "stdio.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include "cmdline.h"
#include "default.h"
#include "version.h"
#include "outputlimitmgr.h"
#include "rdftriple.h"
#include "rdftriplepool.h"
#include "functions.h"
#include "proceedings.h"
#include "inproceedings.h"
#include "institution.h"
#include "article.h"
#include "article_inpro.h"
#include "journal.h"
#include "incollection.h"
#include "book.h"
#include "phdthesis.h"
#include "mastersthesis.h"
#include "www.h"
#include "gaussiandistribution.h"
#include "propertyjournal.h"
#include "activeauthors.h"
#include "author.h"
#include "editor.h"
#include "missingcites.h"
#include "blindrdftriple.h"
#include "referencebag.h"
#include "referencebagreference.h"

#define DBLP_STARTYEAR 1936 // real DBLP start year、
#define DIVISOR 24

#ifdef LOGMODE
#include "instancelogger.h"
#endif

using namespace std;

/**
* Main class (output generator). Incrementally produces output file until
* desired size is reached.
*/
class Generator
{
public:
    Generator(CmdLine* _cmd);
    virtual ~Generator();
    
    void generate();
private:
    void generateYear(unsigned,unsigned &,unsigned &,unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &,unsigned &,
                        unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &, unsigned &);
    
    RDFTriplePool generateConferences(unsigned,unsigned &);
    RDFTriplePool generatePathLengthOne(unsigned,vector<vector<Author *> >,RDFTriplePool *,RDFTriplePool *,unsigned &,unsigned &);
    RDFTriplePool generatePathLengthTwo(unsigned,RDFTriplePool *,RDFTriplePool *,RDFTriplePool *,unsigned &);
    RDFTriplePool generatePathLengthThree(unsigned,RDFTriplePool *,unsigned &);
    RDFTriplePool generatePathLengthFour(unsigned,RDFTriplePool *,unsigned &);
    RDFTriplePool generatePathLengthFive(unsigned,unsigned &);
    RDFTriplePool generatePathLengthSix(unsigned,unsigned &);
    RDFTriplePool generatePathLengthSeven(unsigned,unsigned &);
    RDFTriplePool generatePathLengthEight(unsigned,unsigned &);
    RDFTriplePool generatePathLengthNine(unsigned,unsigned &);
    RDFTriplePool generatePathLengthTen(unsigned,unsigned &);
    RDFTriplePool generatePathLengthEleven(unsigned,unsigned &);
    
    
    RDFTriplePool generateInProceedings(unsigned, RDFTriplePool *,unsigned &);
    RDFTriplePool generateJournals(unsigned,unsigned &);
    RDFTriplePool generateArticles(unsigned, RDFTriplePool *,unsigned &);
    RDFTriplePool generateOthers(unsigned,unsigned &,unsigned &,unsigned &,
									unsigned &,unsigned &);
    RDFTriplePool generateAuthor(unsigned);
    unsigned store(vector <char *>);
    
    CmdLine *cmd;
    OutputLimitMgr olm;
    ActiveAuthors* auths; // permanent pool
    MissingCites missingcites; // permanent pool
};

#endif // GENERATOR_H
