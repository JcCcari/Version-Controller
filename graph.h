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
    //typedef typename Tr::Self traits;
    typedef typename Tr::Self traits;
    typedef CNode<traits> Node;
    typedef CEdge<traits> Edge;
    typedef typename Tr::File N;
    typedef typename Tr::String E;
    typedef typename Tr::HNode HNode;


    CGraph(const string filename, string _user);
    ~CGraph();

    bool insert(N& x);
    bool find(string finded, HNode* node= nullptr);

    bool createBranch(string nameBranch);
    bool checkout(string nameBranch);
    bool changeUser(string another);

    /* data */
    string user;
    int currentId;
    vector<Node*> m_nodes;
    CBranch<traits>* currentBranch;
    vector<Edge*> allEdges;
    vector<CBranch<traits>> branches;
    //Node* root; ///Tenemos que tener un root para guardar los estados del grafo en un tiempo n
    //CHashTable<CNodeHash<CNode<traits>>,DispersionFunction<string>,ListAdaptor<CNodeHash<CNode<traits>>>>* hashtable;
    CHashTable<traits>* hashtable;


};

#endif //VERSIONCONTROLLER_GRAPH_H
