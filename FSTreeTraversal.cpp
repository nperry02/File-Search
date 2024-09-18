#include <string>
#include "DirNode.h"
#include <iostream>
#include <fstream>
#include "FSTree.h"

using namespace std;

/* TraversalHelper
    Purpose: print out the full paths of each file in directory
    Parameters: a DirNode pointer of the directory that file will that 
        will printed, a string of the path that got to file,
        and a int of which file needed to be printed
    Returns: void function
    Effect: prints out a file path of file
*/
void traversalHelper(DirNode *root, string dList, int i) {
    //prints out the path of file
    dList += "/" + root->getFile(i);
    cout << dList << endl;
}

/* FSTreeTraversal
    Purpose: print out the full paths of each file in directory
    Parameters: a DirNode pointer of the directory that file will that 
        will printed, a string of the path that got to file,
    Returns: void function / cout of file paths
    Effect: recursive function which prints out paths
*/
void FSTreeTraversal(DirNode *root, string dList) {
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
            traversalHelper(root, dList, i);
        }
        //goes through each sub directory in root
        for(int i = 0; i < root->numSubDirs(); i++){
            //recusivley goes to next sub dir
            FSTreeTraversal(root->getSubDir(i), dList + "/"); 
                //potential slow uh oh
        }
    }
}


int main(int argc, char *argv[])
{ 
    //if the right amount of arguments
    if (argc == 2) {

         ifstream instream;
        instream.open(argv[1]);
        if (not instream.is_open()) {
            cerr << "not worl";
            return 0;
            //throw std::runtime_error("Could not build index, exiting.");
        }
        else {
            instream.close();
        }
        //creates tree from file given
        FSTree *tree = new FSTree(argv[1]);

        //calls function
        FSTreeTraversal(tree->getRoot(), "");

        //deletes tree
        tree->burnTree();
        delete tree;
    }
    
    return 0; 
}