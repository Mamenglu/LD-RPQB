//
// C++ Implementation: Generator 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "generator.h"
#include <set>

/*!
    Constructor
*/
Generator::Generator(CmdLine* _cmd)
    : cmd(_cmd), olm(_cmd), auths(new ActiveAuthors()), missingcites()
{
}

Generator::~Generator()
{
    auths->retire(auths->count());
    delete auths;
}

/*!
    \fn Generator::generate(unsigned)
    Generates all information and stores it on the disk
 */
void Generator::generate()
{
    //creating/cleaning output file, filling with prefixes...
    FILE *f = fopen(cmd->getOutFileName(), "w+");
    fputs("@prefix dc: <http://purl.org/dc/elements/1.1/> .\n", f);
    fputs("@prefix dcterms: <http://purl.org/dc/terms/> .\n", f);
    fputs("@prefix rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n", f);
    fputs("@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n", f);
    fputs("@prefix swrc: <http://swrc.ontoware.org/ontology#> .\n", f);
    fputs("@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n", f);
    fputs("@prefix bench: <http://localhost/vocabulary/bench/> .\n", f);
    fputs("@prefix rel: <http://localhost/vocabulary/rel/> .\n", f);
    fputs("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .\n", f);
    fputs("@prefix person: <http://localhost/persons/> .\n", f);
    fputs("bench:Journal rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Proceedings rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Inproceedings rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Article rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Www rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:MastersThesis rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:PhDThesis rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Incollection rdfs:subClassOf foaf:Document.\n", f);
    fputs("bench:Book rdfs:subClassOf foaf:Document.\n", f);
    fputs("<http://localhost/persons/Paul_Erdoes> rdf:type foaf:Person.\n",f);
    fputs("<http://localhost/persons/Paul_Erdoes> foaf:name \"Paul Erdoes\"^^xsd:string.\n",f);
    fputs("<http://localhost/persons/WangHui> rdf:type foaf:Person.\n",f);
    fputs("<http://localhost/persons/WangHui> foaf:name \"Wang Hui\"^^xsd:string.\n",f);
    fputs("<http://localhost/misc/UnknownDocument> rdf:type foaf:Document.\n",f);
    fclose(f);

    olm.add(14, 1213); //register nr triples + prefix & def. triple byte size

    //computing output year by year, starting at DBLP_STARTYEAR 
    unsigned long year = DBLP_STARTYEAR;
    
    unsigned long int total_triples=0;
    unsigned long int total_kb=0;

    // keep track of total number of document class instances
    unsigned total_nr_inproceedings=0;
    unsigned total_nr_proceedings=0;
    unsigned total_nr_articles=0;
    unsigned total_nr_journals=0;
    unsigned total_nr_incollections=0;
    unsigned total_nr_books=0;
    unsigned total_nr_wwws=0;
    unsigned total_nr_masterstheses=0;
    unsigned total_nr_phdtheses=0;
    unsigned total_incoming_cites=0; // incoming citations up to now
    unsigned total_pathLength_one=0; // Number of paths whose length is 1
    unsigned total_pathLength_two=0; // Number of paths whose length is 2
    unsigned total_pathLength_three=0; // Number of paths whose length is 3
    unsigned total_pathLength_four=0; // Number of paths whose length is 4
    unsigned total_pathLength_five=0; // Number of paths whose length is 5
    unsigned total_pathLength_six=0; // Number of paths whose length is 6
    unsigned total_pathLength_seven=0; // Number of paths whose length is 7
    unsigned total_pathLength_eight=0; // Number of paths whose length is 8
    unsigned total_pathLength_nine=0; // Number of paths whose length is 9
    unsigned total_pathLength_ten=0; // Number of paths whose length is 10
    unsigned total_pathLength_eleven=0; // Number of paths whose length is 11


    while(! olm.outputComplete())
    {
        cout << "### Calculating document contents for year "
            << year << "..." << endl;
        generateYear(year,total_nr_inproceedings,total_nr_proceedings,
                        total_nr_articles,total_nr_journals,
                        total_nr_incollections,total_nr_books,
                        total_nr_wwws,total_nr_masterstheses,
                        total_nr_phdtheses,total_incoming_cites,
                        total_pathLength_one,total_pathLength_two,
                        total_pathLength_three,total_pathLength_four,
                        total_pathLength_five,total_pathLength_six,
                        total_pathLength_seven,total_pathLength_eight,
                        total_pathLength_nine,total_pathLength_ten,
                        total_pathLength_eleven
                        );

        // calculate and print some statistics for the current year  
        unsigned long int new_total_triples=olm.getTotalTriples();
        unsigned long int new_total_kb=olm.getTotalKB();
     
        cout << "[" << year << "] Triples in year="
                << new_total_triples-total_triples
                << " ---> total triples=" << new_total_triples << endl;
        cout << "[" << year << "] Data written in year="
                << new_total_kb-total_kb << "KB"
                << " ---> total file size=" << new_total_kb << "KB" << endl;

        #ifdef LOGMODE
        cout << "-----------------------------------------------------------" << endl;
        cout << "[" << year << "] total nr inproceedings up to date="
            << total_nr_inproceedings << endl;
        cout << "[" << year << "] total nr proceedings up to date="
                << total_nr_proceedings << endl;
        cout << "[" << year << "] total nr pathlength_one up to date="
                << total_pathLength_one << endl;
        cout << "[" << year << "] total nr pathlength_two up to date="
                << total_pathLength_two << endl;
        cout << "[" << year << "] total nr pathlength_three up to date="
                << total_pathLength_three << endl;
        cout << "[" << year << "] total nr pathlength_four up to date="
                << total_pathLength_four << endl;
        cout << "[" << year << "] total nr pathlength_five up to date="
                << total_pathLength_five << endl;
        cout << "[" << year << "] total nr pathlength_six up to date="
                << total_pathLength_six << endl;
        cout << "[" << year << "] total nr pathlength_seven up to date="
                << total_pathLength_seven << endl;
        cout << "[" << year << "] total nr pathlength_eight up to date="
                << total_pathLength_eight << endl;
        cout << "[" << year << "] total nr pathlength_nine up to date="
                << total_pathLength_nine << endl;
        cout << "[" << year << "] total nr pathlength_ten up to date="
                << total_pathLength_ten << endl;
        cout << "[" << year << "] total nr pathlength_eleven up to date="
                << total_pathLength_eleven << endl;
        cout << "[" << year << "] total nr articles up to date="
                << total_nr_articles << endl;
        cout << "[" << year << "] total nr journals up to date="
                << total_nr_journals << endl;
        cout << "[" << year << "] total nr incollections up to date="
                << total_nr_incollections << endl;
        cout << "[" << year << "] total nr books up to date="
                << total_nr_books << endl;
        cout << "[" << year << "] total nr wwws up to date="
                << total_nr_wwws << endl;
        cout << "[" << year << "] total nr masterstheses up to date="
                << total_nr_masterstheses << endl;
        cout << "[" << year << "] total nr phdtheses up to date="
                << total_nr_phdtheses << endl;
        cout << "[" << year << "] total incoming cites up to next year="
                << total_incoming_cites << endl;
        #endif // LOGMODE
        cout << endl;

		// store values for current year 
        total_triples=new_total_triples;
        total_kb=new_total_kb;

        year++;
    } //while

} //generate()


//一些用得到的池
//dc:creator
RDFTriplePool creator_pool;
//dcterms:coauthor 
RDFTriplePool coauthor_pool;
//存的是 coauthor 最后面的那个宾语 author类
RDFTriplePool coauthor_back_pool;
//存的是 coauthor 最前面的那个宾语 author类
RDFTriplePool coauthor_front_pool;
//存的是 reference-cite 最前面的那个宾语的string
vector <char *> ref_cite_front_pool;
//存的是 reference-cite 最后面的那个宾语的string
vector <char *> ref_cite_back_pool;
//存放uri cite后面跟的Uri
vector <char*> cite_uri;
//dcterms:affect 
RDFTriplePool affect_pool;
//存的是 affect 最后面的那个宾语 author类
RDFTriplePool affect_back_pool;
//存的是 affect 最前面的那个宾语 author类
RDFTriplePool affect_front_pool;
//存的是ref_cite 后面那个uri
vector <char *> uriuris_1;
//存的是ref_cite_ref_cite 后面那个uri
vector <char *> uriuris_2;
//存的是ref_cite_ref_cite_ref_cite 后面那个uri
vector <char *> uriuris_3;
//存的是ref_cite_ref_cite_ref_cite_ref_cite 后面那个uri
vector <char *> uriuris_4;
//存的是ref_cite_ref_cite_ref_cite_ref_cite_ref_cite 后面那个uri
vector <char *> uriuris_5;
//存的是 coauthor-affect-name 最前面的那个宾语 author类
RDFTriplePool coauthor_affect_front_pool;
//存的是 partof_editor_affect 最后面的那个宾语 author类
RDFTriplePool partof_editor_affect_back_pool;
//存的是 partof_editor_affect 最前面的那个宾语 inproceeding类
RDFTriplePool partof_editor_affect_front_pool;



/*!
    \fn Generator::generateYear(unsigned)
    Generates new library information/new entries for specified year
 */
