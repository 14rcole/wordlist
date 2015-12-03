#ifndef _shortestPath_h_
#define _shortestPath_h_

#include <string>
#include <limits>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

class PathSearch{
    public:
        PathSearch(string begin, string end, string dictFilename);
        ~PathSearch();
        stack<string> aStarSearch();

    private:
        string beginWord;
        string endWord;
        ifstream dictFile;
        int editDistance(string word1, string word2);
        bool inSet(string item, list<string> set);
        string lowestFScore(map<string, int> scores);
        stack<string> reconstructPath(map<string, string> cameFrom, string current);
        list<string> getNeighbors(string current, string last);
        int lastEditPosition(string first, string second);

};
#endif
