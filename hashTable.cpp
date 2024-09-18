/*  gerp    
 *  hashTable.cpp
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *
 *  Purpose: Defines the constructor and all functions for the hashTable
             class. The functions in this class handle the creation of
             new buckets and insertion of words into preexisting buckets.
             Other funcitons handle getting all of the lines where a word
             was used. 
 */

#include "hashTable.h"


/* default constructor
    Purpose: initializes the hash table
    Parameters: none
    Returns: nothing, sets the number of buckets in the map
*/
hashTable::hashTable() {
    //set number of buckets in the hash table
    map.resize(100000);
    numBuckets = 100000; 
}

/* addLine
    Purpose: adds the entire line to the allLines vector
    Parameters: a string of the line to be added
    Returns: nothing, adds line to vector
*/
void hashTable::addLine(string &line){
    allLines.push_back(line); //push line to vector containing all lines
}

/* insert
    Purpose: inserts word into bucket or creates bucket if there isn't 
             already one, also stores the spot where the whole line for the
             word is stored in the allLines vector
    Parameters: the word and the location the line is stored
    Returns: nothing, inserts or creates bucket for word
*/
void hashTable::insert(string &name, int lineNum) {
    string lowername = name; //set variable
    toLowerCase(lowername); //make the name all lowercase
    int hashIndex = createHash(lowername); //store the hashed index
    int mapColSize = map[hashIndex].size(); //store the size of map
    for (int i = 0; i < mapColSize; i++) {
        //if the name matches a bucket (insensitive)
        if (map[hashIndex][i][0].rightInsesitive(lowername)) {
            int sameNameSize = map[hashIndex][i].size(); //get size of bucket
            
            for (int j = 0; j < sameNameSize; j++) { //loop through bucket
                // if 
                if (map[hashIndex][i][j].rightBucket(name)) {
                    //if it is the bucket of the word being added
                    map[hashIndex][i][j].addLine(lineNum); 
                    //adds position of line in vector to bucket
                    return;
                } 
            }
            map[hashIndex][i].reserve(sameNameSize + 1); 
            map[hashIndex][i].emplace_back(name, lineNum); 
            //adds new bucket of word into vector of words with same letters
            return;
        }
    }
    map[hashIndex].reserve(mapColSize + 1);
    map[hashIndex].emplace_back();
    map[hashIndex].back().reserve(1);
    map[hashIndex][mapColSize].emplace_back(name, lineNum);
    //adds new word that has not been added yet into bucket 
    return;     
}

/* toLowerCase
    Purpose: changes the word to all lowercase letters
    Parameters: address of word to be changed to lowercase
    Returns: nothing, word is changed to lowercase
*/
void hashTable::toLowerCase(string &name) {
    int strSize = name.size(); //store size of string

    //loop through string
    for (int i = 0; i < strSize; i++) {
        name[i] = tolower(name[i]); //change char at index to lowercase
    }
}

/* search
    Purpose: searches for the bucket that matches the word for case sensitive
    Parameters: string of the word being searched for
    Returns: a string of all lines containing the word
*/
string hashTable::search(string name) {
    string lowername = name; //set variable
    toLowerCase(lowername); //make the name lowercase
    int hashIndex = createHash(lowername); //store index of hashed word

    int mapColSize = map[hashIndex].size(); //store size of map
    for (int i = 0; i < mapColSize; i++) {
        if (map[hashIndex][i][0].rightInsesitive(lowername)) { 
            // if all lowercase version is same (collisions)
            int sameNameSize = map[hashIndex][i].size();
            
            for (int j = 0; j < sameNameSize; j++) { //find version of word
                if (map[hashIndex][i][j].rightBucket(name)) { //calls get line
                    return getAllLines(map[hashIndex][i][j].returnSet());
                }
            }
            //if could not find name in lower case version
            name += " Not Found. Try with @insensitive or @i.\n";
            return name;
        }
    }
    //if could not find lower case version of word
    name += " Not Found. Try with @insensitive or @i.\n";
    return name;
}

/* getAllLines
    Purpose: gets the lines that include the word being searched
    Parameters: a set of ints what are the positions of the lines
        wanted to be outputed 
    Returns: a string of all the lines used
    Effect: takes all lines the word is used and puts them into a string
*/
string hashTable::getAllLines(set<int> lines) {
    //create iterator
    set<int>::iterator itr;
    string linesAdded = "";
    //iterate through entire set
    for (itr = lines.begin(); itr != lines.end(); itr++) {
        linesAdded += allLines[*itr] + "\n";//will have new line at end of file
    }
    return linesAdded; //return string of all lines
}

/* caseInsensitiveSearch
    Purpose: searches for the bucket that matches the word for case insensitive
    Parameters: string of the word being searched for
    Returns: a string of all lines containing the word
*/
string hashTable::caseInsensitiveSearch(string name) {
    string lowername = name;
    toLowerCase(lowername);
    int hashIndex = createHash(lowername);

    int mapColSize = map[hashIndex].size();
    set <int> bigSet;
    for (int i = 0; i < mapColSize; i++) {
        //finds lower case version of word
        if (map[hashIndex][i][0].rightInsesitive(lowername)) {
            int sameNameSize = map[hashIndex][i].size();
            //goes through all versions and adds the sets to bigSet
            for (int j = 0; j < sameNameSize; j++) {
                set <int> smallSet = map[hashIndex][i][j].returnSet();
                bigSet.insert(smallSet.begin(), smallSet.end());
            }
            return getAllLines(bigSet); //gets all lines
        }
    }
    //if could not find word
    name += " Not Found.\n";
    return name;
}

/* createHash
    Purpose: generates a random integer representing the words location in
             the hash table
    Parameters: the word to be hashed
    Returns: integer of the hashed index
*/
int hashTable::createHash(string &name) {
    return hashedWord(name) % numBuckets; //use hash fn
}