void Generator::generateYear(unsigned year,
                                unsigned &total_nr_inproceedings,
                                unsigned &total_nr_proceedings,
                                unsigned &total_nr_articles,
                                unsigned &total_nr_journals,
                                unsigned &total_nr_incollections,
                                unsigned &total_nr_books,
                                unsigned &total_nr_wwws,
                                unsigned &total_nr_masterstheses,
                                unsigned &total_nr_phdtheses,
								unsigned &total_incoming_cites,
                                unsigned &total_pathLength_one,
                                unsigned &total_pathLength_two,
                                unsigned &total_pathLength_three,
                                unsigned &total_pathLength_four,
                                unsigned &total_pathLength_five,
                                unsigned &total_pathLength_six,
                                unsigned &total_pathLength_seven,
                                unsigned &total_pathLength_eight,
                                unsigned &total_pathLength_nine,
                                unsigned &total_pathLength_ten,
                                unsigned &total_pathLength_eleven
                                )
{
Document::numoftotalpage = 0;
Document::numoftotalabstract = 0;
Document::numoftotalpartof = 0;
char *powerauthor_uri = "<http://localhost/persons/Paul_Erdoes>";
char *wh_uri = "<http://localhost/persons/WangHui>";
unsigned pa_yr_cnt = 0; //power author paper count; power author doesn't care for
    //co author relations, triple or size constraints and publishes 10 papers every year

    //conferences, journals
    RDFTriplePool c_pool = generateConferences(year,total_nr_proceedings);
    //     if (c_pool.count() > 0) {
    //     cout << c_pool.count() <<endl;
    //     RDFTriple* triple = c_pool.getAt(0); // 获取第一个元素
    //     if (triple->getSize()>0) { // 确保获取成功
    //         cout<<"cc triple   "<<triple->getSize()<<endl;
    //         char* output = triple->print(); // 调用 print 方法
    //         // cout << "cc"<< endl;
    //         // cout << output << endl; // 输出返回的字符串
    //         // cout << "cc"<< endl;
    //         delete[] output; // 释放 print 方法分配的内存
    //     } else {
    //         cout << "Triple is nullptr." << endl;
    //     }
    // } else {
    //     cout << "c_pool is empty." << endl;
    // }
    RDFTriplePool j_pool = generateJournals(year,total_nr_journals);

    //books, incoll, phd, masters, www
    RDFTriplePool other_pool = generateOthers(year,total_nr_incollections,
                                                total_nr_books,total_nr_wwws,
                                                total_nr_masterstheses,total_nr_phdtheses);
    
    //talks, articles, also considering their relations to conferences, journals
    RDFTriplePool t_pool = generateInProceedings(year, &c_pool,total_nr_inproceedings);
    
    RDFTriplePool a_pool = generateArticles(year, &j_pool,total_nr_articles);

    
    RDFTriplePool garbage_pool = RDFTriplePool();

    //populating garbage collection:
    garbage_pool.addPool(&j_pool);
    garbage_pool.addPool(&other_pool);
    garbage_pool.addPool(&t_pool);
    garbage_pool.addPool(&a_pool);

    //authors
    //estimation of author numbers/counts...
    unsigned anum_distinct = Functions::nrDistinctAuthors(year);
    unsigned anum_returning = anum_distinct - Functions::nrNewAuthors(year);
    unsigned anum_new = Functions::nrNewAuthors(year);

    //pooling all publications that might require an author
    RDFTriplePool publication_pool;
    publication_pool.addPool(&t_pool);
    publication_pool.addPool(&a_pool);
    publication_pool.addPool(&other_pool);

    //pooling authors to work with...
    vector<Author *> picked_authors = auths->draw(anum_returning);

    auths->insertNew(anum_new, picked_authors, year);

    //getting numbers of authors, with i publications in this year each
    vector <unsigned> authors_with_publs;

    double param=Functions::fitAuthorsWithNumPublicationsParameter(year);
    for(unsigned i = 1; Functions::authorsWithNumPublications(i,year,param) > 0; i++)
        authors_with_publs.push_back(Functions::authorsWithNumPublications(i,year,param));

    #ifdef LOGMODE
    vector <unsigned> authors_with_publs_copy = authors_with_publs;
    #endif

    //assigning properties number of publ count, co-author count, distinct co-author count
    //(within this year) to authors:
    unsigned pcnt = authors_with_publs.size() - 1; //starting to assign max publications
    for(unsigned i = 0; i < picked_authors.size(); i++)
    {
        //number of publications:
        if(authors_with_publs[pcnt] == 0)
            pcnt--;

        picked_authors[i]->assignPublExp(pcnt+1);
        authors_with_publs[pcnt]--;
            
        //expectation value for co-authors (for particular author up to this year)
        double mu_coauth = Functions::muCoauth(picked_authors[i]->publications()
            + picked_authors[i]->expectedPublications());
        double mu_dist_coauth = Functions::muDistCoauth((unsigned)mu_coauth);
        
        int coauth_delta = (unsigned)mu_coauth - picked_authors[i]->coAuthors();
        int dist_coauth_delta = (unsigned)mu_dist_coauth
            - picked_authors[i]->distinctCoAuthors();
    
        if(coauth_delta < 0) coauth_delta = 0; //just in case, should not happen
        if(dist_coauth_delta < 0) dist_coauth_delta = 0;
        
        if(dist_coauth_delta > coauth_delta)
            dist_coauth_delta = coauth_delta; //this can happen in early years
        
        picked_authors[i]->assignCoauthExp((unsigned)coauth_delta);
        picked_authors[i]->assignDCoauthExp((unsigned)dist_coauth_delta);
        
    } //for

    
    //getting numbers for authors per paper expectation...
    GaussianDistribution probAuth(1,Functions::probAuthExpectation(year),
        Functions::probAuthVariance(year));    
    
    
    /* plan: handling papers one by one, trying to satisfy
        distinct co-author property for all selected authors as early as possible, then
        total co-authors */
    vector <unsigned> first_poses; //positions to start searching in
        //authors vecor for papers requiring INDEX distinct co authors
        //(gets initialized to 0 for each index when first used, then
        //increases while we're learning from failure)
    vector<vector<Author *> > coauthor_group;
    coauthor_group.resize(publication_pool.count());
    unsigned numofAuthor = 0;
    for(unsigned i = 0; i < publication_pool.count(); i++)
    {
    unsigned auth_num = probAuth.getRandomnizedValue();

        /* picking auth_num authors (preferring those who can accept at least
           auth_num new co authors) */
        vector <Author *> workgroup;
        vector <unsigned> nondistinct;
        int wanted_distinct = auth_num-1;

        do
        {
            /* trying to find author who expects at least wanted_distinct new distinct 
               co authors AND who is distinct to all previously selected authors, OR
               who is not distinct to all of them but expects at least "delta" more
               non-distinct co authors (and all previously choosen authors also have
               a pending delta of at least one) */
            while(first_poses.size() < (unsigned)wanted_distinct + 1)
                first_poses.push_back(0);
            unsigned first_possible_pos = first_poses[wanted_distinct];
                //first pos where we could
                //find an author with expected disctinct coAuths >=
                //wanted_distinct

            for(unsigned ii = first_possible_pos; ii < picked_authors.size()
                && workgroup.size() < auth_num; ii++)
            {
            
                //expecting at least wanted_distinct (additional) new distinct co authors this year?
                //also need to check whether one or more publications are expected for this author
                if(picked_authors[ii]->expectedDCoauths() >= (unsigned)wanted_distinct
                    && picked_authors[ii]->expectedPublications())
                {
                    //distinct to how many of the previously picked authors? - and (where not)
                    //could those other authors accept one more non-distinct author?
                    bool distinct_to_all = true;
                    bool acceptable = true;
                    for(unsigned iii = 0; iii < workgroup.size(); iii++)
                    {
                        if(workgroup[iii] == picked_authors[ii])
                        { //can't have the same author twice
                            acceptable = false;
                            break;
                        }
                        
                        if(workgroup[iii]->haveCoAuthor(picked_authors[ii]))
                        {
                            distinct_to_all = false;
                            if(! nondistinct[iii])
                            {
                                acceptable = false;
                                break;
                            } //if
                        } //if
                    } //for
                    
                    //satisfies all criteria or can be accepted through accepting
                    //non-distinct everywhere?
                    if(acceptable)
                    {
                        //adding author to working group
                        workgroup.push_back(picked_authors[ii]);
                        nondistinct.push_back(picked_authors[ii]->expectedCoauths()
                            - picked_authors[ii]->expectedDCoauths());
                        
                        //decreasing number of (remaining) expected co authors/distinct
                        //co authors for everyone in the working group:
                        for(unsigned iii = 0; iii < workgroup.size() - 1; iii++)
                            if(workgroup[iii]->haveCoAuthor(picked_authors[ii]))
                            { //non-distinct
                                nondistinct[iii]--;
                                nondistinct[nondistinct.size()-1]--;
                            }
                    } //if(acceptable)
                    
                } //if
                else if(first_poses[wanted_distinct] < ii)
                {
                    first_poses[wanted_distinct] = ii;
                }
            } //for
            
            if(wanted_distinct == 0 && workgroup.size() < auth_num)
            { //it all didn't help - need to add some totally new authors, to keep
                //error as small as possible
                
                //adding missing authors as new:
                unsigned delta = auth_num - workgroup.size();
                auths->insertNew(delta, picked_authors, year);

                //assigning all of them with one expected paper, auth_num-1 expected
                //co authors, adding to working group
                for(unsigned ii = picked_authors.size() - delta;
                    ii < picked_authors.size(); ii++)
                {
                    picked_authors[ii]->assignPublExp(1);
                    picked_authors[ii]->assignCoauthExp(auth_num-1);
                    picked_authors[ii]->assignDCoauthExp(auth_num-1);
                    
                    workgroup.push_back(picked_authors[ii]);
                    nondistinct.push_back(0); //it's all 0 for them
                }
            } //if
            
            /* the "n" distinct expected property is not satisfiable anymore with this
               algorithm, step down by one to go ahead and keep error as small as possible:*/
            wanted_distinct--;

        } while(workgroup.size() < auth_num);
        
        //now we have a working group for this publication assigned:
        for(unsigned ii = 0; ii < workgroup.size(); ii++)
        {
            //assigning co authors to each other (thereby decreasing number of
            //(remaining) expected co authors/distinct co authors
            for(unsigned iii = 0; iii < workgroup.size(); iii++)
                if(iii != ii)
                    workgroup[ii]->addCoAuthor(workgroup[iii]);
                    
            //adding publication/decreasing publication expectation
            workgroup[ii]->addPublication();
            
            //relating all authors with the publication (triple printing relation, non-dependant)
            publication_pool.getAt(i)->addRelated(workgroup[ii], false);
            
            //creating the paper-author relation triples and relating them
            //to papers (dependant relation)
            publication_pool.getAt(i)->addRelated(
                workgroup[ii]->createPublicationRelationTriple(publication_pool.getAt(i)),
                true);
            numofAuthor++;

        } //for(working group)

        if(pa_yr_cnt < 10 && year <= 1996) //for ten papers each year, up to 1996
        {
            BlindRDFTriple *bt = new BlindRDFTriple(powerauthor_uri, "", "");
            PropertyAuthor *ppp = new PropertyAuthor(publication_pool.getAt(i), bt);
            publication_pool.getAt(i)->addRelated(ppp, true);
            creator_pool.add(ppp);
            numofAuthor++;
            delete bt;
    
            pa_yr_cnt++;
        }
        for(int k = 0;k<workgroup.size();k++){
            // RDFObject *temp = (*workgroup[k]).getSubjectPtr();
            coauthor_group[i].push_back(workgroup[k]);
        }
        

    } //for(all papers)


    //powerauthor as editor:
    for(unsigned pa_ed = 0; pa_ed < 2; pa_ed++)
    {
        if(year > 1996) break;

        if(c_pool.count() <= pa_ed)
            break;

        c_pool.getAt(pa_ed)->addRelated(new PropertyEditor(
            c_pool.getAt(pa_ed), powerauthor_uri), true);
    }

    #ifdef LOGMODE
    vector <unsigned> real_a_with_publ;
    for(unsigned i = 0; i < picked_authors.size(); i++)
    {
        //calculating number of publications in this year
        unsigned publ_num = picked_authors[i]->origExpectedPublications()
            - picked_authors[i]->expectedPublications();
    
        //make sure that vector is large enough
        while(real_a_with_publ.size() <= publ_num)
            real_a_with_publ.push_back(0);
        
        real_a_with_publ[publ_num]++; //increase for this author
    } //for

    char *fn = StringTools::numStr("log/publicationsperauthor", year);
    FILE *f = fopen(fn, "a+");
    delete[] fn;
    
    if(f == 0L)
    {
        cout << "fatal error: failed to access log file in ./log/ for writing" << endl;
        exit(2);
    }
    
    unsigned real=0;
    for(unsigned i = 0; i < real_a_with_publ.size()
        && i < authors_with_publs_copy.size(); i++)
    {
    unsigned exp_num = 0;
    unsigned real_num = 0;
    
        if(i < authors_with_publs_copy.size() && i > 0)
            exp_num = authors_with_publs_copy[i-1];
        
        if(i < real_a_with_publ.size())
            real_num = real_a_with_publ[i];
        
        char *cs = StringTools::numStr("", i);
        char *ens = StringTools::numStr(" ", exp_num);
        char *rns = StringTools::numStr(" ", real_num);

        fputs(cs, f);
        fputs(ens, f);
        fputs(rns, f);
        fputs("\n", f);
        
        delete[] cs;
        delete[] ens;
        delete[] rns;
        real+=i*real_a_with_publ[i];
    } //for
    char *rs = StringTools::numStr("",real);
	delete rs;
    fputs("### TOTAL NUMBER OF AUTHORS = ", f);
    fputs(rs, f);
    fputs("\n", f);
    
    fclose(f);
    #endif

    //adding editors...
    vector <unsigned> editors_with_publs; //editors_with_publs[i] = number of editors with
        //i publications as an author

    for(unsigned i = 0; Functions::editorPublications(i, year); i++)
        editors_with_publs.push_back(Functions::editorPublications(i, year));

    if(editors_with_publs.size() == 0)
        editors_with_publs.push_back(1); //required fallback to have
            //at least one editor at hand
            
    //distribution of repeated editor attribute
    GaussianDistribution prob_edit(1,Functions::probEditExpectation(year),
        Functions::probEditVariance(year));

    vector <Editor *> editors;
    
    //finding appropriate editors from pool (or creating new ones for editors
    //with no publications
    for(unsigned i = 0; i < editors_with_publs[0]; i++)
        //editors with no publications as an author
    {
        Author *dummy = new Author(year);
        editors.push_back(new Editor(dummy,true));
    } //for
    
    for(unsigned i = 1; i < editors_with_publs.size(); i++)
    { //editors with i publications as an author
        
        //getting authors with precise number of publications
        vector <Author *> a_with_n_publ = auths->getMAuthorsWithNPublications(
            editors_with_publs[i], i);
            
        for(unsigned ii = 0; ii < a_with_n_publ.size(); ii++)
            editors.push_back(new Editor(a_with_n_publ[ii]));
            
        //if none (not enough) were available, again use dummies...
        for(unsigned ii = 0; ii < editors_with_publs[i] - a_with_n_publ.size(); ii++)
        {
            Author *dummy = new Author(year);
            editors.push_back(new Editor(dummy,true));
        }

    } //for

    //editor's pool created, now pooling relevant papers and assigning to papers...
    //pooling all publications that might require an editor
    RDFTriplePool editor_publication_pool;
    editor_publication_pool.addPool(&c_pool); //proceedings
    editor_publication_pool.addPool(&j_pool); //journals
    editor_publication_pool.addPool(&other_pool); //others (includes relevant categories
        //"books" and "wwws"
    


    //looping relevant papers...
    unsigned ed_pos = 0;

    for(unsigned i = 0; i < editor_publication_pool.count(); i++)
    {
        if(editor_publication_pool.getAt(i)->requirement(2))
            //requirement(1) == Document::requireEditor()
        {
        unsigned editor_cnt = prob_edit.getRandomnizedValue();

            // enforce (avl editors>=editor_cnt), which may fail in early years
            while (editors.size()<editor_cnt)
            {
                Author *dummy = new Author(year);
                editors.push_back(new Editor(dummy,true));
            }

            //now assigning authors to paper
            for(unsigned ii = 0; ii < editor_cnt; ii++)
            {
                editor_publication_pool.getAt(i)->addRelated(
                    editors[ed_pos]->getRelationTriple(
                        editor_publication_pool.getAt(i)));

                ed_pos++;
                
                if(ed_pos >= editors.size()) ed_pos = 0;
            } //for

        } //if(require editor)
        
    } //for

    //citations
    //number of outgoing citations (distribution; call once for every paper
    // which requires a cite)
    GaussianDistribution prob_cite(1,Functions::probCiteExpectation(year),
        Functions::probCiteVariance(year));
        
    //pooling papers that might require citations
    RDFTriplePool citepapers_pool;
    citepapers_pool.addPool(&t_pool); //inproceedings
    citepapers_pool.addPool(&a_pool); //articles
    citepapers_pool.addPool(&other_pool); //others

    //now assigning outgoing citations...
    unsigned requiring=0;
    for(unsigned i = 0; i < citepapers_pool.count(); i++)
    {
        if(citepapers_pool.getAt(i)->requirement(1)) //== Document::requireCite()
        {
        requiring++;
        unsigned cite_cnt = prob_cite.getRandomnizedValue(); //number of outgoing citations
        
            vector <char *> uris = missingcites.citeSomeURIs(cite_cnt);
            
            ReferenceBag *ref_bag = new ReferenceBag();
            ReferenceBagReference *c = new ReferenceBagReference(
                        citepapers_pool.getAt(i)->getSubjectPtr()->getString(),
                        ref_bag->getSubjectPtr()->getString());
            c->addRelated(ref_bag, true);
            citepapers_pool.getAt(i)->addRelated(c, true);

            unsigned cnum = 1;
            while(cite_cnt)
            {
                PropertyCite *ci;
                
                char * uri = 0L;
                if(uris.size() > 0)
                {
                    uri = uris[uris.size() -1];
                    uris.pop_back();
                }

                if(uri)
                {
                    ci = new PropertyCite(
                        ref_bag->getSubjectPtr()->getString(), cnum, uri);
                    
                    delete[] uri;
                }
                else
                {
                    ci = new PropertyCite(
                        ref_bag->getSubjectPtr()->getString(),
                        cnum, "<http://localhost/misc/UnknownDocument>");
                }
                
                citepapers_pool.getAt(i)->addRelated(ci, true);

                cite_cnt--;
                cnum++;

            } //while
        } //if
    } //for


    /*incoming cites (for some papers) - number of papers with N expected incoming cites;
      nrIncomingCitations() returns the total (historic) number of papers with expected
      N incoming citations.
      As most of the cites that we request this year will be assigned next year, the best
      approximation will be reached by assigning expectations one year earlier.
      We also add up and remember the total number of new papers from this year which
      expect incoming cites, so we can determine a percentage of papers to nominate for
      future incoming cites */
    vector <unsigned> papers_with_cites;
    unsigned total_papers_with_incoming_cites = 0;

    // estimate total nr of outgoing references in next year;
    // we will then use this value to generate a certain percentage of 
    // incoming citation (the other outgoing citations point to
    // UnknownDocument, i.e. refere documents not contained in the data
    // set, just like the original DBLP data set)
    unsigned est_nr_ref=Functions::estimateNrOutgoingReferencesUpTo(year+1,
                                            total_nr_inproceedings,
                                            total_nr_proceedings,
                                            total_nr_articles,
                                            total_nr_journals,
                                            total_nr_incollections,
                                            total_nr_books,
                                            total_nr_wwws,
                                            total_nr_masterstheses,
                                            total_nr_phdtheses,
											prob_cite.getAverage());
    double c_param=Functions::fitNrIncomingCitationsParameter(year+1,est_nr_ref);

    // estimate last year again (we require this again)
    unsigned est_nr_ref_lastyear=Functions::estimateNrOutgoingReferencesUpTo(year,
                                            total_nr_inproceedings-Functions::inproc(year),
                                            total_nr_proceedings-Functions::proc(year),
                                            total_nr_articles-Functions::article(year),
                                            total_nr_journals-Functions::journal(year),
                                            total_nr_incollections-Functions::incoll(year),
                                            total_nr_books-Functions::book(year),
                                            total_nr_wwws-Functions::www(year),
                                            total_nr_masterstheses-Functions::master(year),
                                            total_nr_phdtheses-Functions::phd(year),
											prob_cite.getAverage());
    double c_param_lastyear=Functions::fitNrIncomingCitationsParameter(year,est_nr_ref_lastyear);
    // cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!mml       "<<year<<endl;
    unsigned total_incoming_citations=0;
    for(unsigned i = 1; Functions::nrIncomingCitations(i, year+1, c_param); i++)
    {
    unsigned exp = Functions::nrIncomingCitations(i,year+1,c_param);
    unsigned prev = Functions::nrIncomingCitations(i,year,c_param_lastyear);

        if(exp > prev) {
            exp -= prev;
        } else {
            exp = 0;
        }

        papers_with_cites.push_back(exp);
        total_papers_with_incoming_cites += exp;
        total_incoming_citations+=exp*i;
    }
    total_incoming_cites+=total_incoming_citations;

    //loop again for expected number of (future) incoming citations:
    for(unsigned i = 0; i < citepapers_pool.count(); i++)
    {
        //some papers will also be honoured by incoming citations (in future) ;-)
        if(i >= total_papers_with_incoming_cites)
            break;
        else//(r->getRandomValue(100) <= percent_with_incoming_cites)
        {
            //assigning number of expected incoming cites
            unsigned cinum = 1;
            
            for(unsigned ii = 0; ii < papers_with_cites.size(); ii++)
                if(papers_with_cites[ii])
                {
                    cinum = ii + 1;
                    papers_with_cites[ii]--;
            
                    //adding to list of URI's to which we expect incoming citations later...
                    missingcites.request(
                        citepapers_pool.getAt(i)->getSubjectPtr()->getString(), cinum);
                        //need URI only, plus expected number of incoming citations
                        
                    break;
                }
        }
    } //for

    RDFTriplePool articleInpro_pool;
    RDFTriplePool one_pool = generatePathLengthOne(year,coauthor_group,&articleInpro_pool,&a_pool,numofAuthor,total_pathLength_one);
    RDFTriplePool two_pool = generatePathLengthTwo(year,&a_pool,&citepapers_pool,&articleInpro_pool, total_pathLength_two);
    RDFTriplePool three_pool = generatePathLengthThree(year,&a_pool, total_pathLength_three);
    RDFTriplePool four_pool = generatePathLengthFour(year,&a_pool, total_pathLength_four);
    RDFTriplePool five_pool = generatePathLengthFive(year,total_pathLength_five);
    RDFTriplePool six_pool = generatePathLengthSix(year,total_pathLength_six);
    RDFTriplePool seven_pool = generatePathLengthSeven(year,total_pathLength_seven);
    RDFTriplePool eight_pool = generatePathLengthEight(year,total_pathLength_eight);
    RDFTriplePool nine_pool = generatePathLengthNine(year,total_pathLength_nine);
    RDFTriplePool ten_pool = generatePathLengthTen(year,total_pathLength_ten);
    RDFTriplePool eleven_pool = generatePathLengthEleven(year,total_pathLength_eleven);

    creator_pool.removeAllElement();
    coauthor_pool.removeAllElement();
    affect_pool.removeAllElement();
    coauthor_back_pool.removeAllElement();
    affect_back_pool.removeAllElement();
    coauthor_front_pool.removeAllElement();
    affect_front_pool.removeAllElement();
    ref_cite_front_pool.clear();
    ref_cite_back_pool.clear();
    partof_editor_affect_back_pool.removeAllElement();
    partof_editor_affect_front_pool.removeAllElement();

    cout << "[" << year << "] all contents calculated, now storing...\n";

    /* preparing to write output, starting with conferences/journals/other docs,
        always filling a conference etc completely before proceeding...
        checking limits, skipping some if necessary;
        expect to have all events/publications distributed evenly over the year... */
    float perc_c = 0.0, perc_j = 0.0, perc_o = 0.0; //percentage of conferences,
        //journals (every issue counts), other documents already written

    //percentage delta for each event/publication
    float pd_c = 0;
    if(c_pool.count())
        pd_c = 100.0 / c_pool.count();
    else
        perc_c = 100.0;

    float pd_j = 0;
    if(j_pool.count())
        pd_j = 100.0 / j_pool.count();
    else
        perc_j = 100.0;

    float pd_o = 0;
    if(other_pool.count())
        pd_o = 100.0 / other_pool.count();
    else
        perc_o = 100.0;

    //while some stuff still needs 2b stored...
        while(one_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = one_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            one_pool.removeElement(t);

            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();

            // vector<char *> one_lines = one_pool.printAll();
            // unsigned one_nr_triples=store(one_lines);
            // olm.add(one_nr_triples,one_pool.totalSize());
            // one_pool.uncalcAll();
        }
        while(two_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = two_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            two_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(three_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = three_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            three_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(four_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = four_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            four_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(five_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = five_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            five_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(six_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = six_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            six_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(seven_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = seven_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            seven_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(eight_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = eight_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            eight_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(nine_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = nine_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            nine_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(ten_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = ten_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            ten_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }
        while(eleven_pool.count() && ! olm.outputComplete()){
            RDFTriple * t = eleven_pool.getElement();
            RDFTriplePool unprinted_triples(t->recursivePool());
            vector<char *> lines = unprinted_triples.printAll();
            unsigned nr_triples=store(lines);
            for(unsigned i = 0; i < lines.size(); i++)
                delete[] lines[i];
            eleven_pool.removeElement(t);
            //updating limit manager
            //olm.add(unprinted_triples.count(),
            olm.add(nr_triples,unprinted_triples.totalSize());
            unprinted_triples.uncalcAll();
        }


        while((c_pool.count() || j_pool.count() || other_pool.count())&&! olm.outputComplete())
        {    
            //we try to keep the percentage of all events/singular publications at a
            //similar level, so in case we reach some output limit, their distribution is
            //still realistic
            if(perc_c <= perc_j
                && perc_c <= perc_o)
            {
                //storing unprinted relevant triples
                RDFTriple * t = c_pool.getElement();
                RDFTriplePool unprinted_triples(t->recursivePool());
                vector<char *> lines = unprinted_triples.printAll();
                unsigned nr_triples=store(lines);
                for(unsigned i = 0; i < lines.size(); i++)
                    delete[] lines[i];
                c_pool.removeElement(t);

                //updating limit manager
                //olm.add(unprinted_triples.count(),
                olm.add(nr_triples,unprinted_triples.totalSize());
                unprinted_triples.uncalcAll();
                
                //updating progress percentage
                perc_c += pd_c;

                //cleaning up
                delete t;
            }
            else if(perc_j <= perc_o)
            {
                //storing unprinted relevant triples
                RDFTriple * t = j_pool.getElement();
                RDFTriplePool unprinted_triples(t->recursivePool());
                vector<char *> lines = unprinted_triples.printAll();
                unsigned nr_triples=store(lines);
                for(unsigned i = 0; i < lines.size(); i++)
                    delete[] lines[i];
                j_pool.removeElement(t);
                
                //updating limit manager
                //olm.add(unprinted_triples.count(),
                olm.add(nr_triples,unprinted_triples.totalSize());
                unprinted_triples.uncalcAll();
                
                //updating progress percentage
                perc_j += pd_j;
            }
            else //publication ("other" publication)
            {
                //storing unprinted relevant triples
                RDFTriple * t = other_pool.getElement();
                RDFTriplePool unprinted_triples(t->recursivePool());
                vector<char *> lines = unprinted_triples.printAll();
                unsigned nr_triples=store(lines);
                for(unsigned i = 0; i < lines.size(); i++)
                    delete[] lines[i];
                other_pool.removeElement(t);

                //updating limit manager
                //olm.add(unprinted_triples.count(),
                olm.add(nr_triples,unprinted_triples.totalSize());
                unprinted_triples.uncalcAll();
                
                //updating progress percentage
                perc_o += pd_o;
            }
        } //while

    // } //while

    garbage_pool.addPool(&c_pool);
    garbage_pool.addPool(&one_pool);
    garbage_pool.addPool(&two_pool);
    garbage_pool.addPool(&three_pool);
    garbage_pool.addPool(&four_pool);
    garbage_pool.addPool(&five_pool);
    garbage_pool.addPool(&six_pool);
    garbage_pool.addPool(&seven_pool);
    garbage_pool.addPool(&eight_pool);
    garbage_pool.addPool(&nine_pool);
    garbage_pool.addPool(&ten_pool);
    garbage_pool.addPool(&eleven_pool);
    garbage_pool.destroyElements();

    //authors who retire after this year:
    #ifdef LOGMODE
    cout << "[" << year << "] Active authors=" << auths->count() << endl;
    #endif // LOGMODE
    unsigned anum_retiring = Functions::nrRetiringAuthors(year,auths->count());
    #ifdef LOGMODE
    cout << "[" << year << "] Retiring " << anum_retiring << " authors now..." << endl;
    #endif // LOGMODE
    auths->retire(anum_retiring);
    #ifdef LOGMODE
    cout << "[" << year << "] Remaining authors after retiring=" << auths->count() << endl;
    #endif // LOGMODE

    //dumping editor objects
    for(unsigned i = 0; i < editors.size(); i++)
        delete editors[i];

    #ifdef LOGMODE
    char *fn_coauths = StringTools::numStr("log/histcoauthavg", year);
    f = fopen(fn_coauths, "a+");
    delete[] fn_coauths;

    //log avg number of co authors (life time) for all active authors (non-retired)
    auths->averageCoAuthors();
    
    //log avg number of distinct co authors (life time) for all active authors (non-retired)
    auths->averageDistinctCoAuthors();
    
    fclose(f);
    
    InstanceLogger *l = InstanceLogger::getInstance();
    l->writeLogs(year);
    
    vector<unsigned> incoming_cites = missingcites.getIncomingCiteCounts();
    char *fn_cites = StringTools::numStr("log/citations", year);
    f = fopen(fn_cites, "a+");
    delete[] fn_cites;
    
    if(f == 0L)
    {
        cout << "fatal error: failed to access log file in ./log/ for writing" << endl;
        exit(2);
    }
    
    for(unsigned i = 0; i < incoming_cites.size(); i++)
    {
        char *cns = StringTools::numStr("", i+1);
        char *cis = StringTools::numStr(" ", incoming_cites[i]);

        fputs(cns, f);
        fputs(cis, f);
        fputs("\n", f);

        delete[] cns;
        delete[] cis;
    }
    
    fclose(f);
    #endif //LOGMODE

} //generateYear()


/*!
    \fn Generator::generateConferences(unsigned)
    generates all conference objects for specified year, including the basic attributes
    (added as related triples)
    @return pool with generated triple objects
 */
RDFTriplePool Generator::generateConferences(unsigned year,unsigned & total_nr_proceedings)
{
RDFTriplePool ret;
unsigned cnt = Functions::proc(year);

    // adapt count
    total_nr_proceedings+=cnt;

    for(unsigned i = 0; i < cnt; i++)
    {
    Proceedings * e = new Proceedings(i+1, year);
    // cout << (*e).print() << endl;
        ret.add(e);
    }
    
    return ret;
} //generateConferences()

RDFTriplePool Generator::generatePathLengthOne(unsigned year,vector<vector<Author *> > coauthor_group,RDFTriplePool *articleInpro_pool,RDFTriplePool *a_pool,unsigned & numofAuthor, unsigned & total_pathLength_one)
{
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 180;
    // adapt count
    total_pathLength_one+=cnt/6*6;
    unsigned long int mml= cmd->getSizeValue();
    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    vector<vector<Author *> > coauthor_group_temp = coauthor_group;

    //dcterms:coauthor foaf:name
    int number = 0;
    int au = 0;
    // for(unsigned k = 0; k < coauthor_group_temp.size()&&k<cnt/6 ; k++){
    //     for(unsigned i = 0; i < coauthor_group_temp[k].size()&&i<cnt/6 ; i++)
    //     {
    //         for (unsigned j = i+1; j < coauthor_group_temp[k].size()&&j<cnt/6 ; j++) {
    //             PropertyCoauthor * p = new PropertyCoauthor(coauthor_group_temp[k][i],coauthor_group_temp[k][j]);
    //             number++;
    //             ret.add(p);
    //         }
    //     }
    // }
    // for (unsigned k = 0; k < coauthor_group_temp.size(); k++) {
    //     for (unsigned i = 0; i < coauthor_group_temp[k].size(); i++) {
    //         for (unsigned j = i + 1; j < coauthor_group_temp[k].size(); j++) {
    //             if(coauthor_group_temp[k][i] != NULL && coauthor_group_temp[k][j] != NULL){
    //                 Author *a_temp1 = new Author(year);
    //                 Author *a_temp2 = new Author(year);
    //                 // RDFTriple *temp1 = static_cast<RDFTriple *>(a_temp1);
    //                 // RDFTriple *temp2 = static_cast<RDFTriple *>(a_temp2);
    //                 PropertyCoauthor *p = new PropertyCoauthor(a_temp1, a_temp2);
    //                 number++;
    //                 ret.add(p);
    //                 // delete a_temp1;
    //                 // delete a_temp2;
    //             }
    //         }
    //     }
    // }

    // if(number < cnt/6){
        // if(static_cast<int>(coauthor_group_temp[0].size()) - 1 == 0){
        //     Author * a = new Author(year);
        //     PropertyCoauthor * p = new PropertyCoauthor(a,coauthor_group_temp[0][0]);
        //     number++;
        //     ret.add(a);
        //     ret.add(p);
        // }

    int count = (cnt/6)/coauthor_group_temp.size();
    count += 1;
    // Author *a = coauthor_group_temp[0][0];

    bool shouldStop = false;
    for(int k = 0;k < coauthor_group_temp.size() && !shouldStop; k++){
        for(int i = 0;i<count;i++){
            Author * a = new Author(year);
            if((i+1+allauthor)>cnt/6){
                vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
                int size = (*relatedvecRDF).size();
                for(int i = 0;i<size;i++){
                    RDFTriple * relatedRDF = (*relatedvecRDF)[i];
                    RDFObject * rdfpre = (*relatedRDF).getPrePtr();
                    if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
                    {
                        (*a).removeRelated(i);
                    }
                }
            }
            au++;

            // Author * b = new Author(year);
            // ret.add(b);
            ret.add(a);
            
            // same_year_author.push_back(new Author(year));
            // int mina = min(i-number, static_cast<int>(coauthor_group_temp[0].size()) - 1);
            // PropertyCoauthor * p = new PropertyCoauthor(coauthor_group_temp[0][mina],a);
            PropertyCoauthor * p = new PropertyCoauthor(coauthor_group_temp[k][0],a);
            number++;
            if (number > cnt/6) {
                shouldStop = true; // 设置标志位为 true，将退出所有循环
                break; // 立即退出内部循环
            }
            coauthor_pool.add(p);
            coauthor_back_pool.add(a);
            coauthor_front_pool.add(coauthor_group_temp[k][0]);
            ret.add(p);
        }
    }

    // for(int i = 0;i<cnt/6;i++){
    //     Author * a = new Author(year);
    //     if((i+1+allauthor)>cnt/6){
    //         vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
    //         int size = (*relatedvecRDF).size();
    //         for(int i = 0;i<size;i++){
    //             RDFTriple * relatedRDF = (*relatedvecRDF)[i];
    //             RDFObject * rdfpre = (*relatedRDF).getPrePtr();
    //             if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
    //             {
    //                 (*a).removeRelated(i);
    //             }
    //         }
    //     }
    //     au++;

    //     Author * b = new Author(year);
    //     ret.add(b);
    //     ret.add(a);
        
    //     // same_year_author.push_back(new Author(year));
    //     // int mina = min(i-number, static_cast<int>(coauthor_group_temp[0].size()) - 1);
    //     // PropertyCoauthor * p = new PropertyCoauthor(coauthor_group_temp[0][mina],a);
    //     PropertyCoauthor * p = new PropertyCoauthor(b,a);
    //     coauthor_pool.add(p);
    //     coauthor_back_pool.add(a);
    //     coauthor_front_pool.add(b);
    //     ret.add(p);
    // }
    // }


    //dc:creator
    int nAuthor = numofAuthor;    
    //swrc:pages bench:abstract
    int pk = 0;
    int numoftotalpage = Document::numoftotalpage;
    int numoftotalabstract = Document::numoftotalabstract;
    Article * arc = static_cast<Article*>(static_cast<Document*>((*a_pool).getAt(acnt-1)));
    unsigned numofj = (*arc).getjnum();
    Journal *j = new Journal(numofj+1,year);
    ret.add(j);
    int numnum = 0;
    while(numoftotalpage < cnt/6){
        Article * a = new Article(pk+1,year,numofj+1);
        cite_uri.push_back((*(*a).getSubjectPtr()).getString());
        (*articleInpro_pool).add(a);
        if(nAuthor < cnt/6){
            Author * authortemp = new Author(year);
            if(numnum <3){
                NamePoolMgr *npm = NamePoolMgr::getInstance();
                char *sstr = StringTools::concatStrs("_:",
                            npm->getNameById(NamePoolFile::givenNames,(*authortemp).getGivenName()),
                            "_",
                            npm->getNameById(NamePoolFile::familyNames,(*authortemp).getLastName()));
                PropertyEditor *edi = new PropertyEditor(j,sstr);
                ret.add(edi);
                numnum++;
            }
            vector <RDFTriple *> * relatedvecRDF = (*authortemp).getRelated();
            int size = (*relatedvecRDF).size();
            for(int i = 0;i<size;i++){
                RDFTriple * relatedRDF = (*relatedvecRDF)[i];
                RDFObject * rdfpre = (*relatedRDF).getPrePtr();
                if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
                {
                    (*authortemp).removeRelated(i);
                }
            }
            nAuthor++;
            PropertyAuthor *pauthor = new PropertyAuthor(a,authortemp);
            creator_pool.add(pauthor);
            ret.add(pauthor);
        }
        PropertyJournal *pj = new PropertyJournal(a,j);
        RDFTriple * rdf = a;
        vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
        int size = (*relatedvecRDF).size();
        int tempp = 0;
        int tempa = 0;
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if (!strncmp("bench:abstract", (*rdfpre).getString(), 14))
            {
                //相等，‘bench:abstract’共14个字符，与line串判断前14个字符。
                tempa = 1;
                // break;
            }
            if (!strncmp("swrc:pages", (*rdfpre).getString(), 10))
            {
                //相等，‘swrc:pages’共10个字符，与line串判断前10个字符。
                tempp = 1;
                // break;
            }
        }
        if(tempp==0){
            PropertyPage *p = new PropertyPage(a);
            ret.add(p);
        }
        if(tempa==0){
            PropertyAbstract *ab = new PropertyAbstract(a);
            ret.add(ab);
        }
        ret.add(a);
        ret.add(pj);
        pk++;
        numoftotalpage++;
    }
    while(numoftotalabstract+pk < cnt/6){
        Article * a = new Article(pk+1,year,numofj+1);
        cite_uri.push_back((*(*a).getSubjectPtr()).getString());
        (*articleInpro_pool).add(a);
        if(nAuthor < cnt/6){
            Author * authortemp = new Author(year);
            vector <RDFTriple *> * relatedvecRDF = (*authortemp).getRelated();
            int size = (*relatedvecRDF).size();
            for(int i = 0;i<size;i++){
                RDFTriple * relatedRDF = (*relatedvecRDF)[i];
                RDFObject * rdfpre = (*relatedRDF).getPrePtr();
                if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
                {
                    (*authortemp).removeRelated(i);
                }
            }
            nAuthor++;
            PropertyAuthor *pauthor = new PropertyAuthor(a,authortemp);
            creator_pool.add(pauthor);
            ret.add(pauthor);
        }
        PropertyJournal *pj = new PropertyJournal(a,j);
        RDFTriple * rdf = a;
        vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
        int size = (*relatedvecRDF).size();
        // int tempp = 0;
        int tempa = 0;
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if (!strncmp("bench:abstract", (*rdfpre).getString(), 14))
            {
                //相等，‘bench:abstract’共14个字符，与line串判断前14个字符。
                tempa = 1;
                // break;
            }
            if (!strncmp("swrc:pages", (*rdfpre).getString(), 10))
            {
                //相等，‘swrc:pages’共10个字符，与line串判断前10个字符。
                // tempp = 1;
                (*a).removeRelated(i);
                break;
            }
        }
        if(tempa==0){
            PropertyAbstract *ab = new PropertyAbstract(a);
            ret.add(ab);
        }
        ret.add(a);
        ret.add(pj);
        pk++;
    }

    //dcterms:partOf
    int numoftotalpartof = Document::numoftotalpartof;
    int temp = 0;
    Proceedings *pro = new Proceedings(pcnt+1,year);
    int numnumnum = 0;
    while(numoftotalpartof+temp < cnt/6){
        Inproceedings * e = new Inproceedings(temp+1, year, pcnt+1);
        cite_uri.push_back((*(*e).getSubjectPtr()).getString());
        (*articleInpro_pool).add(e);
        if(nAuthor < cnt/6){
            Author * authortemp = new Author(year);
            if(numnumnum <3){
                NamePoolMgr *npm = NamePoolMgr::getInstance();
                char *sstr = StringTools::concatStrs("_:",
                            npm->getNameById(NamePoolFile::givenNames,(*authortemp).getGivenName()),
                            "_",
                            npm->getNameById(NamePoolFile::familyNames,(*authortemp).getLastName()));
                PropertyEditor *edi = new PropertyEditor(pro,sstr);
                ret.add(edi);
                numnumnum++;
            }
            vector <RDFTriple *> * relatedvecRDF = (*authortemp).getRelated();
            int size = (*relatedvecRDF).size();
            for(int i = 0;i<size;i++){
                RDFTriple * relatedRDF = (*relatedvecRDF)[i];
                RDFObject * rdfpre = (*relatedRDF).getPrePtr();
                if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
                {
                    (*authortemp).removeRelated(i);
                }
            }
            nAuthor++;
            PropertyAuthor *pauthor = new PropertyAuthor(e,authortemp);
            creator_pool.add(pauthor);
            ret.add(pauthor);
        }
        RDFTriple * rdf = e;
        vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
        int size = (*relatedvecRDF).size();
        int tempp = 0;
        int tempa = 0;
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("bench:abstract", (*rdfpre).getString(), 14))||(!strncmp("swrc:pages", (*rdfpre).getString(), 10)))
            {
                (*e).removeRelated(i);
            }
        }
        PropertyCrossref *t = new PropertyCrossref(e, pro);
        ret.add(e);
        ret.add(t);
        temp++;
    }
    ret.add(pro);

    //dc:creator 如果前面加完之后还缺 再新建article补充
    while(nAuthor < cnt/6){
        Article * a = new Article(pk+1,year,numofj+1);
        cite_uri.push_back((*(*a).getSubjectPtr()).getString());
        (*articleInpro_pool).add(a);
        Author * authortemp = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*authortemp).getRelated();
        int size = (*relatedvecRDF).size();
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*authortemp).removeRelated(i);
            }
        }
        nAuthor++;
        pk++;
        PropertyAuthor *pauthor = new PropertyAuthor(a,authortemp);
        creator_pool.add(pauthor);
        ret.add(a);
        ret.add(pauthor);
    }
    
    return ret;
} //generatePathLengthOne()


