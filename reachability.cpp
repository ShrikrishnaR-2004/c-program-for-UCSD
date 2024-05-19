#include <iostream>
#include <vector>
using namespace std; 
using std::vector;
using std::pair;

// Search for path between x and y
int search(vector<vector<int> > &adj, int x, int y, vector<int> &visited) {

 // If x and y are the same, a path is found
 if (x == y) {
    return 1;
 }

 // Mark x as visited
 visited[x] = 1;

 // Iterate through all adjacent vertices of x
 for(int i = 0; i < adj[x].size(); i++) {

    // If the adjacent vertex is not visited, search recursively
    if (!visited[adj[x][i]]) {
      if(search(adj, adj[x][i], y, visited)) {
        return 1;
      }
    }
 }

 // If no path is found, return 0
 return 0;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  vector<int> visited(adj.size());
  return search(adj, x, y, visited);
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x - 1, y - 1);
}
