#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

using std::vector;
using std::queue;

int dist(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  if (s == t) {
	return 0;
  }
  
  vector<int> dist(adj.size());
  for(int i=0; i<dist.size();i++){
    dist[i] = numeric_limits<int>::max();
  }
  
  dist[s] = 0;
  queue<int> queue;
  

  queue.push(s);
  while(!queue.empty()) 
  {
    int u = queue.front();
	  queue.pop();
    for(int i=0; i < adj[u].size(); ++i) 
    {
      int v = adj[u][i];
	    if(dist[v] == numeric_limits<int>::max()) 
      {
		    queue.push(v);
		    dist[v] = dist[u] + 1;
	    }
	  }
  }
  
  if(dist[t] != numeric_limits<int>::max()) {
    return dist[t];
  }
  return -1;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << dist(adj, s, t);
}
