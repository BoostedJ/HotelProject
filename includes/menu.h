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

    void endDay() const;

    int revenue = 0;
};