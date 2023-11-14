#pragma once
#include "room.h"

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
    void fullDisplay() const;
    void occupiedDisplay();
    void bookCourt();
};