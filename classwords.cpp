#include <string>
#include <limits>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "classwords.h"

using namespace std;

/** Constructor for PathSearch objects
 */
PathSearch::PathSearch(string begin, string end, string dictFilename){
    if(begin.length() != end.length()){
        cerr << "Words must be the same length" << endl;
        exit(EXIT_FAILURE);
    }

    beginWord = begin;
    endWord = end;
    string newFileName = "newWords";
    ostringstream s;
    s << "awk 'length==" << beginWord.length() << "' words > " << newFileName;
    system(s.str().c_str());

    ifstream dictFile(newFileName.c_str(), ifstream::in);

}

/** Destructor for PathSearch objects
 */
PathSearch::~PathSearch(){
    dictFile.close();
}

/** A* search method
 * Not finished
 */
stack<string> PathSearch::aStarSearch(){
    list<string> closedSet;
    list<string> openSet(1, beginWord);
    map<string, string> cameFrom;

    map<string, int> gScores;
    gScores.insert(std::pair<string, int>(beginWord, 0));
    map<string, int> fScores;
    fScores.insert(std::pair<string, int>(beginWord, gScores[beginWord] + editDistance(beginWord, endWord)));

    string last = lowestFScore(fScores);
    string current;
    while(openSet.size() != 0){
        current = lowestFScore(fScores);
        if(current.compare(endWord) == 0){
            return reconstructPath(cameFrom, endWord);
        }

        openSet.remove(current);
        closedSet.push_front(current);
        list<string> neighbors = getNeighbors(current, last);
        for(list<string>::iterator neighborIterator = neighbors.begin(); neighborIterator != neighbors.end(); neighborIterator++){
            if(inSet(*neighborIterator, closedSet)){
                continue;
            }
            int tentativeGScore = gScores[current] + editDistance(current, *neighborIterator);
            if(!inSet(*neighborIterator, openSet)){
                openSet.push_front(*neighborIterator);
            }else if(tentativeGScore > gScores[*neighborIterator]){
                continue;
            }

            cameFrom.insert(pair<string, string>(*neighborIterator, current));
            gScores.insert(pair<string, int>(*neighborIterator, tentativeGScore));
            fScores.insert(pair<string, int>(*neighborIterator, gScores[*neighborIterator] + editDistance(*neighborIterator, endWord)));
        }
    }

    stack<string> retStack;
    return retStack;
}

/** inSet helper method for A* algorithm
 * Returns true if the passed in string is a part of the passed in list
 */
bool PathSearch::inSet(string item, list<string> set){
    for(list<string>::iterator setIterator = set.begin(); setIterator != set.end(); setIterator++){
        if(item.compare(*setIterator) == 0){
            return true;
        }
    }
    return false;
}

/** Estimates the number of changes required to make one string into another
 */
int PathSearch::editDistance(string word1, string word2){
    int dist = 0;

    if(word1.length() != word2.length()){
        return -1;
    }
    
    for(int i = 0; i < word1.length(); i++){
        if(word1[i] != word2[i]){
            dist++;
        }
    }
}

/** Determine the lowest f score in the map and return the element with it
 */
string PathSearch::lowestFScore(map<string, int> scores){
    int lowest = numeric_limits<int>::max();
    string node = "";
    for(map<string, int>::iterator fScoreIterator = scores.begin(); fScoreIterator != scores.end(); fScoreIterator++){
        if(lowest > fScoreIterator->second){
            lowest = fScoreIterator->second;
            node = fScoreIterator->first;
        }
    }
    return node;
}

/** Once a path has been reached, reconstruct it as a stack and return the stack
 */
stack<string> PathSearch::reconstructPath(map<string, string> cameFrom, string current){
    stack<string> path;
    path.push(current);
    return path;
}

/**Get all words which have an edit distance of one from the current string, and whose
 * changed letter is different from the letter that was changed previously
 */
list<string> PathSearch::getNeighbors(string current, string last){
    list<string> neighbors;
    int lastPos = lastEditPosition(current, last);
    //Seek to beginning of file
    dictFile.clear();
    dictFile.seekg(0, dictFile.beg);
    int c = dictFile.peek();
    while(c != EOF){
        string line;
        getline(dictFile, line);
        int dist = editDistance(current,line);
        if(dist == 1){
            if(line[lastPos] == current[lastPos]){
                neighbors.push_front(line);
            }
        }
        c = dictFile.peek();
    }
    return neighbors;
}

/** Helper method for the getNeighbors method
 * returns the index of the character has changed in the last movement along
 * the path from the last word to the current word
 */
int PathSearch::lastEditPosition(string first, string second){
    for(int i = 0; i < first.length(); i++){
        if(first[i] != second[i]){
            return i;
        }
    }
    return -1;
}

int main(){
    return 0;
    PathSearch ps("
}
