/*  gerp    
 *  bucket.h
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *
 *  Purpose: This is the class that stores the words used in the files
        and where the lines are positioned in the vector of lines in
        hashTable. The buckets are created when gerp is ran, and are used
        when trying to find where each word is used in the files.
 *           
 */

#include <string>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

#ifndef _BUCKET_H_
#define _BUCKET_H_


class Bucket{
    
    public:
        //constructors
        Bucket();
        Bucket(string &name, int lineNum);
        
        //destructor
        ~Bucket();

        //bucket modification
        void addLine(int lineNum);
        void insert(string &name, int lineNum);

        //helper fns
        bool rightBucket(string &name);
        bool rightInsesitive(string &name);
        set<int> returnSet();
        
    private:

        //bucket struct
        struct Node {
            string word;
            set<int> lines;
        };

        //helper
        string toLowerCase(string name);

        //member variable
        Node first;

};

#endif
