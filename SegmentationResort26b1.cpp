// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "SegmentationResort26b1.h"
#include "Guests_Tree.h"
#include "Rooms_Tree.h"
#include "DiningRoom.h"

SegmentationResort::SegmentationResort() : dining_room(new DiningRoom()), guests(new
                                               Guests_Tree()), rooms(new Rooms_Tree()) {
}

SegmentationResort::~SegmentationResort() {
    delete this->dining_room;
    delete this->guests;
    delete this->rooms;
}

StatusType SegmentationResort::checkIn(int geustId, int roomNum) {
    if (geustId <= 0 || roomNum <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (guests->contains(geustId)) {
        return StatusType::FAILURE;
    }
    if (rooms->contains(roomNum)) {
        return StatusType::FAILURE;
    }
    try {
        rooms->insert(roomNum, geustId);
    } catch (std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    try {
        guests->insert(geustId, roomNum);
    } catch (std::exception &e) {
        rooms->remove(roomNum);
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType SegmentationResort::checkOut(int geustId) {
    if (geustId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (!guests->contains(geustId) || guests->guestsTree.find(geustId)->value.diningTable
        != nullptr) {
        return StatusType::FAILURE;
    }
    try {
        guests->remove(geustId);
        rooms->remove(geustId);
    } catch (const std::exception &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType SegmentationResort::addTable(int tableId, int capacity) {
    return this->dining_room->addTable(tableId, capacity);
}

StatusType SegmentationResort::removeTable(int tableId) {
    return this->dining_room->removeTable(tableId);
}

StatusType SegmentationResort::enterDiningRoom(int guestId, int tableId) {
    return this->dining_room->enterDiningRoom(guestId, tableId, guests);
}


StatusType SegmentationResort::leaveDiningRoom(int guestId, int tableId) {
    return this->dining_room->leaveDiningRoom(guestId, tableId);
}

StatusType SegmentationResort::reheatFood() {
    return this->dining_room->reheatFood();
}

StatusType SegmentationResort::joinTables(int tableId1, int tableId2) {
    return this->dining_room->joinTables(tableId1, tableId2);
}

output_t<int> SegmentationResort::joinFriend(int guestId1, int guestId2) {
    return this->guests->joinFriend(guestId1, guestId2, *(this->dining_room));
}

output_t<int> SegmentationResort::cleanNextRoom() {
    return this->rooms->cleanNextRoom();
}
