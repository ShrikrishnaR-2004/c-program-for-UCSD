#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie buildtrie(vector<string> & patterns) {
  trie t;
  // write your code here
   for (int i = 0; i < patterns.size(); i++) {
    int x = 0;
    for (int j = 0; j < patterns[i].size(); j++) {
      bool match_found = false;
      if (x < t.size()) {
        for (const auto & k : t[x]) {
          if (k.first == patterns[i][j]) {
            x = k.second;
            match_found = true;
            break;
          }
        }
        if (!match_found) {
          t[x].insert(pair<char, int> (patterns[i][j], t.size()));
          x = t.size();
        }
      } else {
        map<char, int> m;
        m.insert(pair<char, int> (patterns[i][j], t.size() + 1));
        t.push_back(m);
        x = t.size();
      }
    }
    map<char, int> m;
    //m.insert(pair<char, int> ('$', -1));
    t.push_back(m);
  }
  return t;
}

int main() {
  size_t n;
  cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    cin >> s;
    patterns.push_back(s);
  }

  trie t = buildtrie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}