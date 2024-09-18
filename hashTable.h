/*  gerp    
 *  hashTable.h
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *
 *  Purpose: This is the class which the gerp search uses to store
    all the lines in the file and where each word is being used. The class
    represents the storage of the files. The vector begins with nothing in it.
    But adds the lines of the files when the code is run, adding buckets
    to hold where each word is used
 *           
 */

#include <functional>
#include <string>
#include <list>
#include <vector>
#include <cctype>
#include "bucket.h"
#include <iostream>  
#include <algorithm>


using namespace std;

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

class hashTable{
    
    public:
        //constructor
        hashTable();

        //vector access and modification
        void insert(string &name, int lineNum);
        string search(string name);
        string caseInsensitiveSearch(string name);
        void addLine(string &line);
      
    private:
        //vectors
        vector< vector< vector<Bucket> > > map;
        hash<string> hashedWord;
        vector< string > allLines;

        //hash fn
        int createHash(string &name);

        //private helpers
        void toLowerCase(string &name);
        string getAllLines(set<int> lines);

        //member variable
        int numBuckets;
};

#endif
