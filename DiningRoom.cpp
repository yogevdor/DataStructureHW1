#include "DiningRoom.h"
#include "Guests_Tree.h"

DiningRoom::~DiningRoom() {
    clearTables(tablesTree.root);
}

StatusType DiningRoom::addTable(int tableId, int capacity) {
    if (tableId <= 0 || capacity <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (tablesTree.contains(tableId)) {
        return StatusType::FAILURE;
    }
    auto val = new Dining_Room_Val();
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
    Dining_Room_Val* toRemove = tablePtr->value;
    try {
        tablesTree.remove(tableId);
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    delete toRemove;
    return StatusType::SUCCESS;
}

StatusType DiningRoom::enterDiningRoom(int guestId, int tableId, const Guests_Tree* guests) {
    if (guestId <= 0 || tableId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto current_guest = guests->find(guestId);
    if (current_guest == nullptr) //no such guest
        return StatusType::FAILURE;
    if (current_guest->value->diningTable != nullptr) //in dining room
        return StatusType::FAILURE;
    if (current_guest->value->lastMeal == this->getLastMeal()) //was in this meal
        return StatusType::FAILURE;

    auto current_tablePtr = tablesTree.find(tableId);
    if (current_tablePtr == nullptr) {
        //no such table
        return StatusType::FAILURE;
    }
    if (current_tablePtr->value->guestsTree.getNumNodes() == current_tablePtr->value->capacity) {
        //table is full
        return StatusType::FAILURE;
    }
    try {
        current_tablePtr->value->guestsTree.insert(guestId, current_guest->value);
        current_guest->value->diningTable = current_tablePtr->value;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::leaveDiningRoom(int guestId, int tableId) {
    //YAARA
    if (guestId <= 0 || tableId <= 0)
        return StatusType::INVALID_INPUT;

    auto tablePtr = tablesTree.find(tableId);
    if (tablePtr == nullptr) //no such table
        return StatusType::FAILURE;
    if (!tablePtr->value->guestsTree.contains(guestId)) {
        return StatusType::FAILURE;
    }

    auto guestPtr = tablePtr->value->guestsTree.find(guestId)->value;
    try {
        tablePtr->value->guestsTree.remove(guestId);
        guestPtr->diningTable = nullptr;
        guestPtr->lastMeal = this->mealId;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType DiningRoom::reheatFood() {
    //YAARA
    this->mealId++;
    return StatusType::SUCCESS;
}

StatusType DiningRoom::joinTables(int tableId1, int tableId2) {
    //YAARA
    if (tableId1 <= 0 || tableId2 <= 0 || tableId1 == tableId2) {
        return StatusType::INVALID_INPUT;
    }
    auto table_1Ptr = this->tablesTree.find(tableId1);
    if (table_1Ptr == nullptr) {
        //no such table
        return StatusType::FAILURE;
    }
    auto table_2Ptr = this->tablesTree.find(tableId2);
    if (table_2Ptr == nullptr) {
        //no such table
        return StatusType::FAILURE;
    }

    int newCapacity = table_1Ptr->value->capacity + table_2Ptr->value->capacity;
    try {
        AVLtree<Guest_Val*>* merged_tables = AVLtree<Guest_Val*>::mergeTrees
                (&table_1Ptr->value->guestsTree, &table_2Ptr->value->guestsTree);
        updateTablePointer(merged_tables->root, table_1Ptr->value);
        table_1Ptr->value->guestsTree.root = nullptr;
        table_1Ptr->value->guestsTree.num_node = 0;
        table_2Ptr->value->guestsTree.root = nullptr;
        table_2Ptr->value->guestsTree.num_node = 0;
        table_1Ptr->value->guestsTree.takeOwnership(merged_tables);
        delete merged_tables;
        table_1Ptr->value->capacity = newCapacity;
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return removeTable(tableId2);
}

void DiningRoom::updateTablePointer(AVLtree<Guest_Val*>::node* currentGuest,
                                    Dining_Room_Val* newTable) {
    if (currentGuest == nullptr) {
        return;
    }
    updateTablePointer(currentGuest->leftSon, newTable);
    if (currentGuest->value != nullptr) {
        currentGuest->value->diningTable = newTable;
    }
    updateTablePointer(currentGuest->rightSon, newTable);
}

void DiningRoom::clearTables(AVLtree<Dining_Room_Val*>::node* n) {
    if (n == nullptr) return;
    clearTables(n->leftSon);
    clearTables(n->rightSon);
    delete n->value;
}

int DiningRoom::getLastMeal() const {
    //YAARA
    return this->mealId;
}

bool DiningRoom::contains(int tableId) {
    return this->tablesTree.contains(tableId);
}
