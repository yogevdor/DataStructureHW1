//
// Created by yaara.p on 05/06/2026.
//

#ifndef DININGROOM_TREE_H
#define DININGROOM_TREE_H
#include "AVLtree.h"
#include "wet1util.h"
#include "Guests_Tree.h"

class Guests_Tree;

class DiningRoom {
    friend class :: Guests_Tree;
protected:
    struct Dining_Room_Val{
        AVLtree<Guests_Tree::Guest_Val*> guestsTree;
        int capacity;
    };
private:
    AVLtree<Dining_Room_Val> tree;
    int mealCount;

public:
    DiningRoom() = default;
    ~DiningRoom() = default;
    DiningRoom(const DiningRoom&) = delete;            // חוסם בנאי העתקה
    DiningRoom& operator=(const DiningRoom&) = delete; // חוסם אופרטור השמה
    StatusType addTable(int tableId, int capacity);
    StatusType removeTable(int tableId);
    //StatusType enterDiningRoom(int guestId, int tableId, Guests_Tree& guests);
    StatusType leaveDiningRoom(int guestId, int tableId);
    StatusType reheatFood();
    StatusType joinTables(int tableId1, int tableId2);
    output_t<int> joinFriend(int guestId1, int guestId2);
    int getLastMeal() const;

};



#endif //DININGROOM_TREE_H
