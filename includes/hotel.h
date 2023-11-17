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
    mutable int revenue;
public:
    Hotel();

    ~Hotel();

    void saveToFile(const std::string& filename) const;

    void loadFromFile(const std::string& filename);

    void append(int);

    int availableDisplay() const;

    int occupiedDisplay() const;

    int countOccupiedRooms() const;

    int fullDisplay() const;

    void bookCourt() const;

    void bookScenic() const;

    void bookDeluxe() const;

    void bookPent() const;

    Room* findRoom(int) const;

    void customBook() const;

    int getRev() const;

    [[nodiscard]] std::map<std::string, int> countBookedByType() const;
};