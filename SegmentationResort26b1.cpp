// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "SegmentationResort26b1.h"
#include "Guests_Tree.h"
#include "Rooms_Tree.h"
#include "DiningRoom.h"

//dor
SegmentationResort::SegmentationResort() {
}

SegmentationResort::~SegmentationResort() {
}

//dor
StatusType SegmentationResort::checkIn(int geustId, int roomNum) {
    return StatusType::FAILURE;
}

//dor
StatusType SegmentationResort::checkOut(int geustId) {
    return StatusType::FAILURE;
}

//dor
StatusType SegmentationResort::addTable(int tableId, int capacity) {
    return StatusType::FAILURE;
}

//dor
StatusType SegmentationResort::removeTable(int tableId) {
    return StatusType::FAILURE;
}

StatusType SegmentationResort::enterDiningRoom(int guestId, int tableId) {
    return this->dining_room->enterDiningRoom(guestId, tableId, *(this->guests));
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
