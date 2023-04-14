#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/graphviz.hpp>
#include <bits/stdc++.h>
using namespace boost;
using namespace std;

struct VertexProperties{
    unsigned id;

    VertexProperties() : id(0) {}
    VertexProperties(unsigned _id): id(_id){}
};

typedef adjacency_list_traits < vecS, vecS, directedS > Traits;
typedef adjacency_list < listS, vecS, directedS,
    property < vertex_name_t, std::string >,
    property < edge_capacity_t, long,
    property < edge_residual_capacity_t, long,
    property < edge_reverse_t, Traits::edge_descriptor > > > > Graph;


typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;


int min(int a, int b){
    return a <= b ? a : b;
}

long edmondKarps(vertex_t s, vertex_t t, Graph& g){
    long flow = 0;
    int i = 0;
    vector<vertex_t> parent(num_vertices(g));
    property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
    property_map<Graph, edge_residual_capacity_t>::type residual_capacity = get(edge_residual_capacity, g);
    property_map<Graph, edge_reverse_t>::type rev_map = get(edge_reverse, g);

    while (true) {
        // Run a BFS from s to t, searching for an augmenting path
        std::queue<vertex_t> q;
        q.push(s);
        fill(parent.begin(), parent.end(), graph_traits<Graph>::null_vertex());
        parent[s] = s;
        
        while (!q.empty() && parent[t] == graph_traits<Graph>::null_vertex()) {
            vertex_t u = q.front();
            q.pop();
            for (auto e : make_iterator_range(out_edges(u, g))) {
                vertex_t v = target(e, g);
                if (parent[v] == graph_traits<Graph>::null_vertex() && residual_capacity[e] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        // If no augmenting path was found, terminate
        if (parent[t] == graph_traits<Graph>::null_vertex()) {
            break;
        }

        // Determine the maximum flow that can be added along the augmenting path
        long path_flow = numeric_limits<long>::max();
        vector<vertex_t> pathForward;
        long min_flows = INT_MAX;
        for (vertex_t u = t; u != s; u = parent[u]) {
            auto e = edge(parent[u], u, g).first;
            path_flow = min(path_flow, residual_capacity[e]);
            pathForward.push_back(u);
            min_flows = min(min_flows, residual_capacity[e]);
            // cout << parent[u] << "->" << u << ":" << residual_capacity[e] << "\n";
        }
        pathForward.push_back(s);

        for(int i = pathForward.size()-1; i >= 0; i--){
            cout << pathForward[i] << (i == 0 ? " " : " -> ");
        }
        cout << ":+" << min_flows << "\n";


        // Add the path flow to the overall flow, and update the residual capacities and reverse edges
        for (vertex_t u = t; u != s; u = parent[u]) {
            auto e = edge(parent[u], u, g).first;
            auto rev_e = rev_map[e];
            residual_capacity[e] -= path_flow;
            residual_capacity[rev_e] += path_flow;
        }
        flow += path_flow;
    }

    return flow;
}

int main() {
    Graph g;
    Traits::vertex_descriptor s, t;
    const vector<string> names= {"0", "1", "2","3","4","5","6","7","8"};

    property_map < Graph, edge_capacity_t >::type capacity = get(edge_capacity, g);
    property_map < Graph, edge_reverse_t >::type rev = get(edge_reverse, g);
    property_map < Graph, edge_residual_capacity_t >::type residual_capacity = get(edge_residual_capacity, g);

    read_dimacs_max_flow(g, capacity, rev, s, t);

    // Update the residual capacity available (unused flow)
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
        residual_capacity[*ei] = capacity[*ei];
    }

    long maxFlow = edmondKarps(s, t, g);

    cout << "Max Flow: " << maxFlow << "\n";
    print_graph(g);    
    std::string filenameRes = "res.dot";
    std::ofstream outRes(filenameRes.c_str());

    write_graphviz(outRes, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng res.dot > res.png");

    return 0;
}