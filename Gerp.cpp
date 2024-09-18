/*  gerp    
 *  gerp.cpp
 *  Nate Perry (nperry02)
 *  4/17/23
 *
 *
 *  Purpose: Defines the constructor and all functions for the gerp class.
             These functions facilitate the entire program, namely the 
             runGerp function which runs the program and the query function
             that handles user commands. Also includes functions to build
             the path and process the user given word.
 */

#include "Gerp.h"

/* default constructor
    Purpose: initializes empty gerp
    Parameters: none
    Returns: nothing, creates gerp
*/
Gerp::Gerp() {
    
}

/* runGerp
    Purpose: runs Gerp. goes through directory given and
        allows user to search for words, putting the lines the word
        appears into a outfile.
    Parameters: a string for the name of the file / directory given to search
        through, a string for the name of the outfile where the lines used in
        searched words will initilially go, and the istream of the commands the
        user will give
    Returns: void
    Effect: Runs the whole gerp work, calls functions which gather all the 
        lines and allow user to search for where words are used in files
*/
void Gerp::runGerp(string FN, string OF, istream &input) {
    ifstream instream; //create instream
    instream.open(FN); //open file
    if (not instream.is_open()) {
        //if not opened properly
        cerr << "Could not build index, exiting." << endl;
        return;
    } else {
        //close so it can be opened by FSTree
        instream.close();
    }

    //create tree
    FSTree *tree = new FSTree(FN);

    int lineNum = 0;

    //creates vector of all lines
    FSTreeTraversal(tree->getRoot(), "", lineNum);
    query(OF, input); //query loop
    tree->burnTree(); //deallocate 
    delete tree;
}

/* query
    Purpose: Query command of the commands the user can ask gerp to do
        searchs for word (case sensitive or insesitive), redirect to a new
        output file, and can quit the query loop
    Parameters: a string for the name of the initial outfile, and the istream of
        the commands the user does
    Returns: void
    Effect: gets command from user and finds lines the word is in or changes
        the output file, or quits gerp
*/
void Gerp::query(string OF, istream &input) {
    string command;

    ofstream myfile;
    myfile.open(OF);
    
    while (not input.eof()) { //ends when inquery file ends
        cout << "Query? ";
        input >> command;

        if (command == "@q" or command == "@quit") { //quit function
            cout << "Goodbye! Thank you and have a nice day." << endl;
            myfile.close();
            return;
        } else if (command == "@f") { //creates new folder
            input >> command;
            myfile.close(); //closes old folder
            myfile.open(command); //opens new folder given
        } else if (command == "@i" or command == "@insensitive") {

            input >> command;
            stripNonAlphaNum(command); //gets rid of non-AlphaNum chars
            if (not command.empty()) { //if command is not empty
                myfile << h.caseInsensitiveSearch(command);
            } else {
                myfile << " Not Found.\n";
            }

        } else { //regular search
            stripNonAlphaNum(command); //gets rid of non-AlphaNum chars
            if (not command.empty()) { //if command is not empty
                myfile << h.search(command);
            } else {
                myfile << " Not Found. Try with @insensitive or @i.\n";
            }
        }
        
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

/* FSTreeTraversal
    Purpose: creates the full paths of each file in the directory
    Parameters: a DirNode pointer of the directory that file will that 
        will printed, a string of the path that got to file,
        and a int of the linenumber of each line in the vector
        being created
    Returns: void function
    Effect: recursive function which creates the paths and calls function
        that will edit each path
*/
void Gerp::FSTreeTraversal(DirNode *root, string dList, int &lineNum) {
    //base case
    if(root->isEmpty()){
        return;
    }
    else {
        //put name of directory
        dList += root->getName();
        //goes through each file in root
        for (int i = 0; i < root->numFiles(); i++) {
            //prints out path of file without adding file name to dList
            traversalHelper(root, dList, i, lineNum);
        }
        //goes through each sub directory in root
        for(int i = 0; i < root->numSubDirs(); i++){
            //recusivley goes to next sub dir
            FSTreeTraversal(root->getSubDir(i), dList + "/", lineNum); 
        }


    }
}

/* TraversalHelper
    Purpose: makes the full paths of each file in directory
    Parameters: a DirNode pointer of the directory of the file 
        being looked at, a string of the path that got to file,
        an int of which file needed to be printed,
        and an int of the linenumber of each line in the vector
    Returns: void function
    Effect: creates a file path of file and sends it to be read
*/
void Gerp::traversalHelper(DirNode *root, string dList, int i, int &lineNum) {
    //gets the path of file
    dList += "/" + root->getFile(i);
    runDir(dList, lineNum);
}

/* runDir
    Purpose: makes the full paths of each file in directory and adds it to
        vector in hashTable, and puts where in the vector it is into
        the buckets
    Parameters: the string of the directory path, and an int of where
        in the vector of lines the new line will be
    Returns: void function
    Effect: reads file and puts each line into a vector and puts words
        into a 3dvector of buckets
*/
void Gerp::runDir(string &dList, int &lineNum){
    ifstream instream; //open file
    instream.open(dList);
    if (not instream.is_open()) {
        cerr << "Could not build index, exiting." << endl;
        return;
    }
    
    int fileLine = 1;

    string current_line;
    string indivWord;
    while (not getline(instream, current_line).fail()) { //gets line
        stringstream ss(current_line);
        string line = dList + ":" + to_string(fileLine) + ": " + current_line;
        while (ss >> indivWord) { //goes through each word on line
            stripNonAlphaNum(indivWord);
            h.insert(indivWord, lineNum); //makes bucket
        }
        h.addLine(line); //adds line to vector
        fileLine++;
        lineNum++;
    }
    instream.close(); //closes vector
}

/* stripNonAlphaNum
    Purpose: removes all leading and trailing non-alphanumeric characters from
    the given string
    Parameters: given string 
    Returns: processed string
*/
void Gerp::stripNonAlphaNum(string &input) {
    int size = input.size();
    int start = 0, end = size;
    int i = 0;
    //while the character's ASCII value is in the range of non-alphanum chars
    while (not isalnum(input[i])) {
        //if the entire string is traversed without reaching alphanum char
        if(i == size) { 
            input = ""; //return empty string
            return;
        }
        i++; //increment i
        start = i; //set the start for substring
    }

    i = size -1; //to traverse backwards
    //while the character's ASCII value is in the range of non-alphanum chars
    while (not isalnum(input[i])) {
        i--; //decrement i
        end = i; // set the end for substring
    }

    input = input.substr(start, end - start + 1); //return processed string
}
