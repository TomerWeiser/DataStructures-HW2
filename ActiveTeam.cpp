//
// Created by Tomer on 1/21/2025.
//

#include "ActiveTeam.h"

#include <utility>

ActiveTeam::ActiveTeam(int id, shared_ptr<teamNode> node) :
        id(id),
        record(0),
        size(1),
        root(node){}

int ActiveTeam::getID() const{
    return id;
}

int ActiveTeam::getRecord() const{
    return record;
}

void ActiveTeam::setRecord(int newRecord){
    record = newRecord;
}

int ActiveTeam::getSize() const{
    return size;
}

void ActiveTeam::setSize(int newSize){
    size = newSize;
}

shared_ptr<teamNode> ActiveTeam::getRoot() const{
    return root;
}

void ActiveTeam::setRoot(shared_ptr<teamNode> newRoot){
    root = newRoot;
}