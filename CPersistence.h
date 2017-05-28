//
// Created by jhoelccari on 24/05/17.
//

#ifndef VERSIONCONTROLLER_CPERSISTENCE_H
#define VERSIONCONTROLLER_CPERSISTENCE_H
template <class Tr>
class CPersistence{
    typedef typename Tr::GEdge Edge;
public:
    bool backtrack();
    bool insert(Edge* edge);
    bool remove(Edge* edge);

};

#endif //VERSIONCONTROLLER_CPERSISTENCE_H
