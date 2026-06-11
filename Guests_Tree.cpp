#include "Guests_Tree.h"
#include "DiningRoom.h"

class Rooms_Tree;

void Guests_Tree::clearGuestsMemory(AVLtree<Guest_Val*>::node* current) {
    if (current == nullptr) {
        return;
    }
    clearGuestsMemory(current->leftSon);
    clearGuestsMemory(current->rightSon);
    delete current->value;
}

Guests_Tree::~Guests_Tree() {
    clearGuestsMemory(this->guestsTree.root);
}

void Guests_Tree::insert(int guestId, int roomNum) {
    auto newGuest = new Guest_Val();
    newGuest->roomNum = roomNum;
    newGuest->lastMeal = 0;
    newGuest->diningTable = nullptr;
    try {
        this->guestsTree.insert(guestId, newGuest);
    } catch (const std::exception &e) {
        delete newGuest;
        throw e;
    }
}

void Guests_Tree::remove(int guestId) {
    auto node = this->guestsTree.find(guestId);
    if (node != nullptr) {
        Guest_Val* guest_to_delete = node->value;
        this->guestsTree.remove(guestId);
        delete guest_to_delete;
    }
}

output_t<int> Guests_Tree::joinFriend(int guestId1, int guestId2, DiningRoom &dining_room) {
    if (guestId1 <= 0 || guestId2 <= 0 || guestId1 == guestId2)
        return StatusType::INVALID_INPUT;
    auto guest_in = this->guestsTree.find(guestId2);
    if (guest_in == nullptr) {
        //no such guest
        return StatusType::FAILURE;
    }
    if (guest_in->value->diningTable == nullptr) {
        //not in dining room
        return StatusType::FAILURE;
    }
    auto current_table = guest_in->value->diningTable;
    if (current_table->guestsTree.getNumNodes() == current_table->capacity) {
        //table is full
        return StatusType::FAILURE;
    }
    auto guest_want_in = this->guestsTree.find(guestId1);
    if (guest_want_in == nullptr) {
        //no such guest
        return StatusType::FAILURE;
    }
    if (guest_want_in->value->lastMeal == dining_room.getLastMeal()) {
        //was in this meal
        return StatusType::FAILURE;
    }
    if (guest_want_in->value->diningTable != nullptr) {
        //NOW in this meal
        return StatusType::FAILURE;
    }
    try {
        current_table->guestsTree.insert(guestId1, guest_want_in->value);
        guest_want_in->value->diningTable = current_table;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return guest_in->value->diningTable->tableId;
}

bool Guests_Tree::contains(int guestId) const {
    return guestsTree.find(guestId);
}

AVLtree<Guest_Val*>::node* Guests_Tree::find(int guestId) const {
    return this->guestsTree.find(guestId);
}
