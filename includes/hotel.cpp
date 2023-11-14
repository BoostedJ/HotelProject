#include "hotel.h"
#include <iostream>

Hotel::Hotel() : head(nullptr), tail(nullptr),scenicHead(nullptr),
                 dlxSuiteHead(nullptr), pentHead(nullptr) {}
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
        tail = node;
    }
    if (node->getRoomNum() == 201) {scenicHead = node;}
    else if (node->getRoomNum() == 236) {dlxSuiteHead = node;}
    else if (node->getRoomNum() == 301) {pentHead = node;}
}
void Hotel::fullDisplay() const {
    Room* curr = head;
    int counter = 0;
    if (!head) {
        std::cout << std::endl;
        return;
    }
    while (curr->next) {
        std::cout << curr->getType() << " Room: " << curr->getRoomNum() << " occupied by " << curr->getOccupant();

        curr = curr->next;
        counter++;
        if (counter == 3) {
            counter = 0;
            std::cout << std::endl;
        } else {
            std::cout << " | ";
        }
    }
    std::cout << curr->roomType << "Room: " << curr->roomNumber << " occupied by " << curr->occupant << std::endl;
}
std::string bookMenu() {
    std::string name;
    std::cout << "Please enter the name of the occupant: ";
    std::cin >> name;
    return name;
}
void Hotel::bookCourt() {
    Room* curr = head;
    while (curr->next->getRoomNum() != 201 && curr->isOccupied()) {
        curr = curr->next;
    }
    if (!curr->isOccupied()) {
        curr->book(bookMenu());
    }
}
