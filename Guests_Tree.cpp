//
// Created by yaara.p on 05/06/2026.
//

#include "Guests_Tree.h"


StatusType Guests_Tree::checkIn(int guestId, int roomNum) { //DOR

}
StatusType Guests_Tree::checkOut(int guestId) { //DOR

}
/*StatusType Guests_Tree::enterDiningRoom(int guestId, int tableId, DiningRoom& dining_room) { //YAARA
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
}*/
output_t<int> Guests_Tree::joinFriend(int guestId1, int guestId2, DiningRoom& dining_room) {
    if(guestId1 <= 0 || guestId2 <= 0)
        return StatusType::INVALID_INPUT;
    if(guestId1 == guestId2)
        return StatusType::INVALID_INPUT;
    Guests_Tree::Guest_Val* guest_in = this->tree.find(guestId2);
    if(guest_in == nullptr) //no such guest
        return StatusType::FAILURE;
    if(guest_in->diningRoom == nullptr) //not in dining room
        return StatusType::FAILURE;
    DiningRoom::Dining_Room_Val* current_table = guest_in->diningRoom;
    if(current_table->guestsTree.getNumNodes() == current_table->capacity) //table is full
        return StatusType::FAILURE;
    Guests_Tree::Guest_Val* guest_want_in = this->tree.find(guestId1);
    if(guest_want_in == nullptr) //no such guest
        return StatusType::FAILURE;
    if(guest_want_in->lastMeal == dining_room.getLastMeal()) //was in this meal
        return StatusType::FAILURE;
    if(guest_want_in->diningRoom != nullptr) //NOW in this meal
            return StatusType::FAILURE;
    try {
        current_table->guestsTree.insert(guestId1, guest_want_in);
        guest_want_in->diningRoom = current_table;
        guest_want_in->table_index = guest_in->table_index;
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return guest_in->table_index;
}
