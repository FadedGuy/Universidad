#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/graph_utility.hpp>
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

set<int> marquer(Graph g, vertex_t s, vertex_t t) {
    set<int> L;
    vector<int> marquage(num_vertices(g));

    // Get capacity of a given node
    L.insert(s);
    marquage[s] = 1;
    auto capacity = get(edge_capacity, g);

    while(!L.empty() && marquage[t] == 0) {
        auto i = L.begin();  
        L.erase(i);
        auto neighbors = out_edges(*i, g);
        // take neighbors and 
        // if (i->j) and flow(i,j) < capacity(i,j) alors j marque +1 et capacity(j) = min(capacity(i), capacity(j)-flow)  
        // else if (j->i) and flow(j,i) > 0 (residuel) alors j marque -1 et capacity(j) = min(capacity(i), flow)
        
    }
    return L;
}

int main() {
    Graph g;
    Traits::vertex_descriptor s, t;
    const vector<string> names= {"0", "1", "2","3","4","5","6","7","8"};

    property_map < Graph, edge_capacity_t >::type capacity = get(edge_capacity, g);
    property_map < Graph, edge_reverse_t >::type rev = get(edge_reverse, g);
    property_map < Graph, edge_residual_capacity_t >::type residual_capacity = get(edge_residual_capacity, g);

    read_dimacs_max_flow(g, capacity, rev, s, t);

    set<int> res = marquer(g, s, t);
    print_graph(g);    
    std::string filenameRes = "res.dot";
    std::ofstream outRes(filenameRes.c_str());

    write_graphviz(outRes, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng res.dot > res.png");

    return 0;
}