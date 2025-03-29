//
// Created by Tomer on 1/21/2025.
//

#include "Jockey.h"

Jockey::Jockey(int id, int teamId) :
        id(id),
        team(teamId),
        record(0){}

int Jockey::getID() const{
    return id;
}

int Jockey::getTeam() const{
    return team;
}

int Jockey::getRecord() const{
    return record;
}

void Jockey::setRecord(int newRecord){
    record = newRecord;
}