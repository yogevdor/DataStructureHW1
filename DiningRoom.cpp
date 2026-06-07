#include "DiningRoom.h"
#include "Guests_Tree.h"

StatusType DiningRoom::addTable(int tableId, int capacity) {
    if (tableId <= 0 || capacity <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (tablesTree.contains(tableId)) {
        return StatusType::FAILURE;
    }
    auto* val = new Dining_Room_Val();
    val->capacity = capacity;
    val->tableId = tableId;
    try {
        tablesTree.insert(tableId, val);
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
    auto tablePtr = tablesTree.find(tableId);
    if (tablePtr == nullptr) {
        return StatusType::FAILURE;
    }
    if (tablePtr->value->guestsTree.getNumNodes() > 0) {
        return StatusType::FAILURE;
    }
    try {
        tablesTree.remove(tableId);
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::enterDiningRoom(int guestId, int tableId, Guests_Tree &guests) {
    //YAARA
    if (guestId <= 0 || tableId <= 0)
        return StatusType::INVALID_INPUT;

    Guest_Val* current_guest = guests.guestsTree.find(guestId);
    if (current_guest == nullptr) //no such guest
        return StatusType::FAILURE;
    if (current_guest->diningTable != nullptr) //in dining room
        return StatusType::FAILURE;
    if (current_guest->lastMeal == this->getLastMeal()) //was in this meal
        return StatusType::FAILURE;

    Dining_Room_Val** current_tablePtr = this->tablesTree.find(tableId);
    if (current_tablePtr == nullptr) {
        //no such table
        return StatusType::FAILURE;
    }
    Dining_Room_Val* current_table = *current_tablePtr;
    if (current_table->guestsTree.getNumNodes() == current_table->capacity) //table is full
        return StatusType::FAILURE;
    try {
        current_table->guestsTree.insert(guestId, current_guest);
        current_guest->diningTable = current_table;
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

    Dining_Room_Val** tablePtr = this->tablesTree.find(tableId);
    if (tablePtr == nullptr) //no such table
        return StatusType::FAILURE;

    Dining_Room_Val* current_table = *tablePtr;
    Guest_Val** current_guest = current_table->guestsTree.find(guestId);
    if (current_guest == nullptr) //no such guest in table
        return StatusType::FAILURE;

    Guest_Val* actual_guest = *current_guest;
    try {
        current_table->guestsTree.remove(guestId);
        actual_guest->diningTable = nullptr;
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

    Dining_Room_Val** table_1Ptr = this->tablesTree.find(tableId1);
    if (table_1Ptr == nullptr) //no such table
        return StatusType::FAILURE;
    Dining_Room_Val** table_2Ptr = this->tablesTree.find(tableId2);
    if (table_2Ptr == nullptr) //no such table
        return StatusType::FAILURE;

    Dining_Room_Val* table_1 = *table_1Ptr;
    Dining_Room_Val* table_2 = *table_2Ptr;
    int newCapacity = table_1->capacity + table_2->capacity;
    try {
        AVLtree<Guest_Val*>* merged_tables = AVLtree<Guest_Val
            *>::mergeTrees(&(table_1->guestsTree), &(table_2->guestsTree));
        table_1->guestsTree.takeOwnership(*merged_tables); //here we have a problem
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

bool DiningRoom::contains(int tableId) {
    return this->tablesTree.contains(tableId);
}
