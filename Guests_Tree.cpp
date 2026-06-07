#include "Guests_Tree.h"
#include "DiningRoom.h"

class Rooms_Tree;

void Guests_Tree::insert(int guestId, int roomNum) {
    Guest_Val newGuest;
    newGuest.roomNum = roomNum;
    newGuest.lastMeal = 0;
    this->guestsTree.insert(guestId, newGuest);
}

void Guests_Tree::remove(int guestId) {
    this->guestsTree.remove(guestId);
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

output_t<int> Guests_Tree::joinFriend(int guestId1, int guestId2, DiningRoom &dining_room) {
    if (guestId1 <= 0 || guestId2 <= 0)
        return StatusType::INVALID_INPUT;
    if (guestId1 == guestId2)
        return StatusType::INVALID_INPUT;
    Guest_Val* guest_in = this->guestsTree.find(guestId2);
    if (guest_in == nullptr) //no such guest
        return StatusType::FAILURE;
    if (guest_in->diningTable == nullptr) //not in dining room
        return StatusType::FAILURE;
    Dining_Room_Val* current_table = guest_in->diningTable;
    if (current_table->guestsTree.getNumNodes() == current_table->capacity) //table is full
        return StatusType::FAILURE;
    Guest_Val* guest_want_in = this->guestsTree.find(guestId1);
    if (guest_want_in == nullptr) //no such guest
        return StatusType::FAILURE;
    if (guest_want_in->lastMeal == dining_room.getLastMeal()) //was in this meal
        return StatusType::FAILURE;
    if (guest_want_in->diningTable != nullptr) //NOW in this meal
        return StatusType::FAILURE;
    try {
        current_table->guestsTree.insert(guestId1, guest_want_in);
        guest_want_in->diningTable = current_table;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return guest_in->diningTable->tableId;
}

bool Guests_Tree::contains(int guestId) const {
    return guestsTree.find(guestId);
}
