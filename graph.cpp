//
// Created by jhoelccari on 05/05/17.
//
#include <queue>
#include "graph.h"
#include "CFile.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;


template <class Tr>
CGraph<Tr>::CGraph(const string filename, string _user){
    this->user = _user;
    currentId = 0;

    CFile* file = new CFile(filename);
    Node* tmp = new Node(currentId,"master",file);
    tmp->setLabel("root");
    m_nodes.push_back(tmp);

    setCurrentRoot(tmp);     ///guardamos la direccion del nodo centinela como root

    CEdge<traits>* edge = new CEdge<traits>("centinela", nullptr,tmp);
    //tmp->m_edges.push_back(edge);
    CBranch<traits>* branch = new CBranch<traits>("master", edge);
    allEdges.push_back(edge);

    CBranch<traits>* master = new CBranch<traits>("master", edge );
    //branches.push_back(*master);
    currentBranch = master;
    //branches.push_back(*currentBranch);
    /// Creamos la tabla hash
    //hashtable = new CHashTable< CNodeHash<CNode<traits>> , DispersionFunction<string> , ListAdaptor<CNodeHash<CNode<traits>>> >(15);
    hashtable = new CHashTable<traits>(15);

    ///> Creamos el primer estado de la Persistencia
    states.insertNewState(getNodes());
}

template <class Tr>
CGraph<Tr>::~CGraph(){}

template <class Tr>
bool CGraph<Tr>::insert(N& x){
    currentId +=1;
    /// creamos Node
    CNode<traits>* tmp = new CNode<traits>(currentId,currentBranch->name,&x);
    //states.getCurrentVersion().push_back(tmp);
    m_nodes.push_back(tmp);

    /// creamos Edge
    Node* nodePrev = currentBranch->getEdge()->m_node[1];
    CEdge<traits>* edge = new CEdge<traits>("cambiarEsto",nodePrev,tmp);
    /// guardamos la arista creada
    nodePrev->m_edges.push_back(edge);
    /// actualizamos "currentBranch"
    currentBranch->updateEdge(edge);
    /// guardamos la arista en el nodo creado
    tmp->setPointingEdge(edge);

    allEdges.push_back(edge);

    //CBranch<traits>* branch = new CBranch<traits>("cambiarEstotambien",edge);
    ///*       almacenamos en la hash      *///
    string id = "text"+currentBranch->name+to_string(currentId);
    CNodeHash<traits>* nodeHash = new CNodeHash<traits>(id,tmp,edge);
    hashtable->Insert(*nodeHash);
    //cout << "Insertando: " << id << endl;
    tmp->setLabel(id);      /// le damos una etiqueta al nodo creado

    /// construimos la persistencia
    string objetivo =currentBranch->getEdge()->getSecondNode()->getLabel();
    buildPersistence(objetivo);
};


/* Ejemplo de una busqueda
 * CNodeHash<traits::GNode>* node= new CNodeHash<traits::GNode>();
 * cout << g->find("textmaster1",*node)<< endl;
 * */
template <class Tr>
bool CGraph<Tr>::find(string finded, HNode* node){
    //cout << "Buscando ... " << finded << endl;
    return hashtable->find(finded,*node);
}

template <class Tr>
bool CGraph<Tr>::remove(string target) {
    HNode* node = new HNode();
    if ( not find(target,node))
        return false; ///El nodo no se encontro
    ///borramos
    CEdge<traits>* edge = node->getEdge();
    CNode<traits>* prev = edge->m_node[0]; /// en este nodo debemos borrar el "edge" que apuntaba a "target"
    CNode<traits>* next = edge->m_node[1]; /// este es el nodo a eliminar
    prev->removeEdge(edge);
    next->destroyNode();
    ///Borrar de la tabla hash
    hashtable->remove(node);
    return true;
}

template <class Tr>
bool CGraph<Tr>::merge(string nodeLabel1, string nodeLabel2) {
    ///> Buscamos los nodos con las etiquetas nodeLabel1, y nodeLabel2
    HNode* hnode1, hnode2;
    Node* node1; Node* node2;// Node* merge;
    if ( not find(nodeLabel1,hnode1) ) return false; /// Si alguno de los 2 no es un nodo, terminamos la funcion
    if ( not find(nodeLabel2,hnode2) ) return false; /// Si alguno de los 2 no es un nodo, terminamos la funcion
    node1 = hnode1->getNode();
    node2 = hnode2->getNode();

    ///> Recuperamos el texto que se encuenta en node1 y node2
    string n1 = node1->getFile()->getData();
    string n2 = node2->getFile()->getData();
    string namefile = node1->getFile()->getNameFile();

    /// Creamos un nuevo archivo
    CFile *m = new CFile(namefile);
    Node* merge = new Node(currentId,currentBranch->getName(), m);
    /// Hacemos un merge con los datos de ambos nodos
    merge->getFile()->merge(n1);
    merge->getFile()->merge(n2);

    ///> Linkeamos el nuevo nodo creado con sus dos padres
    Edge* edge1 = new Edge("dato de arista",node1, merge);
    Edge* edge2 = new Edge("dato de arista",node2, merge);
    node1->saveEdge(edge1);
    node2->saveEdge(edge2);

    ///guardamos el nodo merge
    m_nodes.push_back(merge);
    return true;
}


