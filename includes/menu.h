#pragma once
#include <string>

class Menu {
public:
    static void beginDay();



private:
    static void processDate(const std::string&);

    static void loadDay(const std::string&);

    static void displayMenu();

    static void bookRoom();

    static void roomsMenu();

    static void displayRev() ;

    static void endDay() ;

    int revenue = 0;
};
