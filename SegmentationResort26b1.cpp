// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "SegmentationResort26b1.h"

#include "Rooms_Tree.h"


SegmentationResort::SegmentationResort() //DOR
{
    
}

SegmentationResort::~SegmentationResort() //DOR
{
    
}

StatusType SegmentationResort::checkIn(int geustId, int roomNum) //DOR
{
    return StatusType::FAILURE;
}

StatusType SegmentationResort::checkOut(int geustId) //DOR
{
    return StatusType::FAILURE;
}

StatusType SegmentationResort::addTable(int tableId, int capacity) //DOR
{
    return StatusType::FAILURE;
}

StatusType SegmentationResort::removeTable(int tableId) //DOR
{
    return StatusType::FAILURE;
}

StatusType SegmentationResort::enterDiningRoom(int guestId, int tableId)
{
    return this->dining_room->enterDiningRoom(guestId, tableId, *(this->guests));
}

StatusType SegmentationResort::leaveDiningRoom(int guestId, int tableId)
{
    return this->dining_room->leaveDiningRoom(guestId, tableId);
}

StatusType SegmentationResort::reheatFood()
{
    return this->dining_room->reheatFood();
}

StatusType SegmentationResort::joinTables(int tableId1, int tableId2)
{
    return this->dining_room->joinTables(tableId1, tableId2);
}

output_t<int> SegmentationResort::joinFriend(int guestId1, int guestId2)
{
    return this->guests->joinFriend(guestId1, guestId2, *(this->dining_room));
}

output_t<int> SegmentationResort::cleanNextRoom()
{
    return this->rooms->cleanNextRoom();
}