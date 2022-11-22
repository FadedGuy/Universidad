#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/graph_utility.hpp>

#include <iostream>

struct VertexProperties{
    unsigned id;

    VertexProperties() : id(0) {}
    VertexProperties(unsigned _id): id(_id){}
};

typedef boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::bidirectionalS,
    VertexProperties
> Graph;

class custom_dfs_visitor_end : public boost::default_dfs_visitor{
    private:
        boost::shared_ptr<std::vector<int>> vv;

    public:
        custom_dfs_visitor_end() : vv(new std::vector<int>) {}
        
        template <typename Vertex, typename Graph>
        void finish_vertex(Vertex u, const Graph &g) const {
            VertexProperties const &vProperties = g[u];

            // std::cout << "Fini id: " << vProperties.id << "\n";

            vv->push_back(g[u].id);
        }
        
        std::vector<int> &GetVector() const {return *vv;}
};

class custom_dfs_visitor_found : public boost::default_dfs_visitor{
    private:
        boost::shared_ptr<std::vector<int>> vv;

    public:
        custom_dfs_visitor_found() : vv(new std::vector<int>) {}
        
        template <typename Vertex, typename Graph>
        void discover_vertex(Vertex u, const Graph &g) const {
            VertexProperties const &fProperties = g[u];

            // std::cout << "New id: " << vProperties.id << "\n";

            vv->push_back(g[u].id);
        }
        
        std::vector<int> &GetVector() const {return *vv;}
};

int main(int, char*[]){
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

    custom_dfs_visitor_end vis;
    const std::vector<std::string> names = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
    Graph g;

    std::vector<vertex_t> vertices;
    for(int i = 1; i <= names.size(); i++){
        vertices.push_back(boost::add_vertex(VertexProperties(i), g));
    }

    boost::add_edge(vertices[0], vertices[1], g);
    boost::add_edge(vertices[0], vertices[3], g);
    boost::add_edge(vertices[0], vertices[9], g);
    boost::add_edge(vertices[0], vertices[10], g);
    boost::add_edge(vertices[0], vertices[14], g);

    boost::add_edge(vertices[1], vertices[2], g);
    boost::add_edge(vertices[1], vertices[5], g);
    boost::add_edge(vertices[1], vertices[8], g);

    boost::add_edge(vertices[2], vertices[3], g);
    boost::add_edge(vertices[2], vertices[6], g);

    boost::add_edge(vertices[3], vertices[4], g);    
    boost::add_edge(vertices[3], vertices[8], g);    
    boost::add_edge(vertices[3], vertices[14], g);    

    boost::add_edge(vertices[4], vertices[5], g);    
    boost::add_edge(vertices[4], vertices[7], g);    
    boost::add_edge(vertices[4], vertices[11], g);

    boost::add_edge(vertices[5], vertices[8], g);    
    boost::add_edge(vertices[5], vertices[13], g);

    boost::add_edge(vertices[6], vertices[5], g);    
    boost::add_edge(vertices[6], vertices[14], g);

    boost::add_edge(vertices[7], vertices[5], g);    
    boost::add_edge(vertices[7], vertices[6], g);    
    boost::add_edge(vertices[7], vertices[10], g);

    boost::add_edge(vertices[8], vertices[6], g);    
    boost::add_edge(vertices[8], vertices[7], g);    
    boost::add_edge(vertices[8], vertices[9], g);

    boost::add_edge(vertices[9], vertices[12], g);

    boost::add_edge(vertices[10], vertices[9], g);    
    boost::add_edge(vertices[10], vertices[14], g);

    boost::add_edge(vertices[11], vertices[10], g);   

    boost::add_edge(vertices[12], vertices[11], g);    

    boost::add_edge(vertices[13], vertices[10], g);    
    boost::add_edge(vertices[13], vertices[11], g);

    boost::add_edge(vertices[14], vertices[9], g);    
    boost::add_edge(vertices[14], vertices[13], g);    

    std::cout << "Etape 1: Recherche en profondeur sur le graphe\n";
    boost::depth_first_search(g, boost::visitor(vis));

    std::cout << "Etape 1: Trier liste dans l'ordre decroissant de date de fin\n";
    std::vector<int> rVis = vis.GetVector();
    std::reverse(rVis.begin(), rVis.end());

    std::cout << "Etape 2: Creation du graphe dual\n";
    custom_dfs_visitor_found rVisitor;
    auto indexmap = boost::get(boost::vertex_index, g);
    auto colormap = boost::make_vector_property_map<boost::default_color_type>(indexmap);
    Graph gRes = g;

    std::cout << "Etape 2: Parcours en profondeur partant de la liste\n";
    int sizeVisitor = 0;
    std::vector<std::vector<std::string>> cfc;

    while(rVisitor.GetVector().size() != rVis.size()){
        std::cout << "Etape 2: Recherche a partir de " << names[rVis[sizeVisitor]-1] << "\n";
        boost::depth_first_visit(boost::make_reverse_graph(g), rVis[sizeVisitor]-1, rVisitor, colormap);

        std::vector<int> nodesList = rVisitor.GetVector();
        std::vector<std::string> list;
        for(int i = sizeVisitor; i < nodesList.size(); i++){
            list.push_back(names[nodesList[i]-1]);
        }
        cfc.push_back(list);
        
        sizeVisitor = rVisitor.GetVector().size();
    }

    std::cout << "Composants fortement connexe:\n";
    for(auto composant : cfc){
        for(auto node : composant){
            std::cout << node << " ";
        }
        std::cout << "\n"; 
    }

    std::cout << "Faire graphe\n";
    std::string filenameInit = "init.dot";
    std::ofstream outInit(filenameInit.c_str());
    std::string filenameRes = "res.dot";
    std::ofstream outRes(filenameRes.c_str());

    boost::write_graphviz(outInit, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng init.dot > init.png");

    boost::write_graphviz(outRes, g, boost::make_label_writer(&names[0]));
    system("dot -Tpng init.dot > init.png");

    std::cout << "Fini\n";
    return 0;
}