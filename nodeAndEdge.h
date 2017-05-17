//
// Created by jhoelccari on 05/05/17.
//

#ifndef VERSIONCONTROLLER_NODEANDEDGE_H
#define VERSIONCONTROLLER_NODEANDEDGE_H
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template <class G>
class CNode
{
public:
    typedef typename G::Edge Edge; // typedef typename G::Edge Edge; // tmbien es valido esto porque en la clase grafo, decimos que ambos son sus
    typedef typename G::n N;
    //typedef typename G::e E;
    //typedef typename G::Node Node;
    CNode(int i,string o,N* x){
        id = i;
        m_data = x;
    }
    ~CNode();

    int id;
    string owner;
    N* m_data;
    vector<Edge*> m_edges;

};

template <class G>
CNode<G>::~CNode(){}

template <class G>
class CEdge
{
public:
    typedef typename G::Node Node;
    typedef typename G::e E;

    CEdge(const E x, Node* a, Node* b){
        m_data = x;
        m_node[0] = a ;
        m_node[1] = b ;
    }
    ~CEdge();

    /* data */
    Node* m_node[2];
    E m_data;
};


template <class G>
CEdge<G>::~CEdge()
{
    //delete m_node;
}


#endif //VERSIONCONTROLLER_NODEANDEDGE_H