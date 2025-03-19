/*
 | ~~~ SPARQL Benchmark Generator ~~~
 | Author: Michael Schmidt, Christoph Pinkel
*/

#include "stdio.h"
#include <iostream>
#include <unistd.h>
#include "generator.h"
#include "cmdline.h"
#include "default.h"
#include "version.h"
#include "namepoolmgr.h"
#include "gaussiandistribution.h"
#include <time.h>
#include <sys/time.h>
#include "namemgr.h"

using namespace std;

void printVersionNumber() {
    cout << "Thank you for using 'RPQBench' v" << VERSION_NUMBER
        << "!" << endl;
}

void usage() {
    cout << "Usage: "
        << " [BREAK_CONDITION] [OUTFILE], where" << endl << endl;
    cout << "BREAK_CONDITION (choose one of the following):" << endl;
    cout << "-t n\t\t-> produces n triples "
            << "[DEFAULT, with n=50000 triples]" << endl;
    cout << "-s n\t\t-> produces n KB of data " << endl;
    cout << "OUTFILE: name of the output file [DEFAULT='rpqbench.n3']"
            << endl;
}

#include "author.h"

int main(int argc, char **argv)
{
    printVersionNumber();

    //setting up cmdline object...
    CmdLine cmd;
    if(! cmd.parse(argc,argv))
    {
        usage();
        exit(1);
    } //if

    //reading name files (by accessing name mgr for 1st time)
    cout << "reading name files..." << endl;
    NamePoolMgr::getInstance();
    NameMgr::initializeInstance(
        NamePoolFile::getInstance(NamePoolFile::givenNames)->getSize(),
        NamePoolFile::getInstance(NamePoolFile::familyNames)->getSize());
 
    //setting up output generator...
    Generator g(&cmd);

    //generating output...
    #ifdef LOGMODE
    struct timeval t;
    gettimeofday(&t,NULL);
    cout << "===== STARTUP TIME " << t.tv_sec << "." << t.tv_usec << endl;
    #endif // LOGMODE

    cout << "##### Starting data generation..." << endl;
    g.generate();
    cout << "##### Finished: result written to file '"
            << cmd.getOutFileName() << "'!" << endl;

    #ifdef LOGMODE
    cout << "---> " << NameMgr::getInstance()->getNrUsedNames()
            << " author names have been consumed!" << endl;
    gettimeofday(&t,NULL);
    cout << "===== FINISH TIME " << t.tv_sec << "." << t.tv_usec << endl;
    #endif // LOGMODE
    
    delete NamePoolMgr::getInstance();
    return 0;
}