RDFTriplePool Generator::generatePathLengthTwo(unsigned year,RDFTriplePool *a_pool,RDFTriplePool *citepapers_pool,RDFTriplePool *articleInpro_pool,unsigned & total_pathLength_two)
{
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 45;
    // adapt count
    total_pathLength_two+=cnt/8*8;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;

    
    // dcterms:references/ dcterms:cite
    int numofref_cite = 0;
    for(int i = 0;i<(*citepapers_pool).count();i++){
        RDFTriple *rr = (*citepapers_pool).getAt(i);
        vector <RDFTriple *> * relatedvecRDF = (*rr).getRelated();
        int size = (*relatedvecRDF).size();
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("dcterms:cite", (*rdfpre).getString(), 12)))
            {
                // (*rr).removeRelated(i);
                numofref_cite++;
            }
        }
    }
    if(numofref_cite<cnt/8){
        unsigned cite_cnt = cnt/8-numofref_cite;
        //前面生成article和inproceeding的时候 就把uri存下来！！！！！！！！！！！！！！！！！！
        // vector <char *> uriuris_1;
        for (int i = 0; i < cite_uri.size(); i++) {
            char* originalStr = cite_uri[i];
            // 为新字符串分配足够的内存
            char* newStr = new char[strlen(originalStr) + 1];
            strcpy(newStr, originalStr); // 复制原字符串到新字符串

            // 在新字符串上进行修改
            for (int j = 0; newStr[j] != '\0'; ++j) {
                if (newStr[j] == '1' && newStr[j+1] == '9' && isdigit(newStr[j+2]) && isdigit(newStr[j+3])) {
                    char yearSubstr[5] = {newStr[j], newStr[j+1], newStr[j+2], newStr[j+3], '\0'};
                    int year = atoi(yearSubstr);
                    if (year >= 1900 && year <= 1999) {
                        year--; // 年份减1
                        snprintf(yearSubstr, sizeof(yearSubstr), "%d", year);
                        newStr[j+2] = yearSubstr[2];
                        newStr[j+3] = yearSubstr[3];
                        // 修改完成，跳过剩余部分
                        break;
                    }
                }
            }
            uriuris_1.push_back(newStr); // 将修改后的新字符串添加到uris列表中
        }
        // vector <char *> uris = missingcites.citeSomeURIs(cite_cnt);
        ReferenceBag *ref_bag = new ReferenceBag();
        ReferenceBagReference *c = new ReferenceBagReference(
                    (*articleInpro_pool).getAt(0)->getSubjectPtr()->getString(),
                    ref_bag->getSubjectPtr()->getString());
        ret.add(c);
        ref_cite_front_pool.push_back((*articleInpro_pool).getAt(0)->getSubjectPtr()->getString());
        unsigned cnum = 1;
        int cite_cnt_num = max(static_cast<int>(cite_cnt),3);
        while(cite_cnt_num)
        {
            PropertyCite *ci;
            
            char * uri = 0L;
            if(uriuris_1.size() > 0)
            {
                uri = uriuris_1[uriuris_1.size() -1];
                uriuris_1.pop_back();
            }

            if(uri)
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(), cnum, uri);
                ref_cite_back_pool.push_back(uri);
                // delete[] uri;
            }
            else
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(),
                    cnum, "<http://localhost/misc/UnknownDocument>");
            }
            
            // citepapers_pool.getAt(i)->addRelated(ci, true);
            //bug可能地
            (*c).addRelated(ci, true);
            ret.add(ci);
            cite_cnt_num--;
            cnum++;
        } //while    
    }

    //dcterms:record/ dc:creator 不会出现creatornum<cnt/8的情况 在加one_pool时候确保了有足够的creatornum
    int creatornum = creator_pool.count();
    for(int i = 0;i< min(creatornum,static_cast<int>(cnt/8));i++){
        Institution * ins = new Institution(i+1,year);
        ret.add(ins);
        RDFObject *o1 = (*creator_pool.getAt(i)).getSubjectPtr();
        RDFObject *oooo = new RDFObject(RDFObject::URIObj,o1->getString());
        PropertyRecord *prorec = new PropertyRecord(ins,oooo);
        //bug
        (*prorec).addRelated(creator_pool.getAt(i),true);
        ret.add(prorec);
    }

    //dcterms:coauthor/ foaf:name
    for(int i = 0;i<cnt/8;i++){
        Author *co = static_cast<Author*>(coauthor_back_pool.getAt(i));   
        vector <RDFTriple *> * relatedvecRDF = (*co).getRelated();
        int size = (*relatedvecRDF).size();
        int temp = 0;
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                temp = 1;
            }
        }
        if(temp == 0){
            PropertyAuthorName *name = new PropertyAuthorName(co, (*co).getGivenName(), (*co).getLastName());\
            ret.add(name);
        }
    }

    //dc:creator/ dcterms:coauthor 从后往前找  用coauthor_pool
    Article * arc = static_cast<Article*>(static_cast<Document*>((*a_pool).getAt(acnt-1)));
    unsigned numofj = (*arc).getjnum();
    Journal *j = new Journal(numofj+2,year);
    ret.add(j);
    Article * a = new Article(1,year,numofj+2);
    RDFTriple * rdf = a;
    vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
    int size = (*relatedvecRDF).size();
    int tempp = 0;
    int tempa = 0;
    for(int j = 0;j<size;j++){
        RDFTriple * relatedRDF = (*relatedvecRDF)[j];
        RDFObject * rdfpre = (*relatedRDF).getPrePtr();
        if ((!strncmp("bench:abstract", (*rdfpre).getString(), 14))||(!strncmp("swrc:pages", (*rdfpre).getString(), 10)))
        {
            (*a).removeRelated(j);
        }
    }
    ret.add(a);
    set<Author*> uniqueco;
    for(int i = 0;i<coauthor_front_pool.count();i++){
        Author *co = static_cast<Author*>(coauthor_front_pool.getAt(i));
        uniqueco.insert(co);
    }
    int numa = 0;
    for (std::set<Author*>::iterator it = uniqueco.begin(); it != uniqueco.end(); ++it) {
        Author* tempa = *it;
        if(numa>cnt/8){
            break;
        }
        // RDFTriple *coaup = coauthor_pool.getAt(numa);
        PropertyAuthor *create = new PropertyAuthor(a,tempa);
        ret.add(create);
        // (*create).addRelated(coaup);
        numa++;
    }
    int ttt = 0;
    while(uniqueco.size()+ttt<cnt/8){
        Author *aaa = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*aaa).getRelated();
        int size = (*relatedvecRDF).size();
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*aaa).removeRelated(i);
            }
        }
        ret.add(aaa);
        Author *bbb = new Author(year);
        vector <RDFTriple *> * brelatedvecRDF = (*bbb).getRelated();
        int bsize = (*brelatedvecRDF).size();
        for(int i = 0;i<bsize;i++){
            RDFTriple * relatedRDF = (*brelatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*bbb).removeRelated(i);
            }
        }
        ret.add(bbb);
        PropertyAuthor *create = new PropertyAuthor(a,aaa);
        PropertyCoauthor *coauther = new PropertyCoauthor(aaa,bbb);
        ret.add(create);
        ret.add(coauther);
        ttt++;
    }

    // dcterms:partOf / swrc:editor
    // swrc:editor / dcterms:affect
    // dcterms:affect / foaf:name
    Proceedings *pro = new Proceedings(pcnt+2,year);
    ret.add(pro);
    int temp = 0;
    while(temp < cnt/8){
        // Inproceedings * e = new Inproceedings(temp+1, year, 999);
        Inproceedings * e = new Inproceedings(temp+1, year, pcnt+2);
        PropertyCrossref *t = new PropertyCrossref(e, pro);
        ret.add(e);
        ret.add(t);
        (*articleInpro_pool).add(e);
        Author * authortemp = new Author(year);
        NamePoolMgr *npm = NamePoolMgr::getInstance();
        char *sstr = StringTools::concatStrs("_:",
                    npm->getNameById(NamePoolFile::givenNames,(*authortemp).getGivenName()),
                    "_",
                    npm->getNameById(NamePoolFile::familyNames,(*authortemp).getLastName()));
        PropertyEditor *edi = new PropertyEditor(pro,sstr);
        ret.add(edi);
        vector <RDFTriple *> * relatedvecRDF = (*authortemp).getRelated();
        int size = (*relatedvecRDF).size();
        for(int i = 0;i<size;i++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[i];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*authortemp).removeRelated(i);
            }
        }
        ret.add(authortemp);

        Author * authortemp2 = new Author(year);
        ret.add(authortemp2);
        PropertyAffect *affect = new PropertyAffect(authortemp,authortemp2);
        affect_pool.add(affect);
        affect_front_pool.add(authortemp);
        affect_back_pool.add(authortemp2);
        partof_editor_affect_front_pool.add(e);
        partof_editor_affect_back_pool.add(authortemp2);
        ret.add(affect);
        temp++;
    }

    // dcterms:coauthor/ dcterms:coauthor
    // int num_coco = cnt/8;
    // int coauthornum = coauthor_pool.count();
    for(int i = 0;i<cnt/8;i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Author *co = static_cast<Author*>(coauthor_back_pool.getAt(i));
        PropertyCoauthor * coa = new PropertyCoauthor(co,a);
        ret.add(a);
        ret.add(coa);
        coauthor_pool.add(coa);
        coauthor_back_pool.change(i,a);
    }

    return ret;
} //generatePathLengthTwo()

