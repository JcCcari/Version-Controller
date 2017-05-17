//
// Created by jhoelccari on 13/05/17.
//

#ifndef VERSIONCONTROLLER_CFILE_H
#define VERSIONCONTROLLER_CFILE_H
#include <iostream>
#include <fstream>
using namespace std;

struct CFile{
    fstream file;
    string namefile;
    CFile(const string name){
        namefile = name;
        createFile(name);
    }

    void createFile(const string namefile){
        file.open(namefile,std::fstream::in | std::fstream::out | std::fstream::app);
        file<<"hello world!" << endl;
        file.close();
    }

    void merge(string text){
        file.open(namefile,std::fstream::in | std::fstream::out | std::fstream::app);
        file<< text<<endl;
        file.close();
    }


};
#endif //VERSIONCONTROLLER_CFILE_H
