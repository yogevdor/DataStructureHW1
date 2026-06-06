#include "DiningRoom.h"

StatusType DiningRoom::addTable(int tableId, int capacity) {
    if (tableId <= 0 || capacity <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (tree.contains(tableId)) {
        return StatusType::FAILURE;
    }
    auto* val = new Dining_Room_Val();
    val->capacity = capacity;
    try {
        tree.insert(tableId, val);
    } catch (const std::exception &e) {
        delete val;
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::removeTable(int tableId) {
    if (tableId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Dining_Room_Val** tablePtr = tree.find(tableId);
    if (tablePtr == nullptr) {
        return StatusType::FAILURE;
    }
    Dining_Room_Val* table = *tablePtr;
    if (table->guestsTree.getNumNodes() > 0) {
        return StatusType::FAILURE;
    }
    try {
        tree.remove(tableId);
        delete table;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::enterDiningRoom(int guestId, int tableId, Guests_Tree &guests) {
    //YAARA
    if (guestId <= 0 || tableId <= 0)
        return StatusType::INVALID_INPUT;
    Guests_Tree::Guest_Val* current_guest = guests.tree.find(guestId);
    if (current_guest == nullptr) //no such guest
        return StatusType::FAILURE;
    if (current_guest->diningRoom != nullptr) //in dining room
        return StatusType::FAILURE;
    if (current_guest->lastMeal == this->getLastMeal()) //was in this meal
        return StatusType::FAILURE;
    DiningRoom::Dining_Room_Val* current_table = this->tree.find(tableId);
    if (current_table == nullptr) //no such table
        return StatusType::FAILURE;
    if (current_table->guestsTree.getNumNodes() == current_table->capacity) //table is full
        return StatusType::FAILURE;
    try {
        current_table->guestsTree.insert(guestId, current_guest);
        current_guest->diningRoom = current_table;
        current_guest->table_index = tableId;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::leaveDiningRoom(int guestId, int tableId) {
    //YAARA
    if (guestId <= 0 || tableId <= 0)
        return StatusType::INVALID_INPUT;
    DiningRoom::Dining_Room_Val* current_table = this->tree.find(tableId);
    if (current_table == nullptr) //no such table
        return StatusType::FAILURE;
    Guests_Tree::Guest_Val** current_guest = current_table->guestsTree.find(guestId);
    if (current_guest == nullptr) //no such guest in table
        return StatusType::FAILURE;
    Guests_Tree::Guest_Val* actual_guest = *current_guest;
    try {
        current_table->guestsTree.remove(guestId);
        actual_guest->diningRoom = nullptr;
        actual_guest->lastMeal = this->mealCount;
        actual_guest->table_index = -1;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::reheatFood() {
    //YAARA
    this->mealCount++;
    return StatusType::SUCCESS;
}

StatusType DiningRoom::joinTables(int tableId1, int tableId2) {
    //YAARA
    if (tableId1 <= 0 || tableId2 <= 0)
        return StatusType::INVALID_INPUT;
    if (tableId1 == tableId2)
        return StatusType::INVALID_INPUT;
    DiningRoom::Dining_Room_Val* table_1 = this->tree.find(tableId1);
    if (table_1 == nullptr) //no such table
        return StatusType::FAILURE;
    DiningRoom::Dining_Room_Val* table_2 = this->tree.find(tableId2);
    if (table_2 == nullptr) //no such table
        return StatusType::FAILURE;
    int newCapacity = table_1->capacity + table_2->capacity;
    try {
        AVLtree<Guests_Tree::Guest_Val*>* merged_tables = AVLtree<Guests_Tree::Guest_Val
            *>::mergeTrees(&(table_1->guestsTree), &(table_2->guestsTree));
        table_1->guestsTree = *merged_tables;
        table_1->capacity = newCapacity;
        delete merged_tables;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return removeTable(tableId2);
}

int DiningRoom::getLastMeal() const {
    //YAARA
    return this->mealCount;
}
