#include <iostream>
#include <fstream>

#include "graph.cpp"
using namespace std;


struct traits;
struct dataEdge;

int main(int argc, char** argv) {
    CFile file = CFile("test.txt");

    /*
    CGraph<CFile, string>* g = new CGraph<CFile, string>("test.txt");
    g->insert(file);
     */
    //file.merge("foooooo");
    CGraph<CFile, string>* g = new CGraph<CFile, string>("test.txt");
    g->insert(file);
    g->createBranch("branch1");
    g->checkout("branch1");
    g->insert(file);
    return 0;

}



struct traits{
    string node;        /// @Param el archivo
    int edge;           /// @Param sera la diferencia de tiempos de creacion(t2 -t1)
};

struct dataEdge{

};

/*
    g.insertNode("A");
    g.insertNode("B");
    g.insertNode("C");
    g.insertNode("D");
    g.insertEdge(1,"A","A");

    g.insertEdge(1,"A","B");
    g.insertEdge(2,"B","C");
    g.insertEdge(2,"B","D");

    g.insertEdge(3,"C","D");
    g.insertEdge(3,"A","D");

    g.printNodes();
    g.printEdges();
    */