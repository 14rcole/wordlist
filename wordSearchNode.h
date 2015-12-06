#ifndef _word_tree_node_h_
#define _word_tree_node_h_

#include <list>
#include <string>

using namespace std;

namespace prog8lib{
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
