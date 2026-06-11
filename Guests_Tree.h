#pragma once
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
    AVLtree<Guest_Val*> guestsTree;

    void clearGuestsMemory(AVLtree<Guest_Val*>::node* current);

public:
    Guests_Tree() = default;

    ~Guests_Tree();

    Guests_Tree(const Guests_Tree &) = delete;

    Guests_Tree &operator=(const Guests_Tree &) = delete;

    void insert(int guestId, int roomNum);

    void remove(int guestId);

    output_t<int> joinFriend(int guestId1, int guestId2, DiningRoom &dining_room);

    bool contains(int guestId) const;

    AVLtree<Guest_Val*>::node* find(int guestId) const;
};
