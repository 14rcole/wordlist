#include <string>
#include <list>
#include <stack>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "classwords.h"
#include "wordSearchNode.h"

using namespace std;

prog8::WordSearch::WordSearch(string start, string end, string dictionary){
    if(start.length() != end.length()){
        cerr << "Error: words must be of the same length";
        exit(1);
    }

    begin = new prog8lib::WordSearchNode(start, NULL);
    goal = end;

    ostringstream s;
    s << "awk 'length==" << start.length() << "' words > newWords";
    system(s.str().c_str());
    dictStream.open("newWords", fstream::in | fstream::out);
}

prog8::WordSearch::~WordSearch(){
    delete begin;
    dictStream.close();
}

stack<string> prog8::WordSearch::findWordPath(){
    list<prog8lib::WordSearchNode*> beginList;
    beginList.push_front(begin);
    prog8lib::WordSearchNode* endNode = breadthFirstSearch(beginList);
    stack<string> wordPath; 
    if(endNode == NULL){
        return wordPath;
    }
    prog8lib::WordSearchNode* curNode = endNode;
    while(curNode->hasParent()){
        wordPath.push(curNode->getWord());
        curNode = curNode->getParent();
    }
    wordPath.push(curNode->getWord());
    return wordPath;
}

prog8lib::WordSearchNode* prog8::WordSearch::breadthFirstSearch(list<prog8lib::WordSearchNode*> words){
    list<prog8lib::WordSearchNode*> neighbors;
    for(list<prog8lib::WordSearchNode*>::iterator it=words.begin(); it != words.end(); it++){
        list<prog8lib::WordSearchNode*> n = findNeighbors(*it);
        neighbors.merge(n);
    }

    if(neighbors.size() == 0){
        cout << "No path between " << begin->getWord() << " and " << goal << endl;
        return new prog8lib::WordSearchNode(NULL, NULL);
    }

    for(list<prog8lib::WordSearchNode*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
        if((*it)->getWord().compare(goal) == 0){
            return (*it);
        }
    }

    return breadthFirstSearch(neighbors);
}

list<prog8lib::WordSearchNode*> prog8::WordSearch::findNeighbors(prog8lib::WordSearchNode* node){
    dictStream.seekg(0, dictStream.beg);
    string current = node->getWord();
    prog8lib::WordSearchNode* parent = node->getParent();
    string last;
    if(parent == NULL){
        last = current;
    }else{
        last = parent->getWord();
    }
    int lastChanged = diffIndex(current, last);
    list<prog8lib::WordSearchNode*> neighbors;
    int c = dictStream.peek();
    while(c != EOF){
        string possibleWord;
        getline(dictStream, possibleWord);
       if(editDistance(current, possibleWord) == 1 && diffIndex(current, possibleWord) != lastChanged && !used(possibleWord)){
            prog8lib::WordSearchNode* childNode = new prog8lib::WordSearchNode(possibleWord, node);
            neighbors.push_front(childNode);
            usedWords.push_front(possibleWord);
       }
       c = dictStream.peek();
    }
    return neighbors;
}

int prog8::WordSearch::editDistance(string word1, string word2){
    int dist = 0;
    for(unsigned int i = 0; i < word1.size(); i++){
        if(word1[i] != word2[i]){
            dist++;
        }
    }
    return dist;
}

/*Determines the last changed character so that character is not repeatedly
 * changed. This may not even really matter because of the usedWords list and
 * the way that a breadth first search takes all possibilities into account but
 * its a good safeguard anyway
 */
int prog8::WordSearch::diffIndex(string word1, string word2){
    for(unsigned int i = 0; i < word1.size(); i++){
        if(word1[i] != word2[i]){
            return i;
        }
    }
    return -1;
}

bool prog8::WordSearch::used(string word){
    for(list<string>::iterator it = usedWords.begin(); it != usedWords.end(); it++){
        if(word.compare((*it)) == 0){
            return true;
        }
    }
    return false;
}

void printStack(stack<string> st){
    if(st.empty()){
        cerr << "No path between the two words\n";
        return;
    }

    cout << st.top();
    st.pop();
    while(!st.empty()){
        cout << "-->" << st.top();
        st.pop();
    }
}

int main(){
    string word1 = "ABED";
    string word2 = "BUTT";
    prog8::WordSearch ws(word1, word2, "words");
    stack<string> path = ws.findWordPath();
    cout << "The path between " << word1 << " and " << word2 << " is\n";
    printStack(path);
    return 0;
}
