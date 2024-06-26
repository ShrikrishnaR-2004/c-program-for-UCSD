#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> findpattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string p_t = pattern + '$' + text;
  vector<int> s(p_t.size());
  int border = 0;
  for (int i = 1; i < p_t.size(); i++) {
    while (border > 0 && p_t[i] != p_t[border]) {
      border = s[border - 1];
    }
    if (p_t[i] == p_t[border]) {
      border++;
      s[i] = border;
    }
    if (border == 0) {
      s[i] = 0;
    }
  }
  for (int i = pattern.size() + 1; i < p_t.size(); i++) {
    if (s[i] == pattern.size()) {
      result.push_back(i - 2 * pattern.size());
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = findpattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
