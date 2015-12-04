#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <memory>
using namespace std;
static const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const size_t ALPHA_LEN = ALPHA.length();

// a naive word distance
int dist(const string &a, const string &b) {
    size_t l = a.length();
    if (l != b.length()) return INT_MAX;
    int d = 0;
    for (size_t i = 0; i < l; i++) {
        if (a[i] != b[i]) d++;
    }
    return d;
}

bool in_dict(const vector<string> &words,const string &w) {
    return  binary_search(words.begin(),words.end(),w);
}

bool in_vec(const  vector< string> &chain,const  string &w) {
  //for (auto& c:chain) if (c == w) return true;
  //return false;
  for(auto cc=chain.begin();cc != chain.end();++cc){
     string const &c=*cc;
    if(c==w)
      return true;
    //else  
    // return false;
  }
  return false;
}

// replace letters to find new candidates. at this point we only insist that they be words
 vector< string> chain_candidates(const  string &src,
                                          const  string &dest,
                                          const  vector< string> &words) {
     vector< string> candidates;
    size_t l = src.length();
    for (size_t i = 0; i < l; i++) {
        if (src[i] != dest [i]) {
            for (size_t j = 0; j < ALPHA_LEN; j++) {
	       string c(src);
                c.replace(i,1, string{ALPHA[j]});
                if (in_dict(words,c)) candidates.push_back(c);
            }
        }
    }
    return candidates;
}

// given a list of candidate words that may form the next link in the chain,
// assert that they actually are new (not seen before), and that they 
// represent progress (distance to dest is lower
// than dest_dist, the distance to dest for the last word in the chain),
// and then sort them by this distance, so we can choose candidates that
// have the shortest distance to dest first.
 vector< string> viable(const  vector< string> &candidates,
                                const  string &dest,
                                size_t dest_dist,
                                const  vector< string> &chain,
                                const  vector< string> &seen) {
     vector< pair<int, string>> pv;
    //  for (auto& c:candidates) {
    for(auto cc=candidates.begin();cc!=candidates.end();++cc){
       string const &c=*cc;
      

      size_t d = dist(c,dest);

      if ((!in_vec(chain,c)) && (!in_vec(seen,c)) && (d <= dest_dist)) {

	pv.push_back( pair<int, string>{d,c});
        }
    }
     vector< string> v;
    // no candidates, so return empty vector
    if (pv.empty()) return v;
    // reverse (descending) sort so lowest (closest) distance is at the end 
    //     sort(pv.begin(),pv.end(),
	      // [](const  pair<int, string> &a,const  pair<int, string> &b) { 
		//                  return a.first > b.first; });
    //for (auto& a: pv) {
    for(auto cc=pv.begin();cc!=pv.end();++cc){
       pair<int, string> const &a=*cc;
        v.push_back(a.second);
    }
    return v;
}

// try to make a word chain from src to dest.
// algorithm: maintain two arrays, chain and candidates.
// the chain will represent the progress so far
// the candidates will represent those words which progress from the end of chain
// to the destination, meaning they are "closer" by chars (our dist function)
// to the destination string. when candidates are considered, they are added to 
// the end of the chain. if a candidate reaches the destination string, we are done.
// if a candidate does not make progress, it is removed from the candidates list 
// and the chain. this is loosely described as a depth-first-search.
 vector< string> make_chain(const  string &src,
                                    const  string &dest,
                                    const  vector< string> &words) {
     vector< string> candidates{src};
     vector< string> seen{src};
     vector< string> chain{};
    // cerr<<"flag";
    while (!candidates.empty()) {
        auto b = candidates.back();
        chain.push_back(b);
        if (b == dest) return chain;
	// cerr<<"flag";
	
        candidates.pop_back();
         vector< string> cs = viable(chain_candidates(b,dest,words),
                                             dest,
                                             dist(b,dest),
                                             candidates,
                                             seen);
        if (cs.empty()) {
            // no viable candidates could be found to move forward in the chain. 
            // so we should get rid of the current last link, it is a dead end
            chain.pop_back();
        } else {
            // we have some candidates. we received them back from the viable
            // func in descending order of distance to dest, so the last word
            // in the candidates vector is the one we want to try next
            //for (auto& c:cs) {
	  for(auto cc=cs.begin();cc!=cs.end();++cc){
	     string const &c=*cc;
                candidates.push_back(c);
                seen.push_back(c);
            }
        }
    }
    return  vector< string>{}; // no chain!
}

