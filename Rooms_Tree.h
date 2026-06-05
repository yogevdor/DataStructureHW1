//
// Created by yaara.p on 05/06/2026.
//

#ifndef ROOMS_TREE_H
#define ROOMS_TREE_H
#include "AVLtree.h"
#include "wet1util.h"


class Rooms_Tree {
private:
    AVLtree<int> tree;
    AVLtree<int>::node* cleaningStaff;
    AVLtree<int>::node* minRoom;


public:
    Rooms_Tree() = default;
    ~Rooms_Tree() = default;
    StatusType insert(int guestId,int roomNum);
    output_t<int> cleanNextRoom();
    StatusType checkOut(int guestId);
};



#endif //ROOMS_TREE_H
