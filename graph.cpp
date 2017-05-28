//
// Created by jhoelccari on 05/05/17.
//

#include "graph.h"
#include "CFile.h"
#include <iostream>
using namespace std;

template <class Tr>
CGraph<Tr>::CGraph(const string filename, string _user){
    this->user = _user;
    currentId = 0;

    CFile* file = new CFile(filename);
    Node* tmp = new Node(currentId,"master",file);
    m_nodes.push_back(tmp);

    //root = tmp;     ///guardamos la direccion del nodo centinela como root
    CEdge<traits>* edge = new CEdge<traits>("centinela", nullptr,tmp);
    tmp->m_edges.push_back(edge);
    CBranch<traits>* branch = new CBranch<traits>("master", edge);
    allEdges.push_back(edge);

    CBranch<traits>* master = new CBranch<traits>("master", edge );
    branches.push_back(*master);
    currentBranch = master;

    /// Creamos la tabla hash
    //hashtable = new CHashTable< CNodeHash<CNode<traits>> , DispersionFunction<string> , ListAdaptor<CNodeHash<CNode<traits>>> >(15);
    hashtable = new CHashTable<traits>(15);
}

template <class Tr>
CGraph<Tr>::~CGraph(){}

template <class Tr>
bool CGraph<Tr>::insert(N& x){
    currentId +=1;
    /// creamos Node
    CNode<traits>* tmp = new CNode<traits>(currentId,currentBranch->name,&x);
    m_nodes.push_back(tmp);

    /// creamos Edge
    CEdge<traits>* edge = new CEdge<traits>("cambiarEsto",currentBranch->ptr->m_node[1],tmp);
    /// actualizamos "currentBranch"
    currentBranch->updateEdge(edge);
    /// guardamos la arista creada
    tmp->m_edges.push_back(edge);
    allEdges.push_back(edge);

    CBranch<traits>* branch = new CBranch<traits>("cambiarEstotambien",edge);

    /// almacenamos en la hash

    string id = "text"+currentBranch->name+to_string(currentId);
    CNodeHash<Node>* nodeHash = new CNodeHash<Node>(id,tmp);
    hashtable->Insert(*nodeHash);
};

/* Ejemplo de una busqueda
 * CNodeHash<traits::GNode>* node= new CNodeHash<traits::GNode>();
 * cout << g->find("textmaster1",*node)<< endl;
 * */
template <class Tr>
bool CGraph<Tr>::find(string finded, HNode* node){
    hashtable->find(finded,*node);
    return node != nullptr;
}

template <class Tr>
bool CGraph<Tr>::createBranch(string nameBranch){ /// crea un branch y lo almacena en "branches"
    /// El nuevo branch apunta a Edge de "currentBranch"
    CBranch<traits>* branch = new CBranch<traits>(nameBranch,currentBranch->ptr);
    branches.push_back(* branch);
    return 1;
};

template <class Tr>
bool CGraph<Tr>::checkout(string nameBranch) { /// cambia el valor de "currentBranch" a un branch ya creado
    for(int i=0; i< branches.size(); i++){
        if (nameBranch == branches[i].name) {
            currentBranch = &branches[i];
            return true;
        }
    }
    currentBranch = &branches[0]; /// Si no se encuentra, se asigna al branch master por default
    return false;
}

template <class Tr>
bool CGraph<Tr>::changeUser(string another){
    this->user = another;
}