int main(int argc,char **argv) {
  // if (argc != 3) {
  //       cerr << "use: wordchain src dest" <<  endl;
  //       exit(1);
  //  }
    // cout<<"flag";
    // lowercase both args
    // string src{argv[1]};
    // string dest{argv[2]};
  //transform(src.begin(), src.end(), src.begin(),::toupper);
  //  transform(dest.begin(), dest.end(), dest.begin(),::toupper);    
    // cout<<"flag";
    
    // read in the local dictionary
    //  const  string dict_fn{"dictionary.txt"};
    // cout<<"flag";
    
     ios_base::sync_with_stdio(false);
    // cout<<"flag";
    // ifstream dict("dictionary.txt");
     ifstream dict("words");
    // ifstream dict(dict_fn,ifstream::in);
    // cout<<"flag";
    
    //dict.open(dict_fn);
    // cout<<"flag";
    
    if (!dict.is_open()) {
         exit(1);
    }
    // cout<<"flag";
    
     string line;
     vector< string> words;
    while (dict >> line) {
        words.push_back(line);
    }
    dict.close();
    //     cerr<< words.size();
	//for(unsigned int a=0;a<words.size();a++){
	//  cerr<<words.at(a)<< endl;
	// }

    // must be the same length
     ifstream classwords("classwords.txt");
     string li;
     vector< string> cl;
    while(classwords>>li){
      cl.push_back(li);
    }
        classwords.close();
    //      cerr<< cl.size();
	// for(unsigned int a=0;a<cl.size();a++){
	// cerr<<cl.at(a)<< endl;
	//  }
	int count=0;
	while(count<cl.size()){
	  string x=cl.at(count);
	  count++;
	  cout<<x<<" ";
	  string y=cl.at(count);
	  if(in_dict(words,y)){
	    if(in_dict(words,cl.at(count+1))){
	      string z=cl.at(count+1);
	      //cout<<y<<" "<<z<<endl;
	      vector< string> ch = make_chain(y,z,words);
	      if (ch.empty()) {
		cout << "Invalid " <<y<<" "<<z<<  endl;
	      } else {
		//for (auto &c:ch) {
		for(auto cc=ch.begin();cc!=ch.end();++cc){
		  string const &c=*cc;
		  cout << c << " ";
		}
		cout <<  endl;
	      }
	      count++;
	      count++;
	      }
	    else{
	      cout<<"Invalid"<<endl;
	    }

	  }
	  else{
	    cout<<"Invalid"<<endl;
	  }
	  //cout<<cl.at(count)<<endl;
	  //count++;
	    /* if (src.length() != dest.length()) {
         cerr << src << " and " << dest << " must be the same length" <<  endl;
         exit(1);
    }
    if (!(in_dict(words,src) && in_dict(words,dest))) {
         cerr << src << " and " << dest << " must be in the dictionary" <<  endl;
         exit(1);
	 }*/
	    /*
     vector< string> ch = make_chain(x,y,words);
    if (ch.empty()) {
      cout << "Invalid " <<y<<" "<<x<<  endl;
    } else {
      //for (auto &c:ch) {
      for(auto cc=ch.begin();cc!=ch.end();++cc){
	 string const &c=*cc;
             cout << c << " ";
        }
         cout <<  endl;
	 }
	    */
	}
	    
    return 0;
}
