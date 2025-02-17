//
// C++ Interface: RDFTriple
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#ifndef RDFTRIPLE_H
#define RDFTRIPLE_H

#include <vector>
#include <iostream>
#include "rdfobject.h"

#ifdef LOGMODE
#include "instancelogger.h"

#define LOGID_PROCEEDING 1
#define LOGID_INPROCEEDING 2
#define LOGID_JOURNAL 3
#define LOGID_ARTICLE 4
#define LOGID_BOOK 5
#define LOGID_PHD 6
#define LOGID_MASTERS 7
#define LOGID_WWW 8
#define LOGID_INCOLLECTION 9
#define LOGID_AUTHOR 10
#define LOGID_EDITOR 11
#endif

using namespace std;

/**
@author Michael Schmidt, Christoph Pinkel
*/
class RDFTriple
{
public:
    RDFTriple();
    
    virtual ~RDFTriple();
    int getSize();
    char * print();
    vector <RDFTriple *> * getRelated();
    void removeRelated(unsigned i);
    vector <RDFTriple *> recursivePool();
    void addRelated(RDFTriple *, bool = true);
    RDFObject * getSubjectPtr();
    RDFObject * getPrePtr();
    RDFObject * getObjPtr();
    inline bool requirement(unsigned i) { return require[i]; }

    #ifdef LOGMODE
    void setLogId(unsigned id) { logid = id; }
    unsigned logId() { return logid; }
    #endif
    
    virtual void uncalc();

protected:
    virtual bool calc() = 0;
    virtual void init() {};
    void setObjs(RDFObject *, RDFObject *, RDFObject *);
    
    bool require[5];

    bool is_inited;

private:
    void update();

    bool is_changed;
    bool is_complete;
    bool is_printed;
    int t_size;
    vector <RDFObject *> t_obj;
    
    vector <RDFTriple *> explicit_relations;
    vector <bool> existential_relations;
    
    #ifdef LOGMODE
    unsigned logid;
    #endif
};

#endif
