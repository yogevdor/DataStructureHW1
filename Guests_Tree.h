
#ifndef GUESTS_TREE_H
#define GUESTS_TREE_H
#include "AVLtree.h"
#include "wet1util.h"
#include "DiningRoom_Tree.h"

class DiningRoom_Tree;


class Guests_Tree {
    friend class :: DiningRoom_Tree;
protected:
    struct Gueste_Val {
        int roomNum;
        int lastMeal;
        DiningRoom_Tree :: Dining_Room_Val* diningRoom = nullptr;
    };
private:
    AVLtree<Gueste_Val> tree;


public:
    Guests_Tree() = default;
    ~Guests_Tree() = default;
    DiningRoom_Tree :: Dining_Room_Val* get_diningRoom(int guestId);
    int get_lastMeal(int guestId);
    StatusType checkIn(int guestId, int roomNum);
    StatusType checkOut(int guestId);
    StatusType enterDiningRoom(int guestId, int tableId);
    StatusType leaveDiningRoom(int guestId, int tableId);

};



#endif //GUESTS_TREE_H
