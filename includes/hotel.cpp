#include "hotel.h"
#include <iostream>

Hotel::Hotel() : head(nullptr), tail(nullptr), ctYardHead(nullptr),
                 scenicHead(nullptr), dlxSuiteHead(nullptr), pentHead(nullptr) {}
Hotel::~Hotel() {
    const Room* curr = head;
    while (curr != nullptr) {
        const Room* next = curr->next;
        delete curr;
        curr = next;
    }
}
void Hotel::append(const int num) {
    Room* node = new Room(num);
    if (!head) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
    }
}
void Hotel::fullDisplay() const {
    Room* curr = head;
    if (!head) {
        std::cout << std::endl;
        return;
    }
    while (curr->next) {
        std::cout << curr->getType() << " Room: " << curr->getRoomNum() << " occupied by " << curr->getOccupant();
        curr = curr->next;
    }
    std::cout << curr->roomType << "Room: " << curr->roomNumber << " occupied by " << curr->occupant;
}
