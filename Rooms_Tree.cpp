#include "Rooms_Tree.h"

void Rooms_Tree::insert(int roomNum, int guestId) {
    Rooms_Val currentRoom;
    currentRoom.roomNum = roomNum;
    currentRoom.guestId = guestId;

    this->roomsTree.insert(roomNum, currentRoom);
    if (this->minRoom == nullptr) {
        minRoom = roomsTree.find(roomNum);
    }
    if (this->minRoom->value.roomNum >= roomNum) {
        this->minRoom = roomsTree.find(roomNum);
    }
}

void Rooms_Tree::remove(int roomNum) {
    if (!roomsTree.contains(roomNum)) {
        return;
    }
    if (minRoom != nullptr && minRoom->key == roomNum) {
        minRoom = this->findMin();
    }
    this->roomsTree.remove(roomNum);
    if (this->roomsTree.num_node == 0) {
        minRoom = nullptr;
    }
}

output_t<int> Rooms_Tree::cleanNextRoom() {
    //YAARA
    if (this->roomsTree.num_node == 0)
        return StatusType::FAILURE;
    if (this->cleaningStaff->leftSon != nullptr)
        this->cleaningStaff = this->cleaningStaff->leftSon;
    this->cleaningStaff = this->minRoom;
    return this->cleaningStaff->key;
}

bool Rooms_Tree::contains(int roomNum) const {
    return roomsTree.contains(roomNum);
}

AVLtree<Rooms_Val>::node* Rooms_Tree::findMin() const {
    if (roomsTree.root == nullptr) {
        return nullptr;
    }
    AVLtree<Rooms_Val>::node* current = roomsTree.root;
    while (current != nullptr) {
        current = current->leftSon;
    }
    return current;
}
