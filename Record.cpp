//
// Created by Tomer on 1/21/2025.
//

#include "Record.h"

Record::Record(int record, int teamId) :
        record(record),
        team(teamId)
        {}

int Record::getTeam() const{
    return team;
}

int Record::getRecord() const{
    return record;
}

void Record::setRecord(int newRecord){
    record = newRecord;
}