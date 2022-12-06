/*
    Sommets: Thread d'application 
        Code
        Date d'activation au plus tot (ex4)
        Date d'activation au lus tard (ex5)

        Sommets particuliers:
            Debut: Initialise le cycle, sa duree est Nulle, thread virtuelle
                Date d'activation x = 0

            Fin: Termine le cycle, duree nulle, thread virtuelle

    Arcs:
        Relations entre threads de x vers y

    Cout: 
        Duree maximum d'execution du thread y 
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

#include <iostream>


#define ARRAYSIZE(b) (sizeof(b)/sizeof(b[0]))
#define NUMNODES 12


struct VertexProperties{
    size_t id;
    size_t dateTot;
    size_t dateTard;

    VertexProperties() : id(0), dateTot(0), dateTard(0) {}
    VertexProperties(size_t _id, size_t _dateTot, size_t _dateTard): id(_id), dateTot(_dateTot), dateTard(_dateTard) {}
};

typedef boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::directedS,
    VertexProperties,
    boost::property<boost::edge_weight_t, int>
> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;    
typedef std::pair<int, int> E;

class label_writer{
    private:
        int debutNode;
        int finalNode;
    
    public:
        label_writer(int debut, int final) : debutNode(debut), finalNode(final) {}

        template <class VertexorEdge>
        void operator()(std::ostream& out, const VertexorEdge& e) const{
            if(e == debutNode){
                out << "[label=\"Init\"]";
            }
            else if(e == finalNode){
                out << "[label=\"Fin\"]";
            }
            else{
                out << "[label=" << e << "]";
            }
        }
};

class edge_writer{
    private:
        Graph& graph;
    
    public:
        edge_writer(Graph& _graph) : graph(_graph) {}

        template <class VertexorEdge>
        void operator()(std::ostream& out, const VertexorEdge& e) const{
            boost::property_map<Graph, boost::edge_weight_t>::type weight = get(boost::edge_weight, graph);
            out << "[label=\"" << get(weight, edge(boost::source(e, graph), boost::target(e, graph), graph).first) << "\"]";
        }
};

int main(int, char*[]){
    int nNodes = NUMNODES+2;
    E edgeArray[] = {
        E(3, 4),
        E(1, 5),
        E(1, 6),
        E(2, 7),
        E(5, 8), E(6, 8), E(7, 8),
        E(4, 9),
        E(9, 10),
        E(8, 11),
        E(10, 12), E(11, 12)
    };

    int weights[] = {
        0, 4, 8, 1, 1, 6, 3, 5, 3, 1, 2, 2, 5, 0
    };

    int num_edges = ARRAYSIZE(edgeArray);
    int debutNode = 0;
    int finalNode = nNodes-1;

    // Creation du graphe
    Graph g;
    std::vector<std::string> names;
    std::vector<vertex_t> vertices;
    std::vector<std::pair<Graph::edge_descriptor, bool>> edges;

    // Ajout noeuds
    for(int i = 0; i < nNodes; i++){
        names.push_back(std::to_string(i));
        vertices.push_back(boost::add_vertex(VertexProperties(i, 0, 0), g));
    }

    // Ajout arcs
    edges.push_back(boost::add_edge(vertices[debutNode], vertices[1], weights[1], g));
    edges.push_back(boost::add_edge(vertices[debutNode], vertices[2], weights[2], g));
    edges.push_back(boost::add_edge(vertices[debutNode], vertices[3], weights[3], g));
    for(int i = 0; i < num_edges; i++){
        edges.push_back(boost::add_edge(vertices[edgeArray[i].first], vertices[edgeArray[i].second], weights[edgeArray[i].second], g));
    }
    edges.push_back(boost::add_edge(vertices[12], vertices[finalNode], weights[finalNode], g));

    
    // Faire graph graphique
    std::string filenameInit = "init.dot";
    std::ofstream outfig(filenameInit.c_str());    

    boost::write_graphviz(outfig, g, label_writer(debutNode, finalNode), edge_writer(g));
    system("dot -Tpng init.dot > init.png");

    return 0;
}