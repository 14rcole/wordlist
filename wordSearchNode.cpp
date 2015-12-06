#include <list>
#include <string>

#include "wordSearchNode.h"

using namespace std;

/* Constructor for the WordSearchNode class
 */
prog8lib::WordSearchNode::WordSearchNode(string w, WordSearchNode* p){
    word = w;
    parent = p;
}

/* Destructor for the WordSearchNode class
 */
prog8lib::WordSearchNode::~WordSearchNode(){
    delete parent;
}

/* Return the word
 */
string prog8lib::WordSearchNode::getWord(){
    return word;
}

/*Returns true if the parent is not NULL
 */
bool prog8lib::WordSearchNode::hasParent(){
    if(parent != NULL){
        return true;
    }else{
        return false;
    }
}

/* Returns a pointer to the parent node
 */
prog8lib::WordSearchNode* prog8lib::WordSearchNode::getParent(){
    return parent;
}

