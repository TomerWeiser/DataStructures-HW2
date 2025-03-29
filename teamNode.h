//
// Created by Tomer on 1/21/2025.
//

#ifndef HW2_TEAMNODE_H
#define HW2_TEAMNODE_H

#include <memory>

using std::shared_ptr;

class teamNode {
private:

    int id;
    shared_ptr<teamNode> parent;
    int activeTeam;

public:

    teamNode(int id);

    int getID() const;

    shared_ptr<teamNode> getParent() const;

    void setParent(shared_ptr<teamNode> newParent);

    int getActiveTeam() const;

    void setActiveTeam(int newTeam);

    int getRecord() const;

};


#endif //HW2_TEAMNODE_H
