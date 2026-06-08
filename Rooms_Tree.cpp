#include "Rooms_Tree.h"

Rooms_Tree::~Rooms_Tree() {
    clearNodes(roomsTree.root);
}

void Rooms_Tree::clearNodes(AVLtree<Rooms_Val>::node* current) {
    if (current == nullptr) {
        return;
    }
    clearNodes(current->leftSon);
    clearNodes(current->rightSon);
    delete current->value.list_node;
}

void Rooms_Tree::insert(int roomNum, int guestId) {
    Rooms_Val currentRoom;
    currentRoom.list_node = new Rooms_list_node();
    currentRoom.list_node->roomNum = roomNum;
    currentRoom.list_node->guestId = guestId;
    currentRoom.list_node->next =  find_next(roomNum);
    currentRoom.list_node->prev =  find_prev(roomNum);
    this->roomsTree.insert(roomNum, currentRoom);
    Rooms_list_node* inserted = this->roomsTree.find(roomNum)->value.list_node;
    if (minRoom == nullptr || roomNum < minRoom->roomNum) {
        minRoom = inserted;
    }
    if(inserted->prev != nullptr)
        inserted->prev->next = inserted;
    if(inserted->next != nullptr)
        inserted->next->prev = inserted;
}

Rooms_list_node* Rooms_Tree::find_next(int roomNnum) {
    AVLtree<Rooms_Val> ::node* current = this->roomsTree.root;
    Rooms_list_node* next = nullptr;
    while (current != nullptr) {
        if(current->key > roomNnum) {
            next = (current->value.list_node);
            current = current->leftSon;
        }
        else
            current = current->rightSon;
    }
    return next;
}
Rooms_list_node* Rooms_Tree::find_prev(int roomNnum) {
    AVLtree<Rooms_Val> ::node* current = this->roomsTree.root;
    Rooms_list_node* prev = nullptr;
    while (current != nullptr) {
        if(current->key < roomNnum) {
            prev = (current->value.list_node);
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
    Rooms_list_node* list_node_delete = this->roomsTree.find(roomNum)->value.list_node;
    if(list_node_delete->prev != nullptr)
        list_node_delete->prev->next = list_node_delete->next;
    if (list_node_delete->next != nullptr)
        list_node_delete->next->prev = list_node_delete->prev;
    this->roomsTree.remove(roomNum);
    delete(list_node_delete);
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
