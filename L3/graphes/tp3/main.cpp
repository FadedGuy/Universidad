// Graphe non-oriente avec conexion entre transmetteurs
// Nb min de frequences compatibles = probleme de coloration de graphe
// Algo de welsh powell solution approchee, un nombre k pas trop grand mais n'assure pas qu'il soit min
// Etape 1
// Classer les sommets dans l'ordre decroissant de leur degre
// Attribuer a chacun son numoer d'ordre dans la liste triee
// Etape 2
// Parcourir la liste des sommets dans l'ordre de tri et:
// Attribuer une couleur non encore utilisee au premier sommet non encore colore
// Attribuer cette meme couleur a chaque sommet non encontre colore et non adjacent a un sommet de cette couler
// Etape 3
// S'il reste encore des sommets non colores revenir a 2
// Sinon la coloration est terminee

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

struct VertexProperties{
    char id;

    VertexProperties() : id(0) {}
    VertexProperties(char _id): id(_id){}
};


typedef boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    VertexProperties
> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;    
typedef std::pair<int, int> E;

std::string colorsArray[] = {
    "blue",
    "cyan",
    "gold",
    "gray",
    "green",
    "purple",
    "peru"
};

int getNum(char character){
    // return character - '1';
    return character - 'A';
}

bool compareDegree(std::pair<vertex_t, int> a, std::pair<vertex_t, int> b){
    return a.second > b.second;
}

std::vector<vertex_t> forbidenConnections(std::vector<vertex_t> connections, std::vector<std::pair<vertex_t, int>> vertices, int index, Graph g){
    auto connectionsIter = boost::out_edges(vertices[index].first, g);

    if(std::find(connections.begin(), connections.end(), vertices[index].first) == connections.end()){
        connections.push_back(vertices[index].first); 
    }
    for(auto iter = connectionsIter.first; iter != connectionsIter.second; ++iter){
        if(std::find(connections.begin(), connections.end(), boost::target(*iter, g)) == connections.end()){
            connections.push_back(boost::target(*iter, g));
        }
    }

    return connections;
}

class color_writer{
    private:
        char* name;
        int* color;
    public:
        color_writer(char* _name, int* _color): name(_name), color(_color) {}

        template <class VertexorEdge>
        void operator()(std::ostream& out, const VertexorEdge& e){
            out << "[label=" << *name << "][color=" << colorsArray[*color] << "]";
            name++;
            color++;
        }
};

int main(int, char*[]){
    int nodes = 'T'-'A';
    // int nodes = '7'-'1';
    // E edge_array[]{
    //     E(getNum('1'), getNum('2')),
    //     E(getNum('1'), getNum('3')),

    //     E(getNum('2'), getNum('3')),
    //     E(getNum('2'), getNum('4')),
    //     E(getNum('2'), getNum('7')),

    //     E(getNum('3'), getNum('4')),
    //     E(getNum('3'), getNum('7')),

    //     E(getNum('4'), getNum('5')),
    //     E(getNum('4'), getNum('7')),
        
    //     E(getNum('5'), getNum('7')),
    //     E(getNum('5'), getNum('6')),

    //     E(getNum('6'), getNum('7')),
    // };

    E edge_array[]{
        E(getNum('A'), getNum('D')), 
        E(getNum('A'), getNum('E')),
        E(getNum('A'), getNum('H')),
        E(getNum('A'), getNum('K')),

        E(getNum('B'), getNum('C')),
        E(getNum('B'), getNum('G')),
        E(getNum('B'), getNum('M')),
        E(getNum('B'), getNum('S')),

        E(getNum('C'), getNum('R')),
        E(getNum('C'), getNum('T')),

        E(getNum('D'), getNum('M')),
        E(getNum('D'), getNum('S')),

        E(getNum('E'), getNum('F')),
        E(getNum('E'), getNum('G')),
        E(getNum('E'), getNum('O')),

        E(getNum('F'), getNum('G')),
        E(getNum('F'), getNum('Q')),
        E(getNum('F'), getNum('T')),

        E(getNum('G'), getNum('I')),

        E(getNum('H'), getNum('L')),
        E(getNum('H'), getNum('Q')),

        E(getNum('I'), getNum('K')),
        E(getNum('I'), getNum('S')),

        E(getNum('J'), getNum('N')),
        E(getNum('J'), getNum('O')),
        
        E(getNum('K'), getNum('P')),
        E(getNum('K'), getNum('R')),

        E(getNum('L'), getNum('O')),

        E(getNum('N'), getNum('T')),

        E(getNum('P'), getNum('T')),
    };
    
    int num_edges = sizeof(edge_array)/sizeof(E);
    Graph g;

    std::cout << "Creation du graphe\n";
    std::vector<char> names;
    std::vector<vertex_t> vertices;
    std::vector<std::pair<Graph::edge_descriptor, bool>> edges;
    std::vector<int> colored;
    for(int i = 0; i <= nodes; i++){
        // names.push_back(char('1'+i));
        names.push_back(char('A'+i));
        vertices.push_back(boost::add_vertex(VertexProperties(char('A'+i)), g));
        colored.push_back(0);
    }

    for(int i = 0; i < num_edges; i++){
        edges.push_back(boost::add_edge(vertices[edge_array[i].first], vertices[edge_array[i].second], g));
    }

    std::cout << "Etape 1: Classer les sommets dans l'ordre decroissant\n";
    std::vector<std::pair<vertex_t, int>> degrees;
    for(auto vertix: vertices){
        degrees.push_back({vertix, boost::out_degree(vertix, g)});
    }

    std::cout << "Etape 1: Attribuer a chacun son numero d'ordre\n";
    std::sort(degrees.begin(), degrees.end(), compareDegree);

    int numColors = 1;

    std::cout << "Etape 2: Parcourir la liste dans l'ordre du tri\n";
    for(int i = 0; i < degrees.size(); i++){
        std::cout << "Etape 2: Partant du noeud: " << degrees[i].first << "\n";
        if(colored[degrees[i].first] == 0){
            colored[degrees[i].first] = numColors;

            std::vector<vertex_t> connections;
            connections = forbidenConnections(connections, degrees, i, g);

            for(int j = 0; j < degrees.size(); j++){
                if(i != j && colored[degrees[j].first] == 0 && !(std::find(connections.begin(), connections.end(), degrees[j].first) != connections.end())){
                    colored[degrees[j].first] = numColors;
                    connections = forbidenConnections(connections, degrees, j, g);
                    std::cout << "\tNoued " << degrees[j].first << ", couleur " << numColors << "\n";
                }
            }
            numColors++;
        }
    }

    for(auto colors: colored){
        std::cout << colors << "\t";
    }
    std::cout << "\n";

    std::string filenameInit = "init.dot";
    std::ofstream outInit(filenameInit.c_str());
    boost::write_graphviz(outInit, g, color_writer(&names[0], &colored[0]));
    system("dot -Tpng init.dot > init.png");


    return 0;
}