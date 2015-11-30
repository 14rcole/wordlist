#include <string>
#include <queue>
#include <list>

using namespace std;

void aStarSearch(string begin, string end, string filename){
    list<string> closedSet;
    list<string> openSet(1, begin);

}

int editDistance(string word1, string word2){
    int dist = 0;

    if(word1.length() != word2.length()){
        return -1;
    }
    
    for(int i = 0; i < word1.length; i++){
        if(word1[i] != word2[i]){
            dist++;
        }
    }
}


