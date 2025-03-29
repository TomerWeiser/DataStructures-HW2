//
// Created by Tomer on 1/21/2025.
//

#ifndef HW2_JOCKEY_H
#define HW2_JOCKEY_H


class Jockey{
private:

    int id;
    int team;
    int record;

public:

    Jockey(int id, int teamId);

    int getID() const;

    int getTeam() const;

    int getRecord() const;

    void setRecord(int newRecord);

};


#endif //HW2_JOCKEY_H
