//
// Created by jhoelccari on 05/05/17.
//

#ifndef VERSIONCONTROLLER_GRAPH_H
#define VERSIONCONTROLLER_GRAPH_H

#include "nodeAndEdge.h"
#include "tools.h"
#include "hashTable.h"

#include <vector>
using namespace std;

template <class G>
class CNode;

template <class G>
class CEdge;

template <class Tr>
class CGraph
{
public:
    typedef typename Tr::Self self;
    typedef CNode<self> Node;
    typedef CEdge<self> Edge;
    typedef typename Tr::File N;
    typedef typename Tr::String E;
    CGraph(const string filename);
    ~CGraph();

    bool insert(N& x);
    bool removeNode(N);
    bool removeEdge(E,N,N);

    bool createBranch(string nameBranch);
    bool checkout(string nameBranch);

    //E findEdge(N a, N b);
    void printNodes();
    void printEdges();

    /* data */
    int currentId;
    vector<Node*> m_nodes;
    CBranch<self>* currentBranch;
    vector<Edge*> allEdges;
    vector<CBranch<self>> branches;

    CHashTable<CNodeHash<CNode<self>>,DispersionFunction<string>,ListAdaptor<CNodeHash<CNode<self>>>>* hashtable;

};

#endif //VERSIONCONTROLLER_GRAPH_H
