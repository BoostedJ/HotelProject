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

void roomMessage(Room* room) {
    std::cout << room->getType() << " Room: " << room->getRoomNum();
    if (room->isOccupied()) {
        std::cout << " is occupied by " << room->getOccupant();
    } else {
        std::cout << " is vacant";
    }
}

void Hotel::fullDisplay() const {
    Room* curr = head;
    int counter = 0;
    if (!head) {
        std::cout << std::endl;
        return;
    }
    while (curr->next) {
        roomMessage(curr);
        curr = curr->next;
        counter++;
        if (counter == 3) {
            counter = 0;
            std::cout << std::endl;
        } else {
            std::cout << " | ";
        }
    }
    roomMessage(curr);
    std::cout << std::endl;
}

void Hotel::occupiedDisplay() const {
    Room* curr = head;
    int counter = 0;
    do {
        if (curr->isOccupied()) {
            roomMessage(curr);
            counter++;
            if (counter == 2) {
                counter = 0;
                std::cout << std::endl;
            } else {
                std::cout << " | ";
            }
        }
        curr = curr->next;
    } while(curr->next);
}

std::string bookMenu() {
    std::string name;
    std::cout << "Please enter the name of the occupant: ";
    std::cin >> name;
    return name;
}

int Hotel::bookCourt() const {
    Room* curr = head;
    while (curr->next->getRoomNum() != 201 && curr->isOccupied()) {
        curr = curr->next;
    }
    if (!curr->isOccupied()) {
        curr->book(bookMenu());
        return curr->getPrice();
    }
    std::cout << "Unfortunately, all of the Courtyard rooms are occupied!\n";
    return 0;
}

int Hotel::bookScenic() const {
    Room* curr = scenicHead;
    while (curr->next->getRoomNum() != 236 && curr->isOccupied() ) {
        curr = curr->next;
    }
    if (!curr->isOccupied() ) {
        curr->book(bookMenu());
        return curr->getPrice();
    }
    std::cout << "Unfortunately, all of the Scenic rooms are occupied!\n";
    return 0;
}

int Hotel::bookDeluxe() const {
    Room* curr = dlxSuiteHead;
    while (curr->next->getRoomNum() != 301 && curr->isOccupied() ) {
        curr = curr->next;
    }
    if (!curr->isOccupied() ) {
        curr->book(bookMenu());
        return curr->getPrice();
    }
    std::cout << "Unfortunately, all of the Deluxe Suites are occupied!\n";
    return 0;
}

int Hotel::bookPent() const {
    if (!pentHead->isOccupied()) {
        pentHead->book(bookMenu());
        return pentHead->getPrice();
    }
    if (!pentHead->next->isOccupied()) {
        pentHead->next->book(bookMenu());
        return pentHead->next->getPrice();
    }
    std::cout << "Unfortunately, all of the Penthouses are occupied!\n";
    return 0;
}
