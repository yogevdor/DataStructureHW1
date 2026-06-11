#ifndef DININGROOM_TREE_H
#define DININGROOM_TREE_H
#include "AVLtree.h"
#include "wet1util.h"
#pragma once
class Guests_Tree;
struct Guest_Val;

struct Dining_Room_Val {
    AVLtree<Guest_Val*> guestsTree;
    int capacity;
    int tableId;
};

class DiningRoom {
    friend class Guests_Tree;

private:
    AVLtree<Dining_Room_Val*> tablesTree;
    int mealId = 1;

    void updateTablePointer(AVLtree<Guest_Val*>::node* currentGuest,
                            Dining_Room_Val* newTable);

    void clearTables(AVLtree<Dining_Room_Val*>::node* n);

public:
    DiningRoom() = default;

    ~DiningRoom();

    DiningRoom(const DiningRoom &) = delete; // חוסם בנאי העתקה

    DiningRoom &operator=(const DiningRoom &) = delete; // חוסם אופרטור השמה

    StatusType addTable(int tableId, int capacity);

    StatusType removeTable(int tableId);

    StatusType enterDiningRoom(int guestId, int tableId, const Guests_Tree* guests);

    StatusType leaveDiningRoom(int guestId, int tableId);

    StatusType reheatFood();

    StatusType joinTables(int tableId1, int tableId2);

    int getLastMeal() const;

    bool contains(int tableId);
};

#endif //DININGROOM_TREE_H
