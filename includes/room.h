#pragma once
#include <iostream>

struct Room {
private:
    std::string occupant;
    int roomNumber;
    int price;
    std::string roomType;
    bool occupied;
protected:
    Room* next;
public:
    explicit Room(int);

    std::string getType();

    std::string getOccupant();

    void setOccupant(std::string);

    void book(std::string);

    [[nodiscard]] int getRoomNum() const;

    [[nodiscard]] int getPrice() const;

    [[nodiscard]] bool isOccupied() const;

    void setOccupied(bool);

    friend class Hotel;
};