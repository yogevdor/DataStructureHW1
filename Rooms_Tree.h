#pragma once
#include "AVLtree.h"
#include "wet1util.h"

struct Rooms_list_node;

struct Rooms_Val {
    Rooms_list_node* list_node;
};

struct Rooms_list_node {
    int roomNum;
    int guestId;
    Rooms_list_node* prev = nullptr;
    Rooms_list_node* next = nullptr;
};

class Rooms_Tree {
    friend class SegmentationResort;

private:
    AVLtree<Rooms_Val> roomsTree;
    Rooms_list_node* cleaningStaff = nullptr;
    Rooms_list_node* minRoom = nullptr;

public:
    Rooms_Tree() = default;

    ~Rooms_Tree();

    void clearNodes(AVLtree<Rooms_Val>::node* current);

    Rooms_Tree(const Rooms_Tree &) = delete; // חוסם בנאי העתקה

    Rooms_Tree &operator=(const Rooms_Tree &) = delete; // חוסם אופרטור השמה

    void insert(int roomNum, int guestId);

    void remove(int roomNum);

    output_t<int> cleanNextRoom();

    Rooms_list_node* find_next(int roomNnum);

    Rooms_list_node* find_prev(int roomNnum);

    bool contains(int roomNum) const;
};
