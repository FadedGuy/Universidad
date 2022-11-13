#include <iostream>
// Inclusion de la librairie Boost
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/reverse_graph.hpp>

using namespace std;
using namespace boost;
// Dans la structure, on définit les propriété des vertex, c'est à dire des noeux
// Chaque nœud possède 3 caractéristiques :
struct VertexProperties
{
    std::string name; // un nom (A,B,C, etc...)
    unsigned id;      // un identifiant manuel (qui n'est pas assigné automatiquement par la librairie) donc 1,2,3, etc ...
    int date_fin;     // la date de fin demandée
    // un constructeur par défaut si aucune donnée n'est rentrée lors de la création du noeud.
    VertexProperties() : name(""), id(0), date_fin(0) {}
    // La fonction qui permet d'assigner les valeur saisie par l'utilisateur au noeud correspondant.
    VertexProperties(std::string const &n, unsigned i, int j) : name(n), id(i), date_fin(j) {}
};

// typedef qui passe les paramètres nécéssaires à adjacency_list afin d'avoir le graph désiré
typedef boost::adjacency_list<
    boost::vecS,      // OutEdgeList est un des types de conteneurs choisi en interne
    boost::vecS,      // VertexList est de même un type de conteneur choisi en interne
    boost::bidirectionalS, // graphe orienté avec des arcs unidirectionnels
    VertexProperties  // demande de prise en compte de nos noeuds personalisés et non les noeuds par defaut,
