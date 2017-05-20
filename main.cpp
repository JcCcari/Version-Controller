#include <iostream>
#include <fstream>

#include "graph.cpp"
using namespace std;

struct dataEdge{

};

struct traits{
    typedef traits Self;
    typedef CNode<Self> GNode;
    typedef CEdge<Self> GEdge;
    typedef CNodeHash<GNode> HNode;
    typedef CFile File;    /// Dato de los nodos
    typedef string String;  /// Dato de las aristas //PD cambiar esto
    //int edge;           /// @Param sera la diferencia de tiempos de creacion(t2 -t1)
};

int main(int argc, char** argv) {
    typedef typename  traits::File File;
    File file = File("test.txt");

    CGraph<traits>* g = new CGraph<traits>("test.txt");
    g->insert(file);

    return 0;
}