RDFTriplePool Generator::generatePathLengthThree(unsigned year,RDFTriplePool *a_pool,unsigned & total_pathLength_three)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 20;
    // adapt count
    total_pathLength_three+=cnt/6*6;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:partOf / swrc:editor / dcterms:affect
    //之前加的包含这句，且数量足够

    //dcterms:references/ dcterms:cite/ dc:creator
    //用这个ref_cite_back_pool.push_back(uri);写 这里装了dcterms:cite的宾语uri数量足够
    for(int i = 0 ;i<min(static_cast<int>(ref_cite_back_pool.size()),static_cast<int>(cnt/6)) ; i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Article_Inpro *noexist_a = new Article_Inpro(ref_cite_back_pool[i]);
        // cout << (*noexist_a).print() << endl;
        PropertyAuthor *ref_cite_cre = new PropertyAuthor(noexist_a,a);
        // cout << "aaaa   " <<(*ref_cite_cre).print() << endl;
        ret.add(a);
        // ret.add(noexist_a);
        ret.add(ref_cite_cre);
    }

    //dc:creator/dcterms:coauthor / dcterms:coauthor
    //前文加的足够
    Article * arc = static_cast<Article*>(static_cast<Document*>((*a_pool).getAt(acnt-1)));
    unsigned numofj = (*arc).getjnum();
    Journal *j = new Journal(numofj+3,year);
    ret.add(j);
    for(int i =0;i<cnt/6;i++){
        //得到文章A
        Article * a = new Article(i+1,year,numofj+3);
        RDFTriple * rdf = a;
        vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("bench:abstract", (*rdfpre).getString(), 14))||(!strncmp("swrc:pages", (*rdfpre).getString(), 10)))
            {
                (*a).removeRelated(j);
            }
        }
        //将文章A与coauthor/coauthor连起来
        RDFTriple *tempauthor = coauthor_front_pool.getAt(i);
        PropertyAuthor *creator_co_co = new PropertyAuthor(a,tempauthor);
        ret.add(a);
        ret.add(creator_co_co);
    }

    //dcterms:coauthor/ dcterms:coauthor/ foaf:name
    int numofname = 0;
    set<RDFTriple*> unique;
    for(int i = 0;i<coauthor_back_pool.count();i++){
        RDFTriple *co = coauthor_back_pool.getAt(i);
        unique.insert(co);
    }
    // RDFTriple * rdf = coauthor_back_pool.getAt(i);
    for(set<RDFTriple*>::iterator it = unique.begin(); it != unique.end(); ++it){
        RDFTriple* rdf = *it; 
        vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
        int size = (*relatedvecRDF).size();
        int tempp = 0;
        int tempa = 0;
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                numofname++;
            }
            if(numofname >= cnt/6){
                break;
            }
        }
        if(numofname >= cnt/6){
            break;
        }
    }
    //如果原有不够再补充
    if(cnt/6-numofname>0){
        for(set<RDFTriple*>::iterator it = unique.begin(); it != unique.end(); ++it){
            RDFTriple* rdf = *it; 
            vector <RDFTriple *> * relatedvecRDF = (*rdf).getRelated();
            int size = (*relatedvecRDF).size();
            if(size == 0){
                Author *a = static_cast<Author *> (rdf);
                PropertyAuthorName *authorname = new PropertyAuthorName(a,(*a).getGivenName(),(*a).getLastName());
                ret.add(authorname);               
            }
            for(int j = 0;j<size;j++){
                RDFTriple * relatedRDF = (*relatedvecRDF)[j];
                RDFObject * rdfpre = (*relatedRDF).getPrePtr();
                if ((strncmp("foaf:name", (*rdfpre).getString(), 9)))
                {
                    Author *a = static_cast<Author *> (rdf);
                    PropertyAuthorName *authorname = new PropertyAuthorName(a,(*a).getGivenName(),(*a).getLastName());
                    ret.add(authorname);
                    numofname++;
                }
            }
        }
    }

    //dcterms:coauthor/ dcterms:affect / foaf:name
    for(int i = 0;i<cnt/6;i++){
        RDFTriple *before_affect_author = affect_front_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        PropertyCoauthor *co_af = new PropertyCoauthor(a,before_affect_author);
        coauthor_affect_front_pool.add(a);
        ret.add(co_af);
    }
    
    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor
    for(int i = 0;i<cnt/6;i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Author *co = static_cast<Author*>(coauthor_back_pool.getAt(i));
        PropertyCoauthor * coa = new PropertyCoauthor(co,a);
        ret.add(a);
        ret.add(coa);
        coauthor_pool.add(coa);
        coauthor_back_pool.change(i,a);
    }

    
    return ret;
} //generatePathLengthThree()

