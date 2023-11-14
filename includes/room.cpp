#include "room.h"
#include <utility>

Room::Room(const int num) : roomNumber(num), next(nullptr) {
    if (roomNumber <= 170) {
        roomType = "Courtyard";
        price = 125;
    } else if (roomNumber <= 235) {
        roomType = "Scenic";
        price = 145;
    } else if (roomNumber <= 250) {
        roomType = "Deluxe Suite";
        price = 350;
    } else if (roomNumber == 301 || roomNumber == 302) {
        roomType = "Penthouse";
        price = 1135;
    }
    occupant = "N/A";
    occupied = false;
}
std::string Room::getType() {
    return std::move(roomType);
}
std::string Room::getOccupant() {
    return std::move(occupant);
}
void Room::setOccupant(std::string occName) {
    occupant = std::move(occName);
}
int Room::getRoomNum() const {
    return roomNumber;
}
int Room::getPrice() const {
    return price;
}
bool Room::isOccupied() const {
    return occupied;
}
void Room::book(std::string name) {
    std::cout << "Successfully booked " << name << "into" << roomType <<
        " room " << roomNumber << std::endl;
    occupant = std::move(name);
    occupied = true;
}
