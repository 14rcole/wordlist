/*Ryan Cole
 * rbc218
 * Classwords program
 * Takes two words and determines the shortest path between them by changing
 * one letter at a time to form a new word
 */
//Including a LOT of stuff
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

/* Constructor for the WordSearch class
 */
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

/* Destructor for the WordSearch class
 */
prog8::WordSearch::~WordSearch(){
    delete begin;
    dictStream.close();
    remove("newWords");
}

/* Method that calls a breadth first search to get the WordSearchNode for the
 * goal (if it exists).  It then constructs a stack of all of the words tracing
 * back to the beginning node and returns that
 */
stack<string> prog8::WordSearch::findWordPath(){
    list<prog8lib::WordSearchNode*> beginList;
    beginList.push_front(begin);
    prog8lib::WordSearchNode* endNode = breadthFirstSearch(beginList);
    stack<string> wordPath; 
    if(endNode->getWord() == ""){ 
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

/*A breadth first search
 * Searches through all the possible "paths" at each level until it finds the
 * goal, then returns the goal
 */ 
prog8lib::WordSearchNode* prog8::WordSearch::breadthFirstSearch(list<prog8lib::WordSearchNode*> words){
    list<prog8lib::WordSearchNode*> neighbors;
    for(list<prog8lib::WordSearchNode*>::iterator it=words.begin(); it != words.end(); it++){
        list<prog8lib::WordSearchNode*> n = findNeighbors(*it);
        neighbors.merge(n);
    }

    if(neighbors.size() == 0){
        return new prog8lib::WordSearchNode("", NULL);
    }

    for(list<prog8lib::WordSearchNode*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
        if((*it)->getWord().compare(goal) == 0){
            return (*it);
        }
    }

    return breadthFirstSearch(neighbors);
}

/* For a given word, iterates through the dictionary and finds all words with
 * an edit distance of one from it where the changed letter is not the same as
 * the previously changed letter
 */
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

/* Calculates the edit distance between the two strings
 * Each letter that is different changes the edit distance by one
 * Assumes both strings are of the same length
 */
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

/*Checks the usedWords list to see if the passed in word has been used in the
 * search already
 */
bool prog8::WordSearch::used(string word){
    for(list<string>::iterator it = usedWords.begin(); it != usedWords.end(); it++){
        if(word.compare((*it)) == 0){
            return true;
        }
    }
    return false;
}

/*Not a part of any class, but prints each item in the passed in stack,
 * separated by a space
 */
void printStack(stack<string> st){
    if(st.empty()){
        cerr << "No path between the two words\n";
        return;
    }

    while(!st.empty()){
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

/* Main method
 */
int main(){
    fstream classWords("classwords.txt", fstream::in);
    int c = classWords.peek();
    string line;
    while(c != EOF){
        getline(classWords, line);
        istringstream linestream(line);
        string user, word1, word2;
        getline(linestream, user, ' ');
        getline(linestream, word1, ' ');
        getline(linestream, word2, '\n');
        if(word1.length() >= 1){
            prog8::WordSearch ws(word1, word2, "words");
            cout << "The path between " << word1 << " and " << word2 << " is\n";
            stack<string> path = ws.findWordPath();
            printStack(path);
        }
        c = classWords.peek();
    }
    return 0;
}
