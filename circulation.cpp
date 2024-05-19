#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <limits.h>

using namespace std;
#define fora(i, f, t) for(int i=f; i<t; i++)


struct Edge {
        int from, to, cost;
};

class Circle {
private:
    
    vector<Edge> edges;
    vector<vector<int>> init_flow;  
    vector<vector<size_t> > graph;  
    vector<int> lower_edges;        
    int numvertexes;                
    int numedges;                   
    int lowerBoundSum;              
    int maxflow;                    

public:
    
    void readdata(){
        int n;
        cin >> n >> numedges;
        numvertexes = n + 2;
        lowerBoundSum = 0;

        graph = vector<vector<size_t> >(numvertexes);
        init_flow = vector<vector<int>>(numvertexes+1, vector<int>(2, 0));

        fora (i, 0, numedges) {
            int u, v, low_bound,capacity;
            cin >> u >> v >> low_bound >> capacity;
            add_edge(u, v, capacity - low_bound);
            init_flow[u][1] += low_bound;
            init_flow[v][0] += low_bound;
            lowerBoundSum += low_bound;

            lower_edges.push_back(low_bound);
        }
    }

    void solve(){
        add_source_sink();
        maxFlow();
    }

    void print(){
        if(maxflow == lowerBoundSum){
            cout<<"YES"<<endl;
            fora(i, 0, numedges)
                cout<<lower_edges[i] + edges[2*i + 1].cost<<endl;
        }else cout<<"NO"<<endl;
    }

    void add_edge(int from, int to, int cost) {
        Edge forward_edge = {from, to, cost};
        Edge backward_edge = {to, from, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    void update_flow(size_t id, int flow) {
        edges[id].cost -= flow;         //forward edge
        edges[id ^ 1].cost += flow;     //backward edge
    }

    void add_source_sink(){
        fora(i, 1, numvertexes-1){
            add_edge(0, i, init_flow[i][0]);
            add_edge(i, numvertexes-1, init_flow[i][1]);
        }
    }


    void bfs(vector<vector<int>>& parents){
        set<int> visited = {0};  
        queue<int> nodes;       
        nodes.push(0);

        while(!nodes.empty()){
            int curNod = nodes.front();
            nodes.pop();

     
            for(const auto& edgeid : graph[curNod]){
                const Edge edge= edges[edgeid];
                if(edge.cost > 0 && visited.find(edge.to) == visited.end()){
                    nodes.push(edge.to);
                    visited.insert(edge.to);

                    parents[edge.to][0] = curNod;      
                    parents[edge.to][1] = edgeid;       
                    if(edge.to == numvertexes-1) return;
                }
            }
        }
    }

    int findAp(vector<vector<int>>& parents){

        bfs(parents);
        int minres = INT_MAX;
        int curnode = numvertexes-1;
        while(parents[curnode][0] != - 1){
            const Edge edge = edges[parents[curnode][1]];
            minres = min(minres, edge.cost);
            curnode = parents[curnode][0];
        }
        return minres;   
    }

    void maxFlow(){
        vector<vector<int>> parents(numvertexes, vector<int>(2, -1));     
        int mr;                  
        maxflow = 0;             

        while((mr=findAp(parents)) != INT_MAX){
            int curnode = numvertexes - 1;
            while(parents[curnode][0] != - 1){
                const Edge edge = edges[parents[curnode][1]];
                update_flow(parents[curnode][1], mr);
                curnode = parents[curnode][0];
            }

            maxflow += mr;

            fora(i, 0, parents.size())
                parents[i][0] = parents[i][1] = -1;
        }
    }
};

int main() {
    Circle circle;
    circle.readdata();
    circle.solve();
    circle.print();
    return 0;
}