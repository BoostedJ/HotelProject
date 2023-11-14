#pragma once

class Menu {
public:
    void beginDay();

private:
    void displayMenu();
    void bookRoom();
    static void displayRooms();
    void displayRev() const;
    void getTotal() const;
    int revenue = 0;
};