>
Graph; // Création du typedef Graph avec les paramètres ci-dessus
// Pour le parcours en profondeur nous aurons besoins d'un DFS_Visitor
// Soit Depth First Search Visitor, sert à definir l'interface de l'utilisateur
// du parcours en profondeur.
//  On crée une classe qu'on nomme custom_dfs_visitor et qui hérite de la classe de BGL
//  par défaut, default_dfs_visitor.
class custom_dfs_visitor : public boost::default_dfs_visitor
{
    public:
        // On créee un constructeur qui va gébérer un vecteur dans lequel sera stocké le résultat de la recherche
        custom_dfs_visitor() : vv(new std::vector<int>()) {}
        // Ici on paramètre la recherche
        template <typename Vertex, typename Graph>
        void finish_vertex(Vertex u, const Graph &g) const // finish_vertex est une fonction de BGL
        // elle signifie que les noeuds sont ajoutÃ© que lorsqu'ils sont des feuilles
        {
            VertexProperties const &vertexProperties = g[u]; // on crée un tableau de noeuds
            // On affiche dans la console le deroulement de la recherche
            std::cout << "Vertex name : " << vertexProperties.name << " " << vertexProperties.date_fin << std::endl;
            // on stock l'id du noeud dans notre vecteur de int
            vv->push_back(g[u].id);
        }
        // fonction servant à restituer le vecteur
        std::vector<int> &GetVector() const { return *vv; }
        // Déclaration du vecteur vv
    private:
        boost::shared_ptr<std::vector<int>> vv;
};
// fonction d’application
int main(int, char *[])
{
    // Création du fichier nécéssaire à la création de l'image
    string filename = "test.dot";
    ofstream fout(filename.c_str());
    // Déclaration de vis de type de la classe custom_dfs_visitor
    custom_dfs_visitor vis;
    // Définiton des types noeuds et arcs
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
    // Création du graphe g
    Graph g;

    // Date fin = x
    vertex_t A = boost::add_vertex(VertexProperties("A", 1, 1), g);
    vertex_t B = boost::add_vertex(VertexProperties("B", 2, 2), g);
    vertex_t C = boost::add_vertex(VertexProperties("C", 3, 3), g);
    vertex_t D = boost::add_vertex(VertexProperties("D", 4, 4), g);
    vertex_t E = boost::add_vertex(VertexProperties("E", 5, 5), g);
    vertex_t F = boost::add_vertex(VertexProperties("F", 6, 6), g);
    vertex_t G = boost::add_vertex(VertexProperties("G", 7, 7), g);
    vertex_t H = boost::add_vertex(VertexProperties("H", 8, 8), g);
    vertex_t I = boost::add_vertex(VertexProperties("I", 9, 9), g);
    vertex_t J = boost::add_vertex(VertexProperties("J", 10, 10), g);
    vertex_t K = boost::add_vertex(VertexProperties("K", 11, 11), g);
    vertex_t L = boost::add_vertex(VertexProperties("L", 12, 12), g);
    vertex_t M = boost::add_vertex(VertexProperties("M", 13, 13), g);
    vertex_t N = boost::add_vertex(VertexProperties("N", 14, 14), g);
    vertex_t O = boost::add_vertex(VertexProperties("O", 15, 15), g);

    // Date fin modif 
    const std::string names[] = {"A\n1", "B\n2", "C\n3", "D\n4", "E\n5", "F\n6", 
                                 "G\n7", "H\n8", "I\n9", "J\n10", "K\n11", "L\n12", "M\n13",
                                 "N\n14", "O\n15"};

    //I |    A - 
    std::pair<Graph::edge_descriptor, bool> e1 = boost::add_edge(A, B, g);
    std::pair<Graph::edge_descriptor, bool> e2 = boost::add_edge(A, D, g);
    std::pair<Graph::edge_descriptor, bool> e3 = boost::add_edge(A, J, g);
    std::pair<Graph::edge_descriptor, bool> e4 = boost::add_edge(A, K, g);
    std::pair<Graph::edge_descriptor, bool> e5 = boost::add_edge(A, O, g);
    std::pair<Graph::edge_descriptor, bool> e6 = boost::add_edge(B, C, g);
    std::pair<Graph::edge_descriptor, bool> e7 = boost::add_edge(B, F, g);
    std::pair<Graph::edge_descriptor, bool> e8 = boost::add_edge(B, I, g);
    std::pair<Graph::edge_descriptor, bool> e9 = boost::add_edge(B, N, g);
    std::pair<Graph::edge_descriptor, bool> e10 = boost::add_edge(C, D, g);
    std::pair<Graph::edge_descriptor, bool> e11 = boost::add_edge(C, G, g);
    std::pair<Graph::edge_descriptor, bool> e12 = boost::add_edge(D, E, g);
    std::pair<Graph::edge_descriptor, bool> e13 = boost::add_edge(D, I, g);
    std::pair<Graph::edge_descriptor, bool> e14 = boost::add_edge(D, O, g);
    std::pair<Graph::edge_descriptor, bool> e15 = boost::add_edge(E, F, g);
    std::pair<Graph::edge_descriptor, bool> e16 = boost::add_edge(E, H, g);
    std::pair<Graph::edge_descriptor, bool> e17 = boost::add_edge(E, L, g);
    std::pair<Graph::edge_descriptor, bool> e18 = boost::add_edge(F, I, g);
    std::pair<Graph::edge_descriptor, bool> e19 = boost::add_edge(F, N, g);
    std::pair<Graph::edge_descriptor, bool> e20 = boost::add_edge(G, F, g);
    std::pair<Graph::edge_descriptor, bool> e21 = boost::add_edge(G, O, g);
    std::pair<Graph::edge_descriptor, bool> e22 = boost::add_edge(H, F, g);
    std::pair<Graph::edge_descriptor, bool> e23 = boost::add_edge(H, G, g);
    std::pair<Graph::edge_descriptor, bool> e24 = boost::add_edge(H, K, g);
    std::pair<Graph::edge_descriptor, bool> e25 = boost::add_edge(I, G, g);
    std::pair<Graph::edge_descriptor, bool> e26 = boost::add_edge(I, H, g);
    std::pair<Graph::edge_descriptor, bool> e27 = boost::add_edge(I, J, g);
    std::pair<Graph::edge_descriptor, bool> e28 = boost::add_edge(J, M, g);
    std::pair<Graph::edge_descriptor, bool> e29 = boost::add_edge(K, J, g);
    std::pair<Graph::edge_descriptor, bool> e30 = boost::add_edge(K, O, g);
    std::pair<Graph::edge_descriptor, bool> e31 = boost::add_edge(L, K, g);
    std::pair<Graph::edge_descriptor, bool> e32 = boost::add_edge(M, L, g);
    std::pair<Graph::edge_descriptor, bool> e33 = boost::add_edge(N, K, g);
    std::pair<Graph::edge_descriptor, bool> e34 = boost::add_edge(N, L, g);
    std::pair<Graph::edge_descriptor, bool> e35 = boost::add_edge(O, J, g);
    std::pair<Graph::edge_descriptor, bool> e36 = boost::add_edge(O, N, g);

    std::cout << "Recherche en profondeur sur le Graphe normale" << endl;
    boost::depth_first_search(g, visitor(vis));

    // auto indexmap = boost::get(boost::vertex_index, g);
    // // Dans colormap on crée des couleurs pour les noeuds à partir de leur index
    // auto colormap = boost::make_vector_property_map<boost::default_color_type>(indexmap);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de D" << endl;
    // // Recherche dans le graphe dual g à partir de D
    // // make_reverse_graphe(g) rend g dual
    // // 3 correspond à l'id du noeuds de départ, ici D (car A = 0 , B = 1 , C = 2 , D = 3 , etc ... )
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 3);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de H" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 7);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de A" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 0);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de B" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 1);

    // Déclaration de tous les noeuds de nom : "A" , d'id : 1 , de date de fin : 12 dans le Graphe g
    // vertex_t A = boost::add_vertex(VertexProperties("A", 1, 12), g);
    // vertex_t B = boost::add_vertex(VertexProperties("B", 2, 11), g);
    // vertex_t C = boost::add_vertex(VertexProperties("C", 3, 8), g);
    // vertex_t D = boost::add_vertex(VertexProperties("D", 4, 16), g);
    // vertex_t E = boost::add_vertex(VertexProperties("E", 5, 10), g);
    // vertex_t F = boost::add_vertex(VertexProperties("F", 6, 6), g);
    // vertex_t G = boost::add_vertex(VertexProperties("G", 7, 7), g);
    // vertex_t H = boost::add_vertex(VertexProperties("H", 8, 15), g);
    // // Création d'un tableau Contenant le nom et la date de fin de chaque nœud : il est nécéssaire à la créaation de l'image
    // const std::string names[] = {"A\n12", "B\n11", "C\n8", "D\n16", "E\n10", "F\n6", "G\n7", "H\n15"};
    // // Déclaration de tous les arcs (ex: nom : e1 qui est dirigé de A vers B dans le Graphe g)
    // std::pair<Graph::edge_descriptor, bool> e1 = boost::add_edge(A, B, g);
    // std::pair<Graph::edge_descriptor, bool> e2 = boost::add_edge(A, E, g);
    // std::pair<Graph::edge_descriptor, bool> e3 = boost::add_edge(B, C, g);
    // std::pair<Graph::edge_descriptor, bool> e4 = boost::add_edge(C, G, g);
    // std::pair<Graph::edge_descriptor, bool> e5 = boost::add_edge(C, F, g);
    // std::pair<Graph::edge_descriptor, bool> e6 = boost::add_edge(G, F, g);
    // std::pair<Graph::edge_descriptor, bool> e7 = boost::add_edge(F, B, g);
    // std::pair<Graph::edge_descriptor, bool> e8 = boost::add_edge(B, E, g);
    // std::pair<Graph::edge_descriptor, bool> e9 = boost::add_edge(E, F, g);
    // std::pair<Graph::edge_descriptor, bool> e10 = boost::add_edge(D, H, g);
    // std::pair<Graph::edge_descriptor, bool> e11 = boost::add_edge(D, G, g);
    // std::pair<Graph::edge_descriptor, bool> e12 = boost::add_edge(H, G, g);
    // std::cout << "Recherche en profondeur sur le Graphe normale" << endl;
    
    // // Algorithme de recherche en profondeur sur le Graphe g avec les paramètre implenté à vis
    // boost::depth_first_search(g, visitor(vis));
    // // on récupére dans indexmap l'index des noeuds de g
    // auto indexmap = boost::get(boost::vertex_index, g);
    // // Dans colormap on crée des couleurs pour les noeuds à partir de leur index
    // auto colormap = boost::make_vector_property_map<boost::default_color_type>(indexmap);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de D" << endl;
    // // Recherche dans le graphe dual g à partir de D
    // // make_reverse_graphe(g) rend g dual
    // // 3 correspond à l'id du noeuds de départ, ici D (car A = 0 , B = 1 , C = 2 , D = 3 , etc ... )
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 3);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de H" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 7);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de A" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 0);
    // std::cout << "Recherche en profondeur sur le Graphe Dual à partir de B" << endl;
    // boost::depth_first_search(make_reverse_graph(g), vis, colormap, 1);
    // fonction permettant la création du png
    write_graphviz(fout, g, make_label_writer(&names[0]));
    system("dot -Tpng test.dot > tp11.png");
    return 0;
}