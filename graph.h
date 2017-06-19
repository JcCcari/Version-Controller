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
    typedef typename Tr::Branch Branch;
    typedef typename Tr::Persistence Persistence;

    /* data */
    string user;
    int currentId;
    vector<Node*> m_nodes;
    CBranch<traits>* currentBranch;
    vector<Edge*> allEdges;
    vector<CBranch<traits>> branches;
    Node* currentRoot;

    ///Tenemos que tener un root para guardar los estados del grafo en un tiempo n
    //CHashTable<CNodeHash<CNode<traits>>,DispersionFunction<string>,ListAdaptor<CNodeHash<CNode<traits>>>>* hashtable;
    CHashTable<traits>* hashtable;

    /// PARA PATHCOPY
    /// Almacenaremos el camino de "root" hacia un "Node"
    vector<Node*> path;

    /// PARA PERSISTENCIA
    /// Almaneremos punteros a vectores de nodos en otro vector llamado states
    Persistence states;
    //vector<vector<Node*>* > states;


/******************************************************************************/
/****************************** FUNCTIONS *************************************/
/******************************************************************************/
    CGraph(const string filename, string _user);
    ~CGraph();

    bool insert(N& x);

    /// esta funcion busca un nodo, usando como estructura la tabla hash "CHashTable<traits>* hashtable;"
    /// @Param string finded ->
    /// @Param HNode* node ->(opcional) retorna la direccion de memoria del nodo buscado
    bool find(string finded, HNode* node= nullptr);
    bool remove(string target);
    bool merge(string nodeLabel1, string nodeLabel2);

    bool checkCurrentBranch(Edge* b, Branch* tmp= nullptr);
    bool isNewBranch(string nameBranch);

    bool buildPersistence(string target);

    bool createBranch(string nameBranch);
    bool checkout(string nameBranch);
    bool changeUser(string another);

    Node *getCurrentRoot()  const { return currentRoot; }
    void setCurrentRoot(Node * newRoot){ currentRoot = newRoot; }

    void printGraph();

    bool findNodeInPath(Node* n){
        for(int i=0; i<path.size(); i++){
            if( path[i] == n)
                return true;
        }
        return false;
    }

    /// esta funcion buscara un camino desde la raiz a nodo "target"
    /// por lo que guardara los nodos en medio en el "vector<Node*> path"
    //bool findPath(Node* target, Node* start);
    vector<Node*> findPath(string targ){
        /*
        if (targ =="root" ){
            vector<Node*> empty;
            empty.push_back(getCurrentRoot());
            return empty;
        }
         */
        //Node* start = root;
        ///buscamos el nodo
        HNode* tmp = new HNode();
        find(targ,tmp);
        Node* _target = tmp->getNode();
        vector<Node*> pathAux;
        Node* aux = _target;
        while( aux != getCurrentRoot() and aux != nullptr){
            pathAux.push_back(aux);
            aux = aux->pointingEdge->getFirstNode();
            /*
            Node* tmp2 = aux->pointingEdge->getFirstNode();
            if (tmp2 != nullptr)
                aux = tmp2 ; // guardamos el anterior
             */
        }
        //if (not findNodeInPath( getCurrentRoot() ) ) {
            ///cout << "Agregando root" << endl;
        pathAux.push_back(getCurrentRoot());
        //}
        vector<Node*> pathFinal;
        for(int i=0; i<pathAux.size(); i++)
            pathFinal.push_back(pathAux[pathAux.size()-i-1]);
        return pathFinal;
        //return this->path[path.size()-1]==getCurrentRoot()? true:false;
    }

    const vector<Node *> &getM_nodes() const {
        return m_nodes;
    }

    const vector<Node *> &getPath() const {
        return path;
    }


};

#endif //VERSIONCONTROLLER_GRAPH_H