RDFTriplePool Generator::generatePathLengthFour(unsigned year,RDFTriplePool *a_pool,unsigned & total_pathLength_four)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 11;
    // adapt count
    total_pathLength_four+=cnt/7*7;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:partOf/ swrc:editor/ dcterms:affect/ foaf:name
    //之前加的包含这句，且数量足够

    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite
    for (int i = 0; i < uriuris_1.size(); i++) {
        char* originalStr = uriuris_1[i];
        // 为新字符串分配足够的内存
        char* newStr = new char[strlen(originalStr) + 1];
        strcpy(newStr, originalStr); // 复制原字符串到新字符串

        // 在新字符串上进行修改
        for (int j = 0; newStr[j] != '\0'; ++j) {
            if (newStr[j] == '1' && newStr[j+1] == '9' && isdigit(newStr[j+2]) && isdigit(newStr[j+3])) {
                char yearSubstr[5] = {newStr[j], newStr[j+1], newStr[j+2], newStr[j+3], '\0'};
                int year = atoi(yearSubstr);
                if (year >= 1900 && year <= 1999) {
                    year--; // 年份减1
                    snprintf(yearSubstr, sizeof(yearSubstr), "%d", year);
                    newStr[j+2] = yearSubstr[2];
                    newStr[j+3] = yearSubstr[3];
                    // 修改完成，跳过剩余部分
                    break;
                }
            }
        }
        uriuris_2.push_back(newStr); // 将修改后的新字符串添加到uris列表中
    }
    for(int i = 0;i<cnt/7;i++){
        char* ref_cite_back = ref_cite_back_pool[i];
        ReferenceBag *ref_bag = new ReferenceBag();
        ReferenceBagReference *c = new ReferenceBagReference(
                    ref_cite_back,
                    ref_bag->getSubjectPtr()->getString());
        ret.add(c);
        // ref_cite_front_pool.push_back((*articleInpro_pool).getAt(0)->getSubjectPtr()->getString());
        unsigned cnum = 1;
        int cite_cnt_num = 3;
        while(cite_cnt_num)
        {
            PropertyCite *ci;
            
            char * uri = 0L;
            if(uriuris_2.size() > 0)
            {
                uri = uriuris_2[uriuris_2.size() -1];
                uriuris_2.pop_back();
            }

            if(uri)
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(), cnum, uri);
                ref_cite_back_pool[i] = uri;
                // delete[] uri;
            }
            else
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(),
                    cnum, "<http://localhost/misc/UnknownDocument>");
            }
            
            ret.add(ci);
            cite_cnt_num--;
            cnum++;
        } //while
    }

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ foaf:name
    for(int i = 0;i<cnt/7;i++){
        Author *a = static_cast<Author*>(coauthor_back_pool.getAt(i));
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        if(size == 0){
            PropertyAuthorName *author_name = new PropertyAuthorName(a,(*a).getGivenName(),(*a).getLastName());
            ret.add(author_name);      
        }
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                PropertyAuthorName *author_name = new PropertyAuthorName(a,(*a).getGivenName(),(*a).getLastName());
                ret.add(author_name);
            }
        }
    }

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:affect / foaf:name
    for(int i = 0;i<cnt/7;i++){
        // RDFTriple *before_affect_author = affect_front_pool.getAt(i);
        RDFTriple *before_coauthor_affect_author = coauthor_affect_front_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        PropertyCoauthor *co_af = new PropertyCoauthor(a,before_coauthor_affect_author);
        // coauthor_affect_front_pool.add(a);
        coauthor_affect_front_pool.change(i,a);
        ret.add(co_af);
    }

    //dcterms:partOf / swrc:editor / dcterms:affect/ dcterms:affect
    for(int i =0;i<cnt/7;i++){
        RDFTriple *p_e_a_back = partof_editor_affect_back_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        PropertyAffect *affect = new PropertyAffect(p_e_a_back,a);
        ret.add(affect);
        partof_editor_affect_back_pool.change(i,a);
    }

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor
    //不用去掉name 相当于加了路径长度为5的
    for(int i = 0;i<cnt/7;i++){
        Author * a = new Author(year);
        RDFTriple *co = coauthor_back_pool.getAt(i);
        PropertyCoauthor * coa = new PropertyCoauthor(co,a);
        ret.add(a);
        ret.add(coa);
        coauthor_pool.add(coa);
        coauthor_back_pool.change(i,a);
    }
    
    return ret;
} //generatePathLengthFour()

