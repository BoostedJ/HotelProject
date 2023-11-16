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

int Hotel::availableDisplay() const {
    Room* curr = head;
    int counter = 0;
    int occupied = 0;
    do {
        if (!curr->isOccupied()) {
            roomMessage(curr);
            counter++;
            occupied++;
            if (counter == 2) {
                counter = 0;
                std::cout << std::endl;
            } else {
                std::cout << " | ";
            }
        }
        curr = curr->next;
    } while(curr);
    return occupied;
}

int Hotel::occupiedDisplay() const {
    Room* curr = head;
    int counter = 0;
    int occupied = 0;
    do {
        if (curr->isOccupied()) {
            roomMessage(curr);
            counter++;
            occupied++;
            if (counter == 2) {
                counter = 0;
                std::cout << std::endl;
            } else {
                std::cout << " | ";
            }
        }
        curr = curr->next;
    } while(curr->next);
    return occupied;
}
int Hotel::countOccupiedRooms() const {
    Room* curr = head;
    int occupied = 0;
    while (curr) {
        if (curr->isOccupied()) {
            occupied++;
        }
        curr = curr->next;
    }
    return occupied;
}


int Hotel::fullDisplay() const {
    Room* curr = head;
    int counter = 0;
    int total = 0;
    if (!head) {
        std::cout << std::endl;
        return 0;
    }
    while (curr->next) {
        roomMessage(curr);
        curr = curr->next;
        counter++;
        total++;
        if (counter == 3) {
            counter = 0;
            std::cout << std::endl;
        } else {
            std::cout << " | ";
        }
    }
    roomMessage(curr);
    std::cout << std::endl;
    return total;
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

std::map<std::string, int> Hotel::countBookedByType() const {
    std::map<std::string, int> bookedCount;
    Room* curr = head;
    while (curr) {
        if (curr->isOccupied()) {
            std::string roomType = curr->getType();
            bookedCount[roomType]++;
        }
        curr = curr->next;
    }
    return bookedCount;
}