#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>
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

void marquer(Graph g, vertex_t s, vertex_t t) {
    // vector<int> alpha(num_vertices(g), 0);
    // vector<bool> marked(num_vertices(g), false);
    // vector<int> L;
    // graph_traits<Graph>::out_edge_iterator e, e_end;
    // property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
    // property_map<Graph, edge_residual_capacity_t>::type flow = get(edge_residual_capacity, g);
    // int MAX_FLOW_3 = INT_MIN;

    // alpha[s] = INT_MAX;
    // alpha[t] = INT_MAX;
    // marked[s] = true;
    // L.push_back(s);

    // while(!L.empty() && !marked[t]){
    // // while(!L.empty()){
    //     int i = L.front();
    //     L.erase(L.begin());

    //     for(tie(e, e_end) = out_edges(i, g); e != e_end; e++){
    //         int j = target(*e, g);
    //         if(!marked[j] && flow[*e] < capacity[*e]){
    //             alpha[j] = min(alpha[i], capacity[*e]-flow[*e]);
    //             cout << *e << " " << flow[*e] << "\n";
    //             flow[*e] = alpha[j]; // update the flow value for the forward edge
    //             cout << flow[*e] << "\n";
    //             // create the reverse edge
    //             edge_t rev_e = get(edge_reverse, g, *e);
    //             flow[rev_e] = alpha[j]; 
    //             marked[j] = true;
    //             L.push_back(j);
    //         }
    //     }

    //     int min_alpha = INT_MAX;
    //     for(int iter = 0; iter < num_vertices(g); iter++){
    //         if(alpha[iter] != 0){
    //             min_alpha = min(min_alpha, alpha[iter]);
    //         }
    //     }
    //     // for(tie(e, e_end) = in_edges(i, g); e != e_end; e++){
    //     //     int j = target(*e, g);
    //     //     if(!marked[j] && flow[*e] > 0){
    //     //         alpha[j] = min(alpha[i], flow[*e]);
    //     //         marked[j] num_vertices= true;
    //     //         L.push_back(j);
    //     //     }
    //     // }
    // }

    // if(!marked[t]){
    //     cout << "pas de chaine augmentante\n";
    // } else {
    //     if(marked[3]){
    //         cout << "chaine augmentante trouve passant par 3 \n";
    //         cout << alpha[3] << "\n";
    //     }
    //     if(marked[5]){
    //         cout << "chaine augmentante trouve passant par 5 \n";
    //         cout << alpha[5] << "\n";
    //     }        
    // } 

    vector<int> alpha(num_vertices(g), 0);
    vector<bool> marked(num_vertices(g), false);
    vector<int> parent(num_vertices(g), -1); // initialize parent vector with -1
    vector<int> min_flow(num_vertices(g), INT_MAX); // initialize parent vector with -1
    vector<int> L;
    graph_traits<Graph>::out_edge_iterator e, e_end;
    property_map<Graph, edge_capacity_t>::type capacity = get(edge_capacity, g);
    property_map<Graph, edge_residual_capacity_t>::type flow = get(edge_residual_capacity, g);

    alpha[s] = INT_MAX;
    alpha[t] = INT_MAX;
    marked[s] = true;
    L.push_back(s);

    while(!L.empty() && !marked[t]){
        int i = L.front();
        L.erase(L.begin());

        for(tie(e, e_end) = out_edges(i, g); e != e_end; e++){
            int j = target(*e, g);
            if(!marked[j] && flow[*e] < capacity[*e]){
                alpha[j] = min(alpha[i], capacity[*e]-flow[*e]);
                flow[*e] = alpha[j]; // update the flow value for the forward edge
                edge_t rev_e = get(edge_reverse, g, *e);
                flow[rev_e] = alpha[j]; // create the reverse edge
                marked[j] = true;
                parent[j] = i; // set the parent of j to i
                L.push_back(j);

                min_flow[j] = min(min_flow[j], flow[*e]);
            }
        }
    }

    // Now we can trace the augmenting path that passes through node 3 by following the parent vector
    vector<int> augmenting_path;
    int current_node = 8;
    while(parent[current_node] != -1){ // trace the path until we reach the source node (whose parent is -1)
        augmenting_path.push_back(current_node);
        current_node = parent[current_node];
    }
    augmenting_path.push_back(current_node); // add the source node to the path

    // Print the augmenting path
    cout << "Augmenting path that passes through node 3: ";
    for(int i=augmenting_path.size()-1; i>=0; i--){
        cout << augmenting_path[i] << " " << min_flow[i] << "\n";
    }
    cout << endl;

}


int main() {
    Graph g;
    Traits::vertex_descriptor s, t;
    const vector<string> names= {"0", "1", "2","3","4","5","6","7","8"};

    property_map < Graph, edge_capacity_t >::type capacity = get(edge_capacity, g);
    property_map < Graph, edge_reverse_t >::type rev = get(edge_reverse, g);
    property_map < Graph, edge_residual_capacity_t >::type residual_capacity = get(edge_residual_capacity, g);

    read_dimacs_max_flow(g, capacity, rev, s, t);

    // int max_flow = edmonds_karp_max_flow(g, s, t);

    marquer(g, s, t);
    print_graph(g);    
    std::string filenameRes = "res.dot";
    std::ofstream outRes(filenameRes.c_str());

    write_graphviz(outRes, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng res.dot > res.png");

    return 0;
}