RDFTriplePool Generator::generatePathLengthFive(unsigned year,unsigned & total_pathLength_five)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 7;
    // adapt count
    total_pathLength_five+=cnt/7*7;
    
    // unsigned long int mml= cmd->getSizeValue();
   
    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year %static_cast<unsigned long int>(DIVISOR) == 0)){
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!mml       "<<endl;       
        return ret;
    }
        
    
    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ foaf:name
    //之前加的包含这句，且数量足够

    //dc:creator/ dcterms: coauthor / dcterms: coauthor / dcterms: coauthor / dcterms: coauthor
    //之前加的包含这句，且数量足够

    //dcterms:record / dcterms:partOf/ swrc:editor/ dcterms:affect/ foaf:name
    for(int i = 0;i<cnt/7;i++){
        Institution * ins = new Institution(i+6,year);
        ret.add(ins);
        RDFObject *o1 = (*partof_editor_affect_front_pool.getAt(i)).getSubjectPtr();
        RDFObject *oooo = new RDFObject(RDFObject::URIObj,o1->getString());
        PropertyRecord *prorec = new PropertyRecord(ins,oooo);
        ret.add(prorec);
    }

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:affect / foaf:name
    for(int i = 0;i<cnt/7;i++){
        // RDFTriple *before_affect_author = affect_front_pool.getAt(i);
        RDFTriple *before_coauthor_affect_author = coauthor_affect_front_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        RDFTriple *aaa = before_coauthor_affect_author;
        PropertyCoauthor *co_af = new PropertyCoauthor(a,aaa);
        // coauthor_affect_front_pool.add(a);
        coauthor_affect_front_pool.change(i,a);
        ret.add(co_af);
    }

    //dcterms:partOf / swrc:editor / dcterms:affect/ dcterms:affect/ dcterms:affect
    for(int i =0;i<cnt/7;i++){
        RDFTriple *p_e_a_back = partof_editor_affect_back_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        RDFTriple *temp = p_e_a_back;
        PropertyAffect *affect = new PropertyAffect(temp,a);
        ret.add(affect);
        partof_editor_affect_back_pool.change(i,a);
    }

    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dc:creator
    for(int i = 0 ;i<min(static_cast<int>(ref_cite_back_pool.size()),static_cast<int>(cnt/7)) ; i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Article_Inpro *noexist_a = new Article_Inpro(ref_cite_back_pool[i]);
        PropertyAuthor *ref_cite_cre = new PropertyAuthor(noexist_a,a);
        ret.add(a);
        ret.add(ref_cite_cre);
    }

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor
    //不用去掉name 相当于加了路径长度为5的
    for(int i = 0;i<cnt/7;i++){
        Author * a = new Author(year);
        RDFTriple *co = coauthor_back_pool.getAt(i);
        PropertyCoauthor * coa = new PropertyCoauthor(co,a);
        ret.add(a);
        ret.add(coa);
        coauthor_pool.add(coa);
        coauthor_back_pool.change(i,a);
    }
    
    return ret;
} //generatePathLengthFive()

