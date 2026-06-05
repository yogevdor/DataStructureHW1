//
// Created by yaara.p on 05/06/2026.
//

#include "Guests_Tree.h"

DiningRoom::Dining_Room_Val* Guests_Tree::get_diningRoom(int guestId) { //YAARA

}
int Guests_Tree::get_lastMeal(int guestId) { //YAARA

}
StatusType Guests_Tree::checkIn(int guestId, int roomNum) { //DOR

}
StatusType Guests_Tree::checkOut(int guestId) { //DOR

}
StatusType Guests_Tree::enterDiningRoom(int guestId, int tableId, DiningRoom& dining_room) { //YAARA
    if(guestId <= 0 || tableId <= 0)
        return StatusType::INVALID_INPUT;
    Guests_Tree::Guest_Val* current_guest = this->tree.find(guestId);
    if(current_guest == nullptr) //no such guest
        return StatusType::FAILURE;
    if(current_guest->diningRoom != nullptr) //in dining room
        return StatusType::FAILURE;
    if(current_guest->lastMeal == dining_room.getLastMeal()) //was in this meal
        return StatusType::FAILURE;
    DiningRoom::Dining_Room_Val* current_table = dining_room.tree.find(tableId);
    if(current_table == nullptr) //no such table
        return StatusType::FAILURE;
    if(current_table->guestsTree.getNumNodes() == current_table->capacity) //table is full
        return StatusType::FAILURE;
    try {
        current_table->guestsTree.insert(guestId, current_guest);
        current_guest->diningRoom = current_table;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
StatusType leaveDiningRoom(int guestId, int tableId) { //YAARA

}