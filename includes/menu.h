#pragma once

class Menu {
public:
    void beginDay();

private:
    void displayMenu();

    void bookRoom();

    static void displayRooms();

    static void roomsMenu();

    void displayRev() const;

    void getTotal() const;

    int revenue = 0;
};