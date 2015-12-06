#ifndef _classwords_h_
#define _classwords_h_

#include <string>
#include <list>
#include <stack>
#include <fstream>

#include "WordSearchNode.h"

using namespace std;
namespace prog8 {
    /* Class declaration for the main class
     * When findWordPath is called, a breadth first search is used to search
     * through the dictionary to find the shortest path
     */
    class WordSearch {
        public:
            WordSearch(string start, string end, string dictionary);
            ~WordSearch();
            stack<string> findWordPath();
        private:
            prog8lib::WordSearchNode* begin;
            string goal;
            list<string> usedWords;
            fstream dictStream;
            prog8lib::WordSearchNode* breadthFirstSearch(list<prog8lib::WordSearchNode*> words);
            list<prog8lib::WordSearchNode*> findNeighbors(prog8lib::WordSearchNode* node);
            int editDistance(string word1, string word2);
            int diffIndex(string word1, string word2);
            bool used(string word);
    };
}
#endif
