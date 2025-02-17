//
// C++ Implementation: CmdLine 
//
// Author: Michael Schmidt, Christoph Pinkel <>, (C) 2007-2008
// Copyright: See COPYING file that comes with this distribution
//
#include "cmdline.h"

/*!
    \fn CmdLine::CmdLine()
 */
CmdLine::CmdLine()
    : size_type(0), size_value(0) {

    size_type = SIZE_TYPE_DEFAULT;
    size_value = SIZE_VALUE_DEFAULT;
    out_file = OUT_FILE_DEFAULT;
}

CmdLine::~CmdLine() {}


/*!
    \fn CmdLine::parse(int argc, char ** args)
 */
bool CmdLine::parse(int argc, char ** args)
{
    unsigned long int numeric_arg = 0;
    unsigned long int size_nrtriples = 0;
    unsigned long int size_kbytes = 0;

    //parsing...
    if(argc > 1)
    {
        if (argc==2) { // only name provided
            if (args[1][0] == '-') {
                return false; // print help text
            } else {
                out_file=args[1];
            }
        } else if (argc==3 || argc==4) {

            if(args[1][0] == '-'
                   && (args[1][1] == 't' || args[1][1] == 's'))
            {
                //valid option if followed by positive number
                for(int i = 0; args[2][i] != 0L; i++)
                {
                    if(args[2][i] < 48 || args[2][i] > 58)
                        return false; //not a digit

                    numeric_arg *= 10;
                    numeric_arg += args[2][i] - 48; //adding digit
                } //for
    
                switch(args[1][1])
                {
                    case 't':
                        size_nrtriples = numeric_arg;
                        break;
                    
                    case 's':
                        size_kbytes = numeric_arg;
                        break;
                    
                    default: //will never happen
                        break;
                }
            }
            else //invalid option
                return false;

            if (argc==4) {
                if (args[3][0] == '-') {
                    return false; // print help text
                } else {
                    out_file=args[3];
                }
            }
        } //if
    }

    //setting up environment:
    if(size_nrtriples > 0)
    {
        size_type = SIZE_TYPE_TRIPLES;
        size_value = size_nrtriples;
        return true;
    }
    else if (size_kbytes > 0)
    {
        size_type = SIZE_TYPE_KBYTES;
        size_value = size_kbytes;
        return true;
    }
    else //using defaults as set in constructor, still valid
        return true;

}