RDFTriplePool Generator::generatePathLengthSix(unsigned year,unsigned & total_pathLength_six)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 5;
    // adapt count
    total_pathLength_six+=cnt/5*5;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ foaf:name
    //之前加的包含这句，且数量足够

    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:affect / foaf:name
    //之前加的包含这句，且数量足够

    //dc:creator/ dcterms: coauthor / dcterms: coauthor / dcterms: coauthor / dcterms: coauthor / dcterms:coauthor
    //之前加的包含这句，且数量足够

    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite
    for (int i = 0; i < uriuris_2.size(); i++) {
        char* originalStr = uriuris_2[i];
        // 为新字符串分配足够的内存
        char* newStr = new char[strlen(originalStr) + 1];
        strcpy(newStr, originalStr); // 复制原字符串到新字符串

        // 在新字符串上进行修改
        for (int j = 0; newStr[j] != '\0'; ++j) {
            if (newStr[j] == '1' && newStr[j+1] == '9' && isdigit(newStr[j+2]) && isdigit(newStr[j+3])) {
                char yearSubstr[5] = {newStr[j], newStr[j+1], newStr[j+2], newStr[j+3], '\0'};
                int year = atoi(yearSubstr);
                if (year >= 1900 && year <= 1999) {
                    year--; // 年份减1
                    snprintf(yearSubstr, sizeof(yearSubstr), "%d", year);
                    newStr[j+2] = yearSubstr[2];
                    newStr[j+3] = yearSubstr[3];
                    // 修改完成，跳过剩余部分
                    break;
                }
            }
        }
        uriuris_3.push_back(newStr); // 将修改后的新字符串添加到uris列表中
    }
    for(int i = 0;i<cnt/5;i++){
        char* ref_cite_back = ref_cite_back_pool[i];
        ReferenceBag *ref_bag = new ReferenceBag();
        ReferenceBagReference *c = new ReferenceBagReference(
                    ref_cite_back,
                    ref_bag->getSubjectPtr()->getString());
        ret.add(c);
        // ref_cite_front_pool.push_back((*articleInpro_pool).getAt(0)->getSubjectPtr()->getString());
        unsigned cnum = 1;
        int cite_cnt_num = 3;
        while(cite_cnt_num)
        {
            PropertyCite *ci;
            
            char * uri = 0L;
            if(uriuris_3.size() > 0)
            {
                uri = uriuris_3[uriuris_3.size() -1];
                uriuris_3.pop_back();
            }

            if(uri)
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(), cnum, uri);
                ref_cite_back_pool[i] = uri;
                // delete[] uri;
            }
            else
            {
                ci = new PropertyCite(
                    ref_bag->getSubjectPtr()->getString(),
                    cnum, "<http://localhost/misc/UnknownDocument>");
            }
            
            ret.add(ci);
            cite_cnt_num--;
            cnum++;
        } //while
    }

    //dcterms:partOf / swrc:editor / dcterms:affect/ dcterms:affect/ dcterms:affect/dcterms:affect
    for(int i =0;i<cnt/5;i++){
        RDFTriple *p_e_a_back = partof_editor_affect_back_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        RDFTriple *temp = p_e_a_back;
        PropertyAffect *affect = new PropertyAffect(temp,a);
        ret.add(affect);
        partof_editor_affect_back_pool.change(i,a);
    }
    
    return ret;
} //generatePathLengthSix()

RDFTriplePool Generator::generatePathLengthSeven(unsigned year,unsigned & total_pathLength_seven)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 4;
    // adapt count
    total_pathLength_seven+=cnt/3*3;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))

        return ret;
    
    //dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:coauthor/ dcterms:affect / foaf:name
    //之前加的包含这句，且数量足够

    //dcterms:partOf / swrc:editor / dcterms:affect / dcterms:affect / dcterms:affect / dcterms:affect / dcterms:affect
    for(int i =0;i<cnt/3;i++){
        RDFTriple *p_e_a_back = partof_editor_affect_back_pool.getAt(i);
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        ret.add(a);
        RDFTriple *temp = p_e_a_back;
        PropertyAffect *affect = new PropertyAffect(temp,a);
        ret.add(affect);
        partof_editor_affect_back_pool.change(i,a);
    }

    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite / dcterms:references/ dcterms:cite/ dc:creator
    for(int i = 0 ;i<min(static_cast<int>(ref_cite_back_pool.size()),static_cast<int>(cnt/3)) ; i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Article_Inpro *noexist_a = new Article_Inpro(ref_cite_back_pool[i]);
        PropertyAuthor *ref_cite_cre = new PropertyAuthor(noexist_a,a);
        ret.add(a);
        ret.add(ref_cite_cre);
    }
    
    return ret;
} //generatePathLengthSeven()

RDFTriplePool Generator::generatePathLengthEight(unsigned year,unsigned & total_pathLength_eight)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 3;
    // adapt count
    total_pathLength_eight+=cnt;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite
    for (int i = 0; i < uriuris_3.size(); i++) {
        char* originalStr = uriuris_3[i];
        // 为新字符串分配足够的内存
        char* newStr = new char[strlen(originalStr) + 1];
        strcpy(newStr, originalStr); // 复制原字符串到新字符串

        // 在新字符串上进行修改
        for (int j = 0; newStr[j] != '\0'; ++j) {
            if (newStr[j] == '1' && newStr[j+1] == '9' && isdigit(newStr[j+2]) && isdigit(newStr[j+3])) {
                char yearSubstr[5] = {newStr[j], newStr[j+1], newStr[j+2], newStr[j+3], '\0'};
                int year = atoi(yearSubstr);
                if (year >= 1900 && year <= 1999) {
                    year--; // 年份减1
                    snprintf(yearSubstr, sizeof(yearSubstr), "%d", year);
                    newStr[j+2] = yearSubstr[2];
                    newStr[j+3] = yearSubstr[3];
                    // 修改完成，跳过剩余部分
                    break;
                }
            }
        }
        uriuris_4.push_back(newStr); // 将修改后的新字符串添加到uris列表中
    }
    char* ref_cite_back = ref_cite_back_pool[0];
    ReferenceBag *ref_bag = new ReferenceBag();
    ReferenceBagReference *c = new ReferenceBagReference(
                ref_cite_back,
                ref_bag->getSubjectPtr()->getString());
    ret.add(c);
    // ref_cite_front_pool.push_back((*articleInpro_pool).getAt(0)->getSubjectPtr()->getString());
    unsigned cnum = 1;
    int cite_cnt_num = cnt;
    while(cite_cnt_num)
    {
        PropertyCite *ci;
        
        char * uri = 0L;
        if(uriuris_4.size() > 0)
        {
            uri = uriuris_4[uriuris_4.size() -1];
            uriuris_4.pop_back();
        }

        if(uri)
        {
            ci = new PropertyCite(
                ref_bag->getSubjectPtr()->getString(), cnum, uri);
            ref_cite_back_pool[0] = uri;
            // delete[] uri;
        }
        else
        {
            ci = new PropertyCite(
                ref_bag->getSubjectPtr()->getString(),
                cnum, "<http://localhost/misc/UnknownDocument>");
        }
        
        ret.add(ci);
        cite_cnt_num--;
        cnum++;
    } //while

    
    return ret;
} //generatePathLengthEight()

RDFTriplePool Generator::generatePathLengthNine(unsigned year,unsigned & total_pathLength_nine)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 2;
    // adapt count
    total_pathLength_nine+=cnt;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:references/dcterms:cite/dcterms:references/dcterms:cite/dcterms:references/ dcterms:cite / dcterms:references/ dcterms:cite/ dc:creator
    for(int i = 0 ;i<min(static_cast<int>(ref_cite_back_pool.size()),static_cast<int>(cnt)) ; i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Article_Inpro *noexist_a = new Article_Inpro(ref_cite_back_pool[0]);
        PropertyAuthor *ref_cite_cre = new PropertyAuthor(noexist_a,a);
        ret.add(a);
        ret.add(ref_cite_cre);
    }
    
    return ret;
} //generatePathLengthNine()

