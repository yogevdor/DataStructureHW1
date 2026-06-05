//
// Created by yaara.p on 05/06/2026.
//

#include "Rooms_Tree.h"

StatusType Rooms_Tree::insert(int guestId,int roomNum) { //DOR, dont forget to update min

}
output_t<int> Rooms_Tree::cleanNextRoom() { //YAARA
    if(this->tree.num_node == 0)
        return StatusType::FAILURE;
    if(this->cleaningStaff->leftSon != nullptr)
        this->cleaningStaff = this->cleaningStaff->leftSon;
    this->cleaningStaff = this->minRoom;
    return this->cleaningStaff->key;
}
StatusType Rooms_Tree::checkOut(int guestId) { //DOR, dont forget to update min

}