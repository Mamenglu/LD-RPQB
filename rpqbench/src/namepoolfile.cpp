//
// C++ Implementation: NamePoolFile 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "namepoolfile.h"

NamePoolFile* NamePoolFile::instance0 = 0L;
NamePoolFile* NamePoolFile::instance1 = 0L;
NamePoolFile* NamePoolFile::instance2 = 0L;

NamePoolFile::NamePoolFile(nfTypes file)
{
const char *fn = 0L;

    switch(file)
    {
        case givenNames:
            fn = "givennames.txt";
            break;
            
        case familyNames:
            fn = "familynames.txt";
            break;
            
        case titleWords:
            fn = "titlewords.txt";
            break;

        default:
            cout << "name file type error." << endl;
            exit(5);
            break;
    }
    
    FILE *f = fopen(fn, "r");
    
    if(f == 0L)
    {
        cout << "fatal error: failed to access required names file "
            << fn << " for reading." << endl;
        exit(6);
    }
    
    //reading file
    char c;
    char lne_buf[128];
    unsigned lne_pos = 0;
    char *lne;

    do
    {
        c = fgetc (f);
        
        if (c == 10)
        {
        //eol - adding line (name)...
            lne = new char[lne_pos + 1];
            strncpy(lne, lne_buf, lne_pos);
            lne[lne_pos] = 0; //terminator

            //adding line to vector
            names.push_back(lne);

            //initializing for next word
            lne_pos = 0;
        }
        else if(lne_pos < 128) //cutting words with length >= 128 bytes
        { //storing c in buffer...

            lne_buf[lne_pos] = c;
            lne_pos++;
        }
        
    } while (c != EOF);
    
    fclose(f);
    
    //need at least 10 words in each file:
    if(names.size() < 10)
    {
        cout << "fatal error: names file "
            << fn << " contains less than 10 words." << endl;
        exit(7);
    }

} //constructor

NamePoolFile::~NamePoolFile()
{
    for(unsigned i = 0; i < names.size(); i++)
        delete[] names[i];
}

/**
 * Retrieves some instance of singleton ("tripleton") class
 * @param file id of instance to retrieve
 * @return singleton ("tripleton") instance
 */
NamePoolFile * NamePoolFile::getInstance(nfTypes file)
{
    switch(file)
    {
        case givenNames:
            if(instance0 == 0L)
            {
                instance0 = new NamePoolFile(file);
            }
            return instance0;
            break;
            
        case familyNames:
            if(instance1 == 0L)
            {
                instance1 = new NamePoolFile(file);
            }
            return instance1;
            break;
            
        case titleWords:
            if(instance2 == 0L)
            {
                instance2 = new NamePoolFile(file);
            }
            return instance2;
            break;

        default:
            cout << "name file type error." << endl;
            exit(5);
            break;
    }
}

/**
 * fetches line from file
 * @param line_num 
 * @return pointer to specified line or 0L if line is out of range
 */
char * NamePoolFile::getLine(unsigned line_num)
{
    if(line_num >= names.size())
        return 0L;
        
    return names[line_num];
} //getLine()

