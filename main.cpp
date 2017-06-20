#include <iostream>
#include "graph.cpp"
#include "CPersistence.h"

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
    typedef CBranch<Self> Branch;
    typedef CPersistence<Self> Persistence;
};

int main(int argc, char** argv) {
    typedef typename traits::File File;
    string user = "jhoel";
    File file = File("test.txt");
    CGraph<traits>* g = new CGraph<traits>("test.txt", user);
    g->insert(file);
    g->insert(file);
    g->printPersistence();
    /*
    g->insert(file);
    g->insert(file);

    g->createBranch("branch1");
    g->checkout("branch1");
    g->insert(file);
    g->insert(file);

    g->checkout("master");
    g->insert(file);
    g->printGraph();
    //g->findPath("textbranch14");
    /*
    g->createBranch("branch2");
    g->checkout("branch2");
    g->insert(file);

    //

    g->checkout("master");
    g->insert(file);
    g->insert(file);



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
    //g->remove("textmaster3");

    return 0;
}

/* example of use method find
 * traits::HNode* nod = new traits::HNode();
    cout << g->find("textmaster1",nod) << endl;
    traits::GNode* n = nod->node;
    CNode<traits>* nn = nod->node;
*/