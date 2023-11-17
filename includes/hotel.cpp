#include "hotel.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

Hotel::Hotel() : head(nullptr), tail(nullptr),scenicHead(nullptr),
                 dlxSuiteHead(nullptr), pentHead(nullptr), revenue(0) {}

Hotel::~Hotel() {
    const Room* curr = head;
    while (curr != nullptr) {
        const Room* next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = scenicHead = dlxSuiteHead = pentHead = nullptr;
}

void Hotel::saveToFile(const std::string&filename) const {
    std::ofstream outFile(filename);
    Room* curr = head;
    while (curr) {
        outFile << curr->getRoomNum() << "," << curr->getType() << ","
                << (curr->isOccupied() ? "Occupied" : "Vacant") << "," << curr->getOccupant() << std::endl;
        curr = curr->next;
    }
    outFile << "Revenue," << revenue << std::endl;
    outFile.close();
}

void Hotel::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "File not found: " << filename << std::endl;
        return;
    }
    this->~Hotel();
    for (int i = 101; i <= 302; ++i) {
        append(i);
        if (i == 170) {
            i = 200;
        } else if (i == 250) {
            i = 300;
        }
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() == 4 && tokens[0] != "Revenue") {
            int roomNum = std::stoi(tokens[0]);
            Room* room = findRoom(roomNum);
            if (room) {
                room->setOccupant(tokens[3]);
                room->setOccupied(tokens[2] == "Occupied");
            }
        } else if (tokens.size() == 2 && tokens[0] == "Revenue") {
            revenue = std::stoi(tokens[1]);
        }
    }
    inFile.close();
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
    std::string currType = curr->getType();
    do {
        if (curr->isOccupied()) {
            if (curr->getType() != currType) {
                currType = curr->getType();
                counter = 1;
            }
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
    std::getline(std::cin, name);
    return name;
}

void Hotel::bookCourt() const {
    Room* curr = head;
    while (curr->next->getRoomNum() != 201 && curr->isOccupied()) {
        curr = curr->next;
    }
    if (!curr->isOccupied()) {
        curr->book(bookMenu());
        revenue += curr->getPrice();
    } else {
        std::cout << "Unfortunately, all of the Courtyard rooms are occupied!\n";
    }
}

void Hotel::bookScenic() const {
    Room* curr = scenicHead;
    while (curr->next->getRoomNum() != 236 && curr->isOccupied() ) {
        curr = curr->next;
    }
    if (!curr->isOccupied() ) {
        curr->book(bookMenu());
        revenue += curr->getPrice();
    } else {
        std::cout << "Unfortunately, all of the Scenic rooms are occupied!\n";
    }
}

void Hotel::bookDeluxe() const {
    Room* curr = dlxSuiteHead;
    while (curr->next->getRoomNum() != 301 && curr->isOccupied() ) {
        curr = curr->next;
    }
    if (!curr->isOccupied() ) {
        curr->book(bookMenu());
        revenue += curr->getPrice();
    } else {
        std::cout << "Unfortunately, all of the Deluxe Suites are occupied!\n";
    }
}

void Hotel::bookPent() const {
    if (!pentHead->isOccupied()) {
        pentHead->book(bookMenu());
        revenue += pentHead->getPrice();
    } else if (!pentHead->next->isOccupied()) {
        pentHead->next->book(bookMenu());
        revenue += pentHead->next->getPrice();
    } else {
        std::cout << "Unfortunately, all of the Penthouses are occupied!\n";
    }
}

Room* Hotel::findRoom(const int roomNum) const {
    Room* curr = head;
    while (curr) {
        if (curr->getRoomNum() == roomNum) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void Hotel::customBook() const {
    std::cout << "Please enter the room number you would like to book: ";
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid room number. \n";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (Room* room = findRoom(choice)) {
        if (!room->isOccupied()) {
            room->book(bookMenu());
            revenue += room->getPrice();
        } else {
            std::cout << room->getType() << " " << room->getRoomNum() << " is already occupied!\n";
        }
    }
}

int Hotel::getRev() const {
    return revenue;
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

