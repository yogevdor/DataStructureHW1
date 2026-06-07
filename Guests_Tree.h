#ifndef GUESTS_TREE_H
#define GUESTS_TREE_H
#include "AVLtree.h"
#include "wet1util.h"

struct Dining_Room_Val;
class DiningRoom;

struct Guest_Val {
    int roomNum;
    int lastMeal;
    Dining_Room_Val* diningTable = nullptr;
};

class Guests_Tree {
    friend class SegmentationResort;
    friend class DiningRoom;

private:
    AVLtree<Guest_Val> guestsTree;
    AVLtree<int> roomsTree;

public:
    Guests_Tree() = default;

    ~Guests_Tree() = default;

    Guests_Tree(const Guests_Tree &) = delete; // חוסם בנאי העתקה

    Guests_Tree &operator=(const Guests_Tree &) = delete; // חוסם אופרטור השמה

    void insert(int guestId, int roomNum);

    void remove(int guestId);

    output_t<int> joinFriend(int guestId1, int guestId2, DiningRoom &dining_room);

    bool contains(int guestId) const;

    //StatusType enterDiningRoom(int guestId, int tableId, DiningRoom& dining_room);
};

#endif //GUESTS_TREE_H
