//
// Created by jhoelccari on 05/05/17.
//

#include "graph.h"
#include "CFile.h"
#include <iostream>
using namespace std;

template <class Tr>
CGraph<Tr>::CGraph(const string filename){
    currentId = 0;

    CFile* file = new CFile(filename);
    Node* tmp = new Node(currentId,"master",file);
    m_nodes.push_back(tmp);
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


template <class Tr>
bool CGraph<Tr>::removeNode(N x)
{
    Node* tmp;
    for(int i=0; i< m_nodes.size(); i++){
        if(m_nodes[i]->m_data == x){
            tmp = m_nodes[i];
            for(int j=0; j<tmp->m_edges.size(); j++)
                removeEdge(tmp->m_edges[i]->m_data, tmp->m_edges[i]->m_node[0]->m_data, tmp->m_edges[i]->m_node[1]->m_data);

            cout << " Node "<< tmp->m_data <<" Deleting ... " << endl;
            m_nodes.erase(m_nodes.begin()+i);

            //break;
        }

    }
    for(int i=0; i<allEdges.size(); i++){
        if(allEdges[i]->m_node[0]->m_data == x or allEdges[i]->m_node[1]->m_data == x){
            cout << i << endl;
            allEdges.erase(allEdges.begin()+i);
        }
    }

    printEdges();
    return 1;
}

template <class Tr>
bool CGraph<Tr>::removeEdge(E x, N a, N b)
{
    Node* Na; Node* Nb;
    for(int i=0; i< m_nodes.size() ;i++){
        if(m_nodes[i]->m_data == a ) Na = m_nodes[i];
        //if(m_nodes[i]->m_data == b ) Nb = m_nodes[i];
    }
    Edge* borrar;
    //if(Na) // poner cond para que exista Na
    for(int i=0; i< Na->m_edges.size() ;i++)
        if(Na->m_edges[i]->m_data==x){
            borrar = Na->m_edges[i];
            Na->m_edges.erase(Na->m_edges.begin()+i);
        }
    Nb = borrar->m_node[1];
    for(int j=0; j< Nb->m_edges.size() ;j++)
        if(Nb->m_edges[j]->m_data==x)
            Nb->m_edges.erase(Nb->m_edges.begin()+j);
    //delete[] borrar->m_node;
    delete borrar;
    printEdges();
    return 1;
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

/*
template <class Tr>
E CGraph<Tr>::findEdge(N a, N b)
{
    for(int x=0; x< allEdges.size();x++){
        //cout << allEdges[x]->m_node[0]->m_data << " - " << allEdges[x]->m_node[1]->m_data << endl;
        if( allEdges[x]->m_node[0]->m_data==a &&  allEdges[x]->m_node[1]->m_data==b){
            //cout << 1 << endl;
            return  allEdges[x]->m_data;
        }
    }
    return 0;
}
*/

template <class Tr>
void CGraph<Tr>::printNodes()
{
    cout << "\n Nodes List: ";
    for(int i=0; i<m_nodes.size(); i++)
        cout << m_nodes[i]->m_data << " - " ;
    cout << endl;
}

template <class Tr>
void CGraph<Tr>::printEdges()
{
    cout << "Edges List - Total ( "<<allEdges.size()<<" )" << endl;
    for(int i=0; i<allEdges.size(); i++){
        cout <<" [ "<<i<<" ] "<< allEdges[i]->m_data << " between "<<
             allEdges[i]->m_node[0]->m_data <<" to "<<allEdges[i]->m_node[1]->m_data<< endl;
    }
    /*
    cout << "\n Edges List: "<< endl;
    for(int i=0; i<m_nodes.size();i++){
        for(int j=0; j<m_nodes[i]->m_edges.size();j++){
            cout << " [ "<<i<<" ] "<< m_nodes[i]->m_edges[j]->m_node[0]->m_data << " to " << m_nodes[i]->m_edges[j]->m_node[1]->m_data
                 <<" with " << m_nodes[i]->m_edges[j]->m_data << " dir " << m_nodes[i]->m_edges[j]->m_dir << endl;
        }
    }
    */

}

