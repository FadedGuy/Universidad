#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
// #include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <iostream>
#include <fstream>
#include <string>

struct VertexProperties{
    unsigned id;

    VertexProperties() : id(0) {}
    VertexProperties(unsigned _id): id(_id){}
};

typedef boost::adjacency_matrix<
    boost::directedS,
    VertexProperties,
    boost::property<boost::edge_weight_t, int>
> Graph;

void print_all(Graph graph, std::vector<std::string> names){
    std::cout << "vertex: \n";
    boost::print_vertices(graph, &names[0]);
    std::cout << "\n";
    
    std::cout << "edges: \n";
    boost::print_edges(graph, &names[0]);
    std::cout << "\n";

    std::cout << "graph: \n";
    boost::print_graph(graph, &names[0]);
    std::cout << "\n";
}

int main(int, char*[]){
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;    
    typedef std::pair<int, int> E;
    
    int nodes = 34;
    E edge_array[] = {
        E(0, 1), E(0, 2), E(0, 5), E(0, 10),
        E(1, 2), E(1,8),
        E(2, 3), E(2, 6), E(2, 30),
        E(3, 4), E(3, 5), E(3,6),
        E(4, 2),
        E(5, 3),
        E(6, 7), E(6, 8),
        E(7, 12),
        E(8, 7), E(8, 9),
        E(9, 10), E(9, 11), E(9, 12),
        E(10, 11), E(10, 12),
        E(11, 12),
        E(12, 6), E(12, 13),
        E(13, 6), E(13, 14),
        E(14, 15), E(14, 16),
        E(15, 21), E(15, 29), E(15, 30), E(15, 31), E(15, 32), E(15, 33),
        E(16, 17),
        E(17, 18), E(17, 22),
        E(18, 19), E(19, 23),
        E(19, 20),
        E(20, 24),
        E(21, 19), E(21, 32),
        E(22, 23), E(22, 25),
        E(23, 24), E(23, 25),
        E(24, 26), E(24, 27),
        E(25, 28),
        E(26, 27),
        E(27, 28), 
        E(29, 30), E(29, 31),
        E(30, 33),
        E(31, 32)
    };

    int weights[] = {
        8, 13, 12, 1,
        10, 21,
        11, 13, 40,
        4, 2, 22,
        4,
        5,
        2, 8,
        1, 
        10, 9,
        1, 14, 2,
        14, 23, 
        7,
        12, 10,
        8, 18,
        11, 9,
        9, 5, 6, 13, 11, 13,
        10, 
        7, 7,
        6, 8,
        9,
        2,
        10, 7, 
        4, 8,
        15, 6,
        3, 4,
        10,
        2,
        7,
        2, 10,
        8, 
        1
    };

    int num_edges = sizeof(edge_array)/sizeof(E);

    // Creation du graphe
    Graph g(edge_array, edge_array+num_edges, weights, nodes);
    std::vector<std::string> names;
    for(int i = 0; i < nodes; i++){
        names.push_back(std::to_string(i+1));
    }

    
    // Algo de Kruskal
    boost::property_map<Graph, boost::edge_weight_t>::type weight = get(boost::edge_weight, g);
    std::vector<edge_t> mst;

    boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));

    std::cout << "Print the edges in the MST:\n";
    for(std::vector<edge_t>::iterator ei = mst.begin(); ei != mst.end(); ++ei){
        std::cout << boost::source(*ei, g)+1 << "-->" << boost::target(*ei, g)+1 << " with a weight of: "
                  << weight[*ei] << "\n";
        
    }

    int total_weight = 0;
    for(int e = 0; e < mst.size(); ++e){
        total_weight += get(weight, mst[e]);
    }
    std::cout << "total weight: " << total_weight << "\n";


    // print_all(g, names);
    std::string filenameInit = "init.dot";
    std::ofstream outfig(filenameInit.c_str());    

    boost::write_graphviz(outfig, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng init.dot > init.png");


    return 0;
}