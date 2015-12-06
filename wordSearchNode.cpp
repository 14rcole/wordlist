#include <list>
#include <string>

#include "wordSearchNode.h"

using namespace std;

prog8lib::WordSearchNode::WordSearchNode(string w, WordSearchNode* p){
    word = w;
    parent = p;
}

prog8lib::WordSearchNode::~WordSearchNode(){
    delete parent;
}

string prog8lib::WordSearchNode::getWord(){
    return word;
}

bool prog8lib::WordSearchNode::hasParent(){
    if(parent != NULL){
        return true;
    }else{
        return false;
    }
}

prog8lib::WordSearchNode* prog8lib::WordSearchNode::getParent(){
    return parent;
}

