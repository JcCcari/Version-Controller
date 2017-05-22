//
// Created by jhoelccari on 05/05/17.
//

#ifndef VERSIONCONTROLLER_NODEANDEDGE_H
#define VERSIONCONTROLLER_NODEANDEDGE_H
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template <class Tr>
class CNode
{
public:
    typedef typename Tr::GEdge Edge; // typedef typename G::Edge Edge; // tmbien es valido esto porque en la clase grafo, decimos que ambos son sus
    typedef typename Tr::File N;

    CNode(int i,string o,N* x){
        id = i;
        m_data = x;
    }
    ~CNode(){};

    int getId() const {
        return id;
    }

    const string &getOwner() const {
        return owner;
    }

    N *getM_data() const {
        return m_data;
    }

    int id;
    string owner;
    N* m_data;
    vector<Edge*> m_edges;

};

template <class Tr>
class CEdge
{
public:
    typedef typename Tr::GNode Node;
    typedef typename Tr::String E;

    CEdge(const E x, Node* a, Node* b){
        m_data = x;
        m_node[0] = a ;
        m_node[1] = b ;
    }
    ~CEdge(){};

    /* data */
    Node* m_node[2];
    E m_data;
};


#endif //VERSIONCONTROLLER_NODEANDEDGE_H
