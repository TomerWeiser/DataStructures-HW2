//
// Created by Tomer on 1/21/2025.
//

#ifndef HW2_RECORD_H
#define HW2_RECORD_H


class Record {
private:

    int record;
    int team;

public:

    Record() = default;

    Record(int record, int team);

    int getRecord() const;

    int getTeam() const;

    void setRecord(int newRecord);

};


#endif //HW2_RECORD_H
