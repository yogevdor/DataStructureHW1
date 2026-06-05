
#ifndef GUESTS_TREE_H
#define GUESTS_TREE_H
#include "AVLtree.h"
#include "wet1util.h"
#include "DiningRoom.h"

class DiningRoom;


class Guests_Tree {
    friend class :: DiningRoom;
protected:
    struct Guest_Val {
        int roomNum;
        int lastMeal;
        DiningRoom :: Dining_Room_Val* diningRoom = nullptr;
    };
private:
    AVLtree<Guest_Val> tree;


public:
    Guests_Tree() = default;
    ~Guests_Tree() = default;
    Guests_Tree(const Guests_Tree&) = delete;            // חוסם בנאי העתקה
    Guests_Tree& operator=(const Guests_Tree&) = delete; // חוסם אופרטור השמה
    DiningRoom :: Dining_Room_Val* get_diningRoom(int guestId);
    int get_lastMeal(int guestId);
    StatusType checkIn(int guestId, int roomNum);
    StatusType checkOut(int guestId);
    StatusType enterDiningRoom(int guestId, int tableId, DiningRoom& dining_room);
    StatusType leaveDiningRoom(int guestId, int tableId);

};



#endif //GUESTS_TREE_H
