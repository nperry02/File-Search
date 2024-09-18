/*  gerp    
 *  bucket.cpp
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *
 *  Purpose: Defines the constructors, destrucor and all functions for 
             the bucket class. The functions are responsible for filling
             buckets, determining if a word matched a bucket, and for
             getting the locations for where the lines are stored in the 
             allLines vector. 
 */

#include "bucket.h"

/* default constructor
    Purpose: initializes empty bucket
    Parameters: none
    Returns: nothing, creates empty bucket
*/
Bucket::Bucket() {

}

/* parameter constructor
    Purpose: initializes filled bucket
    Parameters: the word for the bucket and an int for the spot in the vector 
                where the line is stored
    Returns: nothing, creates filled bucket
*/
Bucket::Bucket(string &name, int lineNum) { 
    first.word = name; //set bucket word to name
    //insert the spot in the vector where the line is stored
    first.lines.insert(lineNum); 
}

/* default destructor */
Bucket::~Bucket() {

}

/* insert
    Purpose: fills a bucket with a word and line number
    Parameters: the word for the bucket and an int for the spot in the vector 
                where the line is stored
    Returns: nothing, fills bucket
*/
void Bucket::insert(string &name, int lineNum) { 
    first.word = name; //set bucket word to name
    //insert the spot in the vector where the line is stored
    first.lines.insert(lineNum); 
}

/* addLine
    Purpose: adds another spot where the line is stored to the 
             set in the bucket
    Parameters: an int representing the spot in the vector where 
                the line is stored
    Returns: nothing, fills bucket
*/
void Bucket::addLine(int lineNum) {
    //insert the spot in the vector where the line is stored
    first.lines.insert(lineNum);
}

/* rightBucket
    Purpose: determines if the given word matches the right bucket for case
             sensitive search
    Parameters: the word to match to the bucket
    Returns: true if the word matches the bucket, false if not a match
*/
bool Bucket::rightBucket(string &name){
    //return true if the name matches the bucket (sensitive)
    if (name == first.word){
        return true;
    }
    //return false if not a match
    return false;
}

/* rightInsensitive
    Purpose: determines if the given word matches the right bucket for case
             insensitive search
    Parameters: the word to match to the bucket
    Returns: true if the word matches the bucket, false if not a match
*/
bool Bucket::rightInsesitive(string &name) {
    //return true if the name matches the bucket (insensitive)
    if (toLowerCase(first.word) == name) {
        return true;
    }
    //return false if not a match
    return false;
}

/* toLowerCase
    Purpose: changes the word to all lowercase letters
    Parameters: word to be changed to lowercase
    Returns: a string of the lowercase word
*/
string Bucket::toLowerCase(string name) {
    int strSize = name.size(); //store string size

    //loop through string
    for (int i = 0; i < strSize; i++) {
        name[i] = tolower(name[i]); //change char at index to lowercase
    }

    return name; //return lowercase string
}

/* returnSet
    Purpose: returns the set containing all of the locations where lines
             are stored
    Parameters: none
    Returns: returns the set stored in the bucket
*/
set<int> Bucket::returnSet() {
    return first.lines; //return set of lines
}
