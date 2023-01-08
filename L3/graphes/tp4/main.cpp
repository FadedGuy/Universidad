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

    Date plus tot: Djistra des Debut a chaque autre noued du graphe
    Date plus
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <iostream>
#include <vector>

#define ARRAYSIZE(b) (sizeof(b)/sizeof(b[0]))
#define NUMNODES 12
#define INITNODE 0
// #define TARGETNODE 11
#define COLORPATH "blue"


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

class vertex_writer{
    private:
        int debutNode;
        int finalNode;
        std::vector<vertex_t> path;
        Graph g;
    public:
        vertex_writer(int debut, int final, Graph _g) : debutNode(debut), finalNode(final), g(_g) {}

        template <class VertexorEdge>
        void operator()(std::ostream& out, const VertexorEdge& e) const{
            // std::cout << g[e].dateTot << " " << g[e].dateTard << "\n";
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

void calculDateTot(int noeudInitial, Graph g, int numNoeuds, std::vector<std::string> names){
    std::vector<int> parent_2(numNoeuds);
    std::vector<int> distance_2(numNoeuds, (std::numeric_limits <int>::max)());
    for(int i = 0; i < numNoeuds; ++i){
        parent_2[i] = i;
    }
    distance_2[noeudInitial] = 0;
    bool r = boost::bellman_ford_shortest_paths(g, numNoeuds, 
                                                boost::weight_map(boost::get(boost::edge_weight, g))
                                                .distance_map(&distance_2[0])
                                                .predecessor_map(&parent_2[0]));
    if(r){
        for(int i = 0; i < numNoeuds; ++i){
            std::cout << names[i] << ": " << distance_2[i] << " " << names[parent_2[i]] << std::endl;
            g[i].dateTot = distance_2[i];
        }
    }
    else{
        std::cout << "cycle negatif" << std::endl;
    }
}

int dateTard(int targetNode, int weights[], Graph g, std::vector<edge_t> e_path, std::vector<std::string> names){
    auto totalWeight = weights[0];
    std::cout << "Plus direct path de " << names[INITNODE] << " a " << names[targetNode];
    for(std::vector<edge_t>::reverse_iterator riter = e_path.rbegin(); riter != e_path.rend(); ++riter){
        vertex_t u_tmp = boost::source(*riter, g);
        vertex_t v_tmp = boost::target(*riter, g);
        edge_t e_tmp = boost::edge(u_tmp, v_tmp, g).first;

        totalWeight += weights[e_tmp.m_target];
    }
    std::cout << ": " << totalWeight << std::endl;
    return totalWeight;
}

void calculDateTard(vertex_t noeudInitial, std::vector<vertex_t> vertices, int weights[], Graph g, int numNoeuds, std::vector<std::string> names){
    // Liste des ascendants du noeuds i
    std::vector<vertex_t> parent(numNoeuds);
    // Liste des distances depuis INITNODE (Init/0)
    std::vector<int> distance(numNoeuds); 

    boost::dijkstra_shortest_paths(g, noeudInitial, boost::weight_map(boost::get(boost::edge_weight, g))
                                         .distance_map(boost::make_iterator_property_map(distance.begin(), boost::get(boost::vertex_index, g)))
                                         .predecessor_map(boost::make_iterator_property_map(parent.begin(), boost::get(boost::vertex_index, g))));

    // dataTard each node calculation
    std::vector<edge_t> e_path;
    std::vector<vertex_t> v_path;

    for(int i = INITNODE; i < numNoeuds; i++){
        v_path.push_back(noeudInitial);

        vertex_t end = vertices[i];
        for(vertex_t u = parent[end]; u != end; end=u, u=parent[end]){
            std::pair<edge_t, bool> edge = boost::edge(u, end, g);
            e_path.push_back(edge.first);
            v_path.push_back(edge.first.m_target);
        }
        int r_weight = dateTard(i, weights, g, e_path, names);
        g[i].dateTard = r_weight;
        e_path.clear();
        v_path.clear();
    }
}

int main(int, char*[]){
    int nNodes = NUMNODES+2;
    E edgeArray[] = {
        E(0, 1), E(0, 2), E(0, 3),
        E(1, 5), E(1, 6), 
        E(2, 7),
        E(3, 4),
        E(4, 9),
        E(5, 8), E(6, 8), E(7, 8),
        E(8, 11),
        E(9, 10),
        E(10, 12), E(11, 12),
        E(12, 13)
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
        if(i == debutNode || i == finalNode){
            vertices.push_back(boost::add_vertex(VertexProperties(i, 0, 0), g));
            names.push_back(i == debutNode ? "Init" : "Fin");
        }else{
            vertices.push_back(boost::add_vertex(VertexProperties(i, 0, 0), g));
            names.push_back(std::to_string(i));
        }
    }

    // Ajout arcs
    for(int i = 0; i < num_edges; i++){
        edges.push_back(boost::add_edge(vertices[edgeArray[i].first], vertices[edgeArray[i].second], weights[edgeArray[i].first], g));
    }

    // Bellman pour calculer date au plus tot
    // chemin optimal entre Debut et noeud T
    std::cout << "Algo de Bellman pour date au plus tot\n";
    calculDateTot(0, g, nNodes, names);

    // Dijkstra pour calculer date au plus tard 
    // chemin optimal entre tous les sommets et Fin
    std::cout << "\nAlgo de Dijkstra pour date au plus tard\n";
    calculDateTard(vertices[0], vertices, weights, g, nNodes, names);


    // Faire graph graphique
    std::string filenameInit = "init.dot";
    std::ofstream outfig(filenameInit.c_str());    

    boost::write_graphviz(outfig, g, vertex_writer(INITNODE, finalNode, g), edge_writer(g));
    system("dot -Tpng init.dot > init.png");

    return 0;
}