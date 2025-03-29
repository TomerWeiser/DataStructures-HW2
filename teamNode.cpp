//
// Created by Tomer on 1/21/2025.
//

#include "teamNode.h"

#include <utility>

teamNode::teamNode(int id) : id(id), parent(nullptr), activeTeam(id) {}

int teamNode::getID() const{
    return id;
}

shared_ptr<teamNode> teamNode::getParent() const{
    return parent;
}

void teamNode::setParent(shared_ptr<teamNode> newParent){
    parent = newParent;
}

int teamNode::getActiveTeam() const{
    return activeTeam;
}

void teamNode::setActiveTeam(int newTeam){
    activeTeam = newTeam;
}

int teamNode::getRecord() const {
    return 0;
}