#include <iostream>
#include <vector>
using namespace std;
using std::vector;
using std::pair;

int search(vector<vector<int> > &adj, int x, vector<int> &visited, vector<int> &recStack) 
{
  visited[x] = 1;
  recStack[x] = 1;
  for (int i = 0; i < adj[x].size(); i++) 
  {
    if (!visited[adj[x][i]] && search(adj, adj[x][i], visited, recStack))
	    return 1;
	  else if(recStack[adj[x][i]])
	    return 1;
  }
  recStack[x] = 0; 
  return 0;
}

int acyclic(vector<vector<int> > &adj) 
{
  vector<int> visited(adj.size());
  vector<int> recStack(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i]) 
    {
      if (search(adj, i, visited, recStack)) 
        return 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << acyclic(adj);
}
