//
// Created by jhoelccari on 10/05/17.
//

#ifndef VERSIONCONTROLLER_TOOLS_H
#define VERSIONCONTROLLER_TOOLS_H
#include <iostream>
#include "graph.h"
using namespace std;

template <class Tr>
class CBranch{
public:
    typedef typename Tr::Self self;
    typedef typename Tr::String e;
    string name;
    CEdge<self>* ptr;

    CBranch(){
        name = "master";
        ptr = nullptr;
    }

    CBranch(string n,CEdge<self>* p=nullptr){
        name = n;
        ptr = p;
    }

    bool updateEdge(CEdge<self>* e){
        ptr = e;
    }
};
#endif //VERSIONCONTROLLER_TOOLS_H
