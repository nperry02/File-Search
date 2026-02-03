/*  gerp    
 *  gerp.h
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *  Purpose: This is the class runs the gerp search and outputs
    every line of the searched words into a outfile. The class
    represents a search function that searches through the 
    diectorys and files given. The client gives inputs of
    what to search for in the given directory, either case 
    sensitive or not, and can also chnage where the everyhting
    should be outputed.
 *           
 */

#ifndef _GERP_H_
#define _GERP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "bucket.h"
#include "hashTable.h"
#include "DirNode.h"
#include "FSTree.h"
#include <vector>



using namespace std;


class Gerp{
    public:
        Gerp();
        void runGerp(string FN, string OF, istream &input);

    private:
        hashTable h;
        void FSTreeTraversal(DirNode *root, string dList, int &lineNum);
        void traversalHelper(DirNode *root, string dList, int i, int &lineNum);
        void runDir(string &dList, int &lineNum);
        void stripNonAlphaNum (std::string &input);
        void query(string OF, istream &input);
};

#endif
