/*  gerp    
 *  gerp.cpp
 *  Nate Perry (nperry02)
 *  4/17/23
 *  Gerp
 *
 *  Purpose: The program as a whole goes through the files given,
    and creates a seach function where the user can look for
    words case sensitive or insensitive and puts answers into a file
    or files
 *           
 *           
 *
 */


#include <iostream>
#include <fstream>
#include <string>

#include "Gerp.h"
#include "bucket.h"
#include "hashTable.h"

using namespace std;

/* main
    Purpose: makes Gerp run which by getting the directories and output files
    Parameters: takes the amount of arguments and a array of the arguments
        A file of directors, and the outfile
    Returns: 0
    Effect: creates gerp instance and runs gerp
*/
int main(int argc, char *argv[]) {
    if (argc != 3) { //if not the right amount of arguments
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }

    Gerp g;
    g.runGerp(argv[1], argv[2], cin); //runs gerp
    return 0;
}
