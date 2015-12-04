#ifndef WORDLIST_H
#define WORDLIST_H

using namespace std;

class wordlist{
private:
  
public:
  const string Alpha ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const size_t ALPHA_LEN;
  int dist(const string &a, const string &b);
  bool in_dict(const vector<string> &words, const string &w);
  bool in_vec(const vector<string> &chain,const string &w)
  vector<string> viable(const vector<string> &candidates,
				    const string &dest,
				    size_t dest_dist,
				    const vector<string> &chain,
			const vector<string> &seen);
  vector<string> make_chain(const string &src,
				      const string &dest,
				      const vector<string> &words)
};
#endif
