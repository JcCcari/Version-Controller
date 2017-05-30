#include <iostream>
#include "graph.cpp"
using namespace std;

struct dataEdge{

};

struct traits{
    typedef traits Self;
    typedef CNode<Self> GNode;
    typedef CEdge<Self> GEdge;
    typedef CFile File;    /// Dato de los nodos
    typedef string String;  /// Dato de las aristas //PD cambiar esto
    //int edge;           /// @Param sera la diferencia de tiempos de creacion(t2 -t1)

    ///Para la tabla Hash
    typedef CNodeHash<Self> HNode;
    typedef DispersionFunction<Self> DFunction;
    typedef ListAdaptor<Self> LAdaptor;
};

int main(int argc, char** argv) {
    typedef typename traits::File File;
    string user = "jhoel";
    File file = File("test.txt");
    CGraph<traits>* g = new CGraph<traits>("test.txt", user);
    g->insert(file);
    g->insert(file);
    g->createBranch("branch1");

    /*
    g->insert(file);
    g->insert(file);
    g->insert(file);
    g->checkout("branch1");
    g->insert(file);
    g->createBranch("branch2");
    g->insert(file);
    g->checkout("branch2");
    g->insert(file);
     */
    //g->findPath(n,g->root);
    g->remove("textmaster2");

    return 0;
}

/*
 * traits::HNode* nod = new traits::HNode();
    cout << g->find("textmaster1",nod) << endl;
    traits::GNode* n = nod->node;
    CNode<traits>* nn = nod->node;
*/