#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/graph/graph_utility.hpp>
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
    int minFlow = INT_MAX;
    L.insert(s);
    // while(L.empty() == false && L.count(t) == 0) {
        
    // }
    return L;
}

int main() {


    Graph g;
    
    Traits::vertex_descriptor s, t;



}