template <class Tr> /// No recuerdo para que hize esta funcion
bool CGraph<Tr>::checkCurrentBranch(CGraph::Edge *b,Branch* tmp) {
    for (int i = 0; i <branches.size() ; ++i) {
        if(branches[i].getEdge() == b){
            tmp = &branches[i] ;
            return true;
        }
    }
    return false;
}

template <class Tr>
bool CGraph<Tr>::isNewBranch(string nameBranch) {
    for (int i = 0; i <branches.size() ; ++i) {
        if(branches[i].getName() == nameBranch)
            return false;
    }
    return true;
}

template <class Tr>
bool CGraph<Tr>::createBranch(string nameBranch){ /// crea un branch y lo almacena en "branches"
    /// primero guardamos el branch actual
    if( isNewBranch(currentBranch->getName()) )
        branches.push_back(*currentBranch);
    //else cout << "/* ERROR: al crear, branch ya existente*/" << endl;

    /// El nuevo branch apunta a Edge de "currentBranch"
    CBranch<traits>* branch = new CBranch<traits>(nameBranch,currentBranch->getEdge());
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
    return true;
}
/*
template <class Tr>
vector<Node*> CGraph<Tr>::findPath(string _target) {
    //Node* start = root;
    ///buscamos el nodo
    HNode* tmp = new HNode();
    //if ( not find(_target,tmp) ) return ;
    Node* target = tmp->getNode();
    vector<Node*> pathAux;
    Node* aux = target;
    do{
        pathAux.push_back(aux);
        aux = aux->pointingEdge->m_node[0];
    }while(aux != getCurrentRoot());
    if ( not std::find( path.begin(), path.end(), getCurrentRoot() ) )
        path.push_back(getCurrentRoot());
    return pathAux;
    //return this->path[path.size()-1]==getCurrentRoot()? true:false;
}
 */
/*
    path.push_back(start);
    while( path[path.size()-1]->m_edges.size() == 1 ){
        Node* tmp = path[path.size()-1]->m_edges[0]->m_node[1];
        path.push_back(tmp);
        if (tmp == target)
            return true;
    }
    //visitNode();
    */

/*
template <class Tr>
bool CGraph<Tr>::findPath(Node *target) {
    queue<Node*> container;
    container.push(root);
    Node* tmp;
    while( not container.empty() ){
        tmp = container.front();
        container.pop();
        if(target==tmp)
            break;
        for(int i=0; i< tmp->m_edges.size(); i++){
            container.push(tmp->m_edges[i].m_nodes[1]);
        }
    }
    return false;
}
*/

template<class Tr>
bool CGraph<Tr>::buildPersistence(string target) {
    states.insertNewState(getNodes());
    path = findPath(target);
    m_nodes = path;

    return false;
}

template<class Tr>
void CGraph<Tr>::printGraph() {
    cout << "digraph G{ " << endl;
    cout <<     "node [shape=circle];"<< endl;
    for (int i=0; i< m_nodes.size(); i++){
        for (int j=0; j< m_nodes[i]->m_edges.size(); j++){
            cout << m_nodes[i]->getLabel() << " -> " << m_nodes[i]->m_edges[j]->m_node[1]->getLabel() << " [color= red];" << endl;
        }
    }
    cout << "}" << endl;
    //system("dot -Tpng graph.dot -o graph.png");
}

template<class Tr>
void CGraph<Tr>::printPersistence() {
    fstream graph;
    graph.open("graph.dot",fstream::out | fstream::binary);
    if (not graph.is_open()) return; ///no se pudo abrir el archivo, por alguna razon
    graph << "# Printing printPersistence" << endl;
    graph << "digraph G{ " << endl;
    graph <<     "node [shape=circle];"<< endl;
    for (int k =0; k< states.getStatesNumber(); k++) {
        if (k ==0)
            graph << states.getVersion(k)[0]->getLabel() << "0 -> centinela"<<";"<< endl ;
        for (int i = 0; i < states.getVersion(k).size()-1; i++){
                graph << states.getVersion(k)[i]->getLabel() <<k<<" -> " << states.getVersion(k)[i+1]->getLabel() <<k<< ";"<< endl;
        }
    }
    graph << "}" << endl;
    graph.close();

    system("dot -Tpng graph2.dot -o graph2.png");
}



