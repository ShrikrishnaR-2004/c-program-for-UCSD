#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

class Flowgrap {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
  
    vector<Edge> edges;
    vector<vector<size_t> > grap;

public:
    explicit Flowgrap(size_t n)
        : grap(n)
    {
        edges.reserve(n / 2);
    }
    inline void add_edge(int from, int to, int capacity)
    {
        Edge forward_edge = { from, to, capacity, 0 };
        Edge backward_edge = { to, from, 0, 0 };
        grap[from].push_back(edges.size());
        edges.push_back(forward_edge);
        grap[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    inline size_t size() const
    {
        return grap.size();
    }

    inline const vector<size_t>& get_ids(int from) const
    {
        return grap[from];
    }

    inline const Edge& get_edge(size_t id) const
    {
        return edges[id];
    }

    inline void add_flow(size_t id, int flow)
    {
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

vector<vector<int> > read_data(size_t num_stocks, size_t num_points)
{
    vector<vector<int> > stock_data(num_stocks, vector<int>(num_points));

    for (int i = 0; i < num_stocks; ++i)
        for (int j = 0; j < num_points; ++j) {
            std::cin >> stock_data[i][j];
        }

    return stock_data;
}

Flowgrap construct_grap(size_t num_stocks, size_t num_points)
{
    vector<vector<int> > stock_data = read_data(num_stocks, num_points);

    Flowgrap grap(num_stocks * 2 + 2);

    for (int i = 0; i < num_stocks; ++i) {
        grap.add_edge(0, i + 1, 1);
    }

    for (int i = 0; i < num_stocks; ++i) {
        int cur_stock = i;

        for (int j = 0; j < num_stocks; ++j) {
            if (j == cur_stock) {
                continue;
            }

            bool each_less{ true };

            for (int k = 0; k < num_points; ++k) {
                if (stock_data[i][k] >= stock_data[j][k]) {
                    each_less = false;
                    break;
                }
            }

            if (each_less) {
                grap.add_edge(i + 1, num_stocks + j + 1, 1);
            }
        }
    }
    for (int i = num_stocks + 1; i <= num_stocks * 2; ++i) {
        grap.add_edge(i, num_stocks * 2 + 1, 1);
    }

    return grap;
}

void BFS(const Flowgrap& grap, int s, int t, vector<int>& pred)
{
    queue<int> q;
    q.push(s);

    std::fill(pred.begin(), pred.end(), -1);

    while (!q.empty()) {

        int cur = q.front();
        q.pop();

        for (auto id : grap.get_ids(cur)) {

            const Flowgrap::Edge& e = grap.get_edge(id);

            if (pred[e.to] == -1 && e.capacity > e.flow && e.to != s) 
            {
                pred[e.to] = id;
                q.push(e.to);
            }
        }
    }
}

void max_flow(Flowgrap& grap, int s, int t)
{
    int flow = 0;

    vector<int> pred(grap.size());

    do {
        BFS(grap, s, t, pred);

        if (pred[t] != -1) {
            int min_flow = numeric_limits<int>::max();

            for (int u = pred[t]; u != -1; u = pred[grap.get_edge(u).from]) {
                min_flow = std::min(min_flow, grap.get_edge(u).capacity - grap.get_edge(u).flow);
            }
            for (int u = pred[t]; u != -1; u = pred[grap.get_edge(u).from]) {
                grap.add_flow(u, min_flow);
            }

            flow += min_flow;
        }

    } while (pred[t] != -1);
}

int min_overlaid_charts(const Flowgrap& grap, int num_stocks)
{

    int min_path_cover{ 0 };
    for (int i = 1; i <= num_stocks; ++i) {
        for (auto id : grap.get_ids(i)) {
            const Flowgrap::Edge& e = grap.get_edge(id);
            if (e.flow > 0) {
                ++min_path_cover;
                break;
            }
        }
    }

    return (num_stocks - min_path_cover);
}

int main()
{

    size_t num_stocks, num_points;
    cin >> num_stocks >> num_points;
    Flowgrap grap = construct_grap(num_stocks, num_points);
    max_flow(grap, 0, grap.size() - 1);
    cout << min_overlaid_charts(grap, num_stocks) << std::endl;
    return 0;
}