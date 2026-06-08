#include "Rooms_Tree.h"

void Rooms_Tree::insert(int roomNum, int guestId) {
    Rooms_Val currentRoom;
    currentRoom.roomNum = roomNum;
    currentRoom.guestId = guestId;
    currentRoom.next =  find_next(roomNum);
    currentRoom.prev =  find_prev(roomNum);
    this->roomsTree.insert(roomNum, currentRoom);
    Rooms_Val* inserted = &this->roomsTree.find(roomNum)->value;
    if(inserted->prev == nullptr)
        minRoom = inserted;
    else
        inserted->prev->next = inserted;

    if(inserted->next != nullptr)
        inserted->next->prev = inserted;
}

Rooms_Val* Rooms_Tree::find_next(int roomNnum) {
    AVLtree<Rooms_Val> ::node* current = this->roomsTree.root;
    Rooms_Val* next = nullptr;
    while (current != nullptr) {
        if(current->key > roomNnum) {
            next = &(current->value);
            current = current->leftSon;
        }
        else
            current = current->rightSon;
    }
    return next;
}
Rooms_Val* Rooms_Tree::find_prev(int roomNnum) {
    AVLtree<Rooms_Val> ::node* current = this->roomsTree.root;
    Rooms_Val* prev = nullptr;
    while (current != nullptr) {
        if(current->key < roomNnum) {
            prev = &(current->value);
            current = current->rightSon;
        }
        else
            current = current->leftSon;
    }
    return prev;
}

void Rooms_Tree::remove(int roomNum) {
    if (!roomsTree.contains(roomNum)) {
        return;
    }
    if (minRoom != nullptr && minRoom->roomNum == roomNum) {
        minRoom = minRoom->next;
    }
    if (cleaningStaff != nullptr && cleaningStaff->roomNum == roomNum) {
        cleaningStaff = cleaningStaff->prev;
    }
    AVLtree<Rooms_Val> ::node* current = this->roomsTree.find(roomNum);
    if(current->value.prev != nullptr)
        current->value.prev->next = current->value.next;
    if (current->value.next != nullptr)
        current->value.next->prev = current->value.prev;
    this->roomsTree.remove(roomNum);
}

output_t<int> Rooms_Tree::cleanNextRoom() {
    //YAARA
    if (this->roomsTree.num_node == 0)
        return StatusType::FAILURE;
    if(this->cleaningStaff == nullptr || this->cleaningStaff->next == nullptr) {
        this->cleaningStaff = this->minRoom;
    }
    else {
        this->cleaningStaff = this->cleaningStaff->next;
    }
        return this->cleaningStaff->roomNum;
}

bool Rooms_Tree::contains(int roomNum) const {
    return roomsTree.contains(roomNum);
}

AVLtree<Rooms_Val>::node* Rooms_Tree::findMin() const { //not in use
    if (roomsTree.root == nullptr) {
        return nullptr;
    }
    AVLtree<Rooms_Val>::node* current = roomsTree.root;
    while (current != nullptr) {
        current = current->leftSon;
    }
    return current;
}
