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
    typedef typename Tr::Self traits;
    typedef CNode<traits> Node;
    typedef CEdge<traits> Edge;
    typedef typename Tr::File N;
    typedef typename Tr::String E;
    typedef typename Tr::HNode HNode;


    CGraph(const string filename, string _user);
    ~CGraph();

    bool insert(N& x);

    /// esta funcion busca un nodo, usando como estructura la tabla hash "CHashTable<traits>* hashtable;"
    /// @Param string finded ->
    /// @Param HNode* node ->(opcional) retorna la direccion de memoria del nodo buscado
    bool find(string finded, HNode* node= nullptr);

    bool remove(string target);

    /// esta funcion buscara un camino desde la raiz a nodo "target"
    /// por lo que guardara los nodos en medio en el "vector<Node*> path"
    bool findPath(Node* target, Node* start);
    bool visitNode(Node* target, Node* start);

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
    Node* root; ///Tenemos que tener un root para guardar los estados del grafo en un tiempo n
    //CHashTable<CNodeHash<CNode<traits>>,DispersionFunction<string>,ListAdaptor<CNodeHash<CNode<traits>>>>* hashtable;
    CHashTable<traits>* hashtable;

    /// PARA PATHCOPY
    /// Almacenaremos el camino de "root" hacia un "Node"
    vector<Node*> path;
};

#endif //VERSIONCONTROLLER_GRAPH_H
