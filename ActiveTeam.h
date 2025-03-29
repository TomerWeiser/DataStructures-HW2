//
// Created by Tomer on 1/21/2025.
//

#ifndef HW2_ACTIVETEAM_H
#define HW2_ACTIVETEAM_H

#include "teamNode.h"

class ActiveTeam {
private:

    int id;
    int record;
    int size;
    shared_ptr<teamNode> root;

public:

    ActiveTeam(int id, shared_ptr<teamNode> node);

    int getID() const;

    int getRecord() const;

    void setRecord(int newRecord);

    int getSize() const;

    void setSize(int newSize);

    shared_ptr<teamNode> getRoot() const;

    void setRoot(shared_ptr<teamNode> newRoot);

};


#endif //HW2_ACTIVETEAM_H
