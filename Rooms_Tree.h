#ifndef ROOMS_TREE_H
#define ROOMS_TREE_H
#include "AVLtree.h"
#include "wet1util.h"

struct Rooms_Val {
    int roomNum;
    int guestId;
    Rooms_Val* prev = nullptr;
    Rooms_Val* next = nullptr;
};

class Rooms_Tree {
    friend class SegmentationResort;

private:
    AVLtree<Rooms_Val> roomsTree;
    Rooms_Val* cleaningStaff = nullptr;
    Rooms_Val* minRoom = nullptr;

public:
    Rooms_Tree() = default;

    ~Rooms_Tree() = default;

    Rooms_Tree(const Rooms_Tree &) = delete; // חוסם בנאי העתקה

    Rooms_Tree &operator=(const Rooms_Tree &) = delete; // חוסם אופרטור השמה

    void insert(int roomNum, int guestId);

    void remove(int roomNum);

    output_t<int> cleanNextRoom();

    Rooms_Val* find_next(int roomNnum);

    Rooms_Val* find_prev(int roomNnum);

    bool contains(int roomNum) const;

    AVLtree<Rooms_Val>::node* findMin() const;
};

#endif //ROOMS_TREE_H
