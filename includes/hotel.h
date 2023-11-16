#pragma once
#include "room.h"
#include <map>

class Hotel {
private:
    Room* head;
    Room* tail;
    Room* scenicHead;
    Room* dlxSuiteHead;
    Room* pentHead;
public:
    Hotel();

    ~Hotel();

    void append(int);

    int availableDisplay() const;

    int occupiedDisplay() const;

    int countOccupiedRooms() const;

    int fullDisplay() const;

    int bookCourt() const;

    int bookScenic() const;

    int bookDeluxe() const;

    int bookPent() const;

    std::map<std::string, int> countBookedByType() const;
};