RDFTriplePool Generator::generatePathLengthTen(unsigned year,unsigned & total_pathLength_ten)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 2;
    // adapt count
    total_pathLength_ten+=cnt;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite/ dcterms:references/ dcterms:cite
    for (int i = 0; i < uriuris_4.size(); i++) {
        char* originalStr = uriuris_4[i];
        // 为新字符串分配足够的内存
        char* newStr = new char[strlen(originalStr) + 1];
        strcpy(newStr, originalStr); // 复制原字符串到新字符串

        // 在新字符串上进行修改
        for (int j = 0; newStr[j] != '\0'; ++j) {
            if (newStr[j] == '1' && newStr[j+1] == '9' && isdigit(newStr[j+2]) && isdigit(newStr[j+3])) {
                char yearSubstr[5] = {newStr[j], newStr[j+1], newStr[j+2], newStr[j+3], '\0'};
                int year = atoi(yearSubstr);
                if (year >= 1900 && year <= 1999) {
                    year--; // 年份减1
                    snprintf(yearSubstr, sizeof(yearSubstr), "%d", year);
                    newStr[j+2] = yearSubstr[2];
                    newStr[j+3] = yearSubstr[3];
                    // 修改完成，跳过剩余部分
                    break;
                }
            }
        }
        uriuris_5.push_back(newStr); // 将修改后的新字符串添加到uris列表中
    }
    char* ref_cite_back = ref_cite_back_pool[0];
    ReferenceBag *ref_bag = new ReferenceBag();
    ReferenceBagReference *c = new ReferenceBagReference(
                ref_cite_back,
                ref_bag->getSubjectPtr()->getString());
    ret.add(c);
    // ref_cite_front_pool.push_back((*articleInpro_pool).getAt(0)->getSubjectPtr()->getString());
    unsigned cnum = 1;
    int cite_cnt_num = cnt;
    while(cite_cnt_num)
    {
        PropertyCite *ci;
        
        char * uri = 0L;
        if(uriuris_5.size() > 0)
        {
            uri = uriuris_5[uriuris_5.size() -1];
            uriuris_5.pop_back();
        }

        if(uri)
        {
            ci = new PropertyCite(
                ref_bag->getSubjectPtr()->getString(), cnum, uri);
            ref_cite_back_pool[0] = uri;
            // delete[] uri;
        }
        else
        {
            ci = new PropertyCite(
                ref_bag->getSubjectPtr()->getString(),
                cnum, "<http://localhost/misc/UnknownDocument>");
        }
        
        ret.add(ci);
        cite_cnt_num--;
        cnum++;
    } //while    

    
    return ret;
} //generatePathLengthTen()

RDFTriplePool Generator::generatePathLengthEleven(unsigned year,unsigned & total_pathLength_eleven)
{
    
    RDFTriplePool ret;
    unsigned acnt = Functions::article(year);
    unsigned pcnt = Functions::proc(year);
    unsigned books = Functions::book(year);
    unsigned incolls = Functions::incoll(year);
    unsigned phds = Functions::phd(year);
    unsigned masters = Functions::master(year);
    unsigned wwws = Functions::www(year);
    unsigned allauthor = Functions::nrTotalAuthors(year);
    unsigned cnt = 1;
    // adapt count
    total_pathLength_eleven+=cnt;

    //document类至少有一个存在，同时是闰年（防止自加数据过多，一个查询返回一半图）才会开始生成路径长度为1的数据
    if(!(acnt|pcnt|books|incolls|phds|masters|wwws) || !(year % static_cast<unsigned long int>(DIVISOR) == 0))
        return ret;
    
    //dcterms:references/dcterms:cite/dcterms:references/dcterms:cite/dcterms:references/dcterms:cite/dcterms:references/ dcterms:cite / dcterms:references/ dcterms:cite/ dc:creator
    for(int i = 0 ;i<min(static_cast<int>(ref_cite_back_pool.size()),static_cast<int>(cnt)) ; i++){
        Author * a = new Author(year);
        vector <RDFTriple *> * relatedvecRDF = (*a).getRelated();
        int size = (*relatedvecRDF).size();
        for(int j = 0;j<size;j++){
            RDFTriple * relatedRDF = (*relatedvecRDF)[j];
            RDFObject * rdfpre = (*relatedRDF).getPrePtr();
            if ((!strncmp("foaf:name", (*rdfpre).getString(), 9)))
            {
                (*a).removeRelated(j);
            }
        }
        Article_Inpro *noexist_a = new Article_Inpro(ref_cite_back_pool[0]);
        PropertyAuthor *ref_cite_cre = new PropertyAuthor(noexist_a,a);
        ret.add(a);
        ret.add(ref_cite_cre);
    }
    
    return ret;
} //generatePathLengthEleven()



/*!
    \fn Generator::generateJournals(unsigned)
    generates all journal objects for specified year, including the basic attributes
    (added as related triples)
    @return pool with generated triple objects
 */
RDFTriplePool Generator::generateJournals(unsigned year,unsigned & total_nr_journals)
{
RDFTriplePool ret;
unsigned cnt = Functions::journal(year);

    // adapt count
    total_nr_journals+=cnt;

    for(unsigned i = 0; i < cnt; i++)
    {
    Journal * e = new Journal(i+1, year);
        ret.add(e);
    }
    
    return ret;
} //generateJournals()

/*!
    \fn Generator::generateInProceedings(unsigned)
    generates all objects of InProceedings publications
    for specified year, including the basic attributes
    (added as related triples)
    @param year current year
    @param c_pool pointer to pool with available conferences
    @return pool with generated triple objects
 */
RDFTriplePool Generator::generateInProceedings(unsigned year, RDFTriplePool *c_pool,
                                                unsigned & total_nr_inproceedings)
{
RDFTriplePool ret;


    if(! c_pool->count())
        return ret; //can have no inproceedings without proceedings

    unsigned cnt = Functions::inproc(year);
    total_nr_inproceedings+=cnt;

    vector <unsigned> conference_sizes; //expectation values for conference sizes
    GaussianDistribution g(1, cnt/c_pool->count(), .2 * cnt/c_pool->count());

    //initializing expectation values for conference sizes...
    for(unsigned i = 0; i < c_pool->count(); i++)
    {
        conference_sizes.push_back(g.getRandomnizedValue());
    } //for

    unsigned proceeding_num = 0;
    
    for(unsigned i = 0; i < cnt; i++)
    {
        //distributing papers over conferences (exp. sizes); if sum of exp. vals is a bit
        //too small, just rotate equally from beginning for remaining talks...
        if(conference_sizes[proceeding_num])
            conference_sizes[proceeding_num]--;
        else
            proceeding_num++;
            
        if(proceeding_num >= c_pool->count())
            proceeding_num = 0; 
        
        Inproceedings * e = new Inproceedings(i+1, year, proceeding_num+1);
    
        //as it happens, this numeric id part is equal to pos of conference in pool
        c_pool->getAt(proceeding_num)->addRelated(e,false);
        
        if(e->requireCrossRef())
        {
            RDFTriple *t = new PropertyCrossref(e, c_pool->getAt(proceeding_num));
            e->addRelated(t, true);
        }
        
        ret.add(e);
    } //for
    
    return ret;

} //generateInProceedings()


/*!
    \fn Generator::generateArticles(unsigned)
    generates all objects of article publications
    for specified year, including the basic attributes
    (added as related triples)
    @param year current year
    @param j_pool pointer to pool with available journals
    @return pool with generated triple objects
 */
RDFTriplePool Generator::generateArticles(unsigned year, RDFTriplePool *j_pool,
                                            unsigned & total_nr_articles)
{
RDFTriplePool ret;
unsigned cnt = Functions::article(year);

    // adapt counts
    total_nr_articles+=cnt;

    if(! cnt)
        return ret; //to avoid non-necessary (but dangerous) calculations

    if(! j_pool->count() && cnt > 0)
    {
        /* that one is a bit complicated; articles without journals exist, but they're rare,
            so we don't expect the case of having articles but no journals in a year.
            to avoid any misdistribution in output, abort in case it should happen, though ;-) */
        cout << "state with invalid constellation of journals/articles reached" << endl;
        exit(8);
    }

    vector <unsigned> journal_sizes; //expectation values for conference sizes

    GaussianDistribution g(1, cnt/j_pool->count(), .2 * cnt/j_pool->count());

    //initializing expectation values for journal sizes...
    for(unsigned i = 0; i < j_pool->count(); i++)
    {
        journal_sizes.push_back(g.getRandomnizedValue());
    } //for

    unsigned journal_num = 0;

    for(unsigned i = 0; i < cnt; i++)
    {
        //distributing papers over journal (exp. sizes); if sum of exp. vals is a bit
        //too small, just rotate equally from beginning for remaining talks...
        if(journal_sizes[journal_num])
            journal_sizes[journal_num]--;
        else
            journal_num++;
            
        if(journal_num >= j_pool->count())
            journal_num = 0; 
        
        Article * e = new Article(i+1, year, journal_num+1);
    
        /*as it happens, this numeric id part is equal to pos of journal in pool + 1
          however it is important to associate only those articles that really have a
          journal attribute */
        if(e->requireJournal())
        {
            j_pool->getAt(journal_num)->addRelated(e,false);
            
            RDFTriple *t = new PropertyJournal(e, j_pool->getAt(journal_num));
            e->addRelated(t, true);
        }
        
        ret.add(e);
        
    } //for

    
    return ret;
} //generateArticles()


/*!
    \fn Generator::generateOthers(unsigned)
    generates all objects of publications except InProceedings or articles
    for specified year, including the basic attributes
    (added as related triples)
    @return pool with generated triple objects
 */
RDFTriplePool Generator::generateOthers(unsigned year, unsigned &total_nr_incollections,
                                        unsigned &total_nr_books,unsigned &total_nr_wwws,
                                        unsigned &total_nr_masterstheses,
                                        unsigned &total_nr_phdtheses)
{
RDFTriplePool ret;
unsigned books = Functions::book(year);
unsigned incolls = Functions::incoll(year);
unsigned phds = Functions::phd(year);
unsigned masters = Functions::master(year);
unsigned wwws = Functions::www(year);

    // adapt counts
    total_nr_incollections+=incolls;
    total_nr_books+=books;
    total_nr_wwws+=wwws;
    total_nr_masterstheses+=masters;
    total_nr_phdtheses+=phds;
    
    for(unsigned i = 0; i < books; i++)
    {
    Book * e = new Book(i+1, year);
        ret.add(e);
    }

    
    for(unsigned i = 0; i < incolls; i++)
    {
    Incollection * e = new Incollection(i+1, year);
        ret.add(e);
    }

    
    for(unsigned i = 0; i < phds; i++)
    {
    Phdthesis * e = new Phdthesis(i+1, year);
        ret.add(e);
    }
    
    
    for(unsigned i = 0; i < masters; i++)
    {
    Mastersthesis * e = new Mastersthesis(i+1, year);
        ret.add(e);
    }
    
    
    for(unsigned i = 0; i < wwws; i++)
    {
    Www * e = new Www(i+1, year);
        ret.add(e);
    }
    
    return ret;
} //generateOthers()


/*!
    \fn Generator::store(vector <char *>)

    Stores all the lines in triple_lines on the disk (appending to output file)
 */
unsigned Generator::store(vector <char *> triple_lines)
{
    FILE *f = fopen64(cmd->getOutFileName(), "a+");
    
    if(f == 0L)
    {
        cout << "fatal error: failed to access output file '"
				<< cmd->getOutFileName() << "' for writing" << endl;
        exit(2);
    }

    unsigned nr_triples=0;
    for(unsigned i = 0; i < triple_lines.size(); i++)
        if(strlen(triple_lines[i])) //ignore empty/void triples
        {
            fputs(triple_lines[i], f);
            fputs("\n\0", f);
            nr_triples++;
        }

    fclose(f);
    return nr_triples;
}
