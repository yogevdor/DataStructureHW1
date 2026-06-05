cmake_minimum_required(VERSION 3.29)
project(DataStructureHW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DataStructureHW1
    AVLtree.h
    main26b1.cpp
    SegmentationResort26b1.cpp
    SegmentationResort26b1.h
    wet1util.h
        Guests_Tree.h
        Rooms_Tree.h
        Rooms_Tree.cpp
        DiningRoom.h
        DiningRoom.cpp
        Guests_Tree.cpp)
