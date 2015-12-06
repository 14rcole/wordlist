#ifndef _word_tree_node_h_
#define _word_tree_node_h_

#include <list>
#include <string>

using namespace std;

namespace prog8lib{
    /*Class definition for the wordSearchNode object
     * Stores data about the current word and its parent so that it can be
     * backtraced later on to output the path between the start and the goal
     */
    class WordSearchNode {
        public:
            WordSearchNode(string w, WordSearchNode* parent);
            ~WordSearchNode();
            string getWord();
            WordSearchNode* getParent();
            bool hasParent();
        private:
            string word;
            WordSearchNode* parent;
    };
}
#endif
