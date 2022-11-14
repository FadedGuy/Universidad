/*
    EdgeWeight error cuando llamo a prim o kruskal, verificar como se declara la propiedad de los edges
    para asegurar que no sea ese el problema. >edge_weight_t<
    P95.
    
*/

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
// #include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

#include <iostream>
#include <fstream>
#include <string>

struct VertexProperties{
    unsigned id;

    VertexProperties() : id(0) {}
    VertexProperties(unsigned _id): id(_id){}
};

struct EdgeProperties{
    unsigned weight;

    EdgeProperties() : weight(0) {}
    EdgeProperties(unsigned _weight) : weight(_weight) {} 
};

typedef boost::adjacency_matrix<
    boost::directedS,
    VertexProperties,
    EdgeProperties
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
    int size = 34;
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;    

    // Creation du graphe
    Graph g(size);
    std::vector<std::string> names;
    for(int i = 0; i < size; i++){
        names.push_back(std::to_string(i+1));
    }

    std::pair<Graph::edge_descriptor, bool> e1 = boost::add_edge(0, 1, EdgeProperties(8), g);
    std::pair<Graph::edge_descriptor, bool> e2 = boost::add_edge(0, 2, EdgeProperties(13), g);
    std::pair<Graph::edge_descriptor, bool> e3 = boost::add_edge(0, 5, EdgeProperties(12), g);
    std::pair<Graph::edge_descriptor, bool> e4 = boost::add_edge(0, 10, EdgeProperties(1), g);

    std::pair<Graph::edge_descriptor, bool> e5 = boost::add_edge(1, 2, EdgeProperties(10), g);
    std::pair<Graph::edge_descriptor, bool> e6 = boost::add_edge(1, 8, EdgeProperties(21), g);
    
    std::pair<Graph::edge_descriptor, bool> e7 = boost::add_edge(2, 3, EdgeProperties(11), g);
    std::pair<Graph::edge_descriptor, bool> e8 = boost::add_edge(2, 6, EdgeProperties(13), g);
    std::pair<Graph::edge_descriptor, bool> e9 = boost::add_edge(2, 30, EdgeProperties(40), g);
    
    std::pair<Graph::edge_descriptor, bool> e10 = boost::add_edge(3, 4, EdgeProperties(4), g);
    std::pair<Graph::edge_descriptor, bool> e11 = boost::add_edge(3, 5, EdgeProperties(2), g);
    std::pair<Graph::edge_descriptor, bool> e12 = boost::add_edge(3, 6, EdgeProperties(22), g);

    std::pair<Graph::edge_descriptor, bool> e13 = boost::add_edge(4, 2, EdgeProperties(4), g);

    std::pair<Graph::edge_descriptor, bool> e14 = boost::add_edge(5, 4, EdgeProperties(5), g);

    std::pair<Graph::edge_descriptor, bool> e15 = boost::add_edge(6, 7, EdgeProperties(2), g);
    std::pair<Graph::edge_descriptor, bool> e16 = boost::add_edge(6, 8, EdgeProperties(8), g);

    std::pair<Graph::edge_descriptor, bool> e17 = boost::add_edge(7, 12, EdgeProperties(1), g);
    
    std::pair<Graph::edge_descriptor, bool> e18 = boost::add_edge(8, 7, EdgeProperties(10), g);
    std::pair<Graph::edge_descriptor, bool> e19 = boost::add_edge(8, 9, EdgeProperties(9), g);

    std::pair<Graph::edge_descriptor, bool> e20 = boost::add_edge(9, 10, EdgeProperties(1), g);
    std::pair<Graph::edge_descriptor, bool> e21 = boost::add_edge(9, 11, EdgeProperties(14), g);
    std::pair<Graph::edge_descriptor, bool> e22 = boost::add_edge(9, 12, EdgeProperties(2), g);

    std::pair<Graph::edge_descriptor, bool> e23 = boost::add_edge(10, 11, EdgeProperties(14), g);
    std::pair<Graph::edge_descriptor, bool> e24 = boost::add_edge(10, 12, EdgeProperties(23), g);

    std::pair<Graph::edge_descriptor, bool> e25 = boost::add_edge(11, 12, EdgeProperties(7), g);

    std::pair<Graph::edge_descriptor, bool> e26 = boost::add_edge(12, 6, EdgeProperties(12), g);
    std::pair<Graph::edge_descriptor, bool> e27 = boost::add_edge(12, 13, EdgeProperties(10), g);

    std::pair<Graph::edge_descriptor, bool> e28 = boost::add_edge(13, 6, EdgeProperties(8), g);
    std::pair<Graph::edge_descriptor, bool> e29 = boost::add_edge(13, 14, EdgeProperties(18), g);
 
    std::pair<Graph::edge_descriptor, bool> e30 = boost::add_edge(14, 15, EdgeProperties(11), g);
    std::pair<Graph::edge_descriptor, bool> e31 = boost::add_edge(14, 16, EdgeProperties(9), g);

    std::pair<Graph::edge_descriptor, bool> e32 = boost::add_edge(15, 21, EdgeProperties(9), g);
    std::pair<Graph::edge_descriptor, bool> e33 = boost::add_edge(15, 29, EdgeProperties(5), g);
    std::pair<Graph::edge_descriptor, bool> e34 = boost::add_edge(15, 30, EdgeProperties(6), g);
    std::pair<Graph::edge_descriptor, bool> e35 = boost::add_edge(15, 31, EdgeProperties(13), g);
    std::pair<Graph::edge_descriptor, bool> e36 = boost::add_edge(15, 32, EdgeProperties(11), g);
    std::pair<Graph::edge_descriptor, bool> e37 = boost::add_edge(15, 33, EdgeProperties(13), g);

    std::pair<Graph::edge_descriptor, bool> e38 = boost::add_edge(16, 17, EdgeProperties(10), g);

    std::pair<Graph::edge_descriptor, bool> e39 = boost::add_edge(17, 18, EdgeProperties(7), g);
    std::pair<Graph::edge_descriptor, bool> e40 = boost::add_edge(17, 22, EdgeProperties(7), g);

    std::pair<Graph::edge_descriptor, bool> e41 = boost::add_edge(18, 19, EdgeProperties(6), g);
    std::pair<Graph::edge_descriptor, bool> e42 = boost::add_edge(18, 23, EdgeProperties(8), g);

    std::pair<Graph::edge_descriptor, bool> e43 = boost::add_edge(19, 20, EdgeProperties(9), g);

    std::pair<Graph::edge_descriptor, bool> e44 = boost::add_edge(20, 24, EdgeProperties(2), g);

    std::pair<Graph::edge_descriptor, bool> e45 = boost::add_edge(21, 19, EdgeProperties(10), g);
    std::pair<Graph::edge_descriptor, bool> e46 = boost::add_edge(21, 32, EdgeProperties(7), g);

    std::pair<Graph::edge_descriptor, bool> e47 = boost::add_edge(22, 23, EdgeProperties(4), g);
    std::pair<Graph::edge_descriptor, bool> e48 = boost::add_edge(22, 25, EdgeProperties(8), g);

    std::pair<Graph::edge_descriptor, bool> e49 = boost::add_edge(23, 24, EdgeProperties(15), g);
    std::pair<Graph::edge_descriptor, bool> e50 = boost::add_edge(23, 25, EdgeProperties(6), g);

    std::pair<Graph::edge_descriptor, bool> e51 = boost::add_edge(24, 26, EdgeProperties(3), g);
    std::pair<Graph::edge_descriptor, bool> e52 = boost::add_edge(24, 27, EdgeProperties(4), g);

    std::pair<Graph::edge_descriptor, bool> e53 = boost::add_edge(25, 28, EdgeProperties(10), g);

    std::pair<Graph::edge_descriptor, bool> e54 = boost::add_edge(26, 27, EdgeProperties(2), g);

    std::pair<Graph::edge_descriptor, bool> e55 = boost::add_edge(27, 28, EdgeProperties(7), g);

    std::pair<Graph::edge_descriptor, bool> e56 = boost::add_edge(29, 30, EdgeProperties(2), g);
    std::pair<Graph::edge_descriptor, bool> e57 = boost::add_edge(29, 31, EdgeProperties(10), g);

    std::pair<Graph::edge_descriptor, bool> e58 = boost::add_edge(30, 33, EdgeProperties(8), g);

    std::pair<Graph::edge_descriptor, bool> e59 = boost::add_edge(31, 32, EdgeProperties(1), g);

    
    // Algo de Kruskal
    // std::vector<edge_t> mst;
    // boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
    // boost::property_map<Graph, boost::edge_weight_t>::type weight = get(boost::edge_weight, g);
    // int total_weight = 0;
    // for(int e = 0; e < mst.size(); ++e){
    //     total_weight += get(weight, mst[e]);
    // }

    // std::cout << "total weight: " << total_weight << "\n";


    // Algo de Prim
    std::vector<vertex_t> parent(boost::num_vertices(g));
    boost::prim_minimum_spanning_tree(g, &parent[0]);



    // print_all(g, names);
    std::string filenameInit = "init.dot";
    std::ofstream outfig(filenameInit.c_str());    

    boost::write_graphviz(outfig, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng init.dot > init.png");


    return 0;
}