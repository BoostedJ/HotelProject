#include "menu.h"
#include "hotel.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
using namespace std;

string inputDate;
Hotel hotel;
bool edit = true;
bool isValidDate(const string& date) {
    if (date.length() != 8) { return false; }
    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '-' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '-' ||
        !isdigit(date[6]) || !isdigit(date[7])) {
        return false;
        }
    return true;
}

void generate() {
    for (int i=101; i<= 302; i++) {
        hotel.append(i);
        if (i == 170) {
            i = 200;
        } else if (i == 250) {
            i = 300;
        }
    }
}

void Menu::processDate(const string& date) {
    const string& filename = date;
    ifstream existingFile(filename);
    if (existingFile) {
        loadDay(filename);
        existingFile.close();
    } else {
        ofstream newFile(filename);
        newFile.close();
        cout << "Creating new file for " << filename << "!\n";
        generate();
    }
}

void Menu::beginDay() {
    cout << "Welcome to the Hotel administrator platform!" << endl;
    while(true) {

        cout << "Please enter the desired date! (mm-dd-yy): ";
        cin >> inputDate;
        cin.clear();
        if (isValidDate(inputDate)) {
            processDate(inputDate);
            if(!edit) {
                break;
            }
            cout << endl;
            displayMenu();
            break;
        } else {
            cout << "Invalid date format. Please try again." << endl;
        }
    }
}

void Menu::loadDay(const string& filename) {
    cout << "1. Load existing hotel data for editing" << endl;
    cout << "2. Load existing hotel data for viewing only" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number between 1-2. \n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
        case 1:
            hotel.loadFromFile(filename);
            break;
        case 2:
            edit = false;
            hotel.loadFromFile(filename);
            hotel.occupiedDisplay();
            cout << "Revenue: $" << hotel.getRev();
            break;
        default:
            cout << "Please enter a number between 1-2. \n";
        break;
    }
}

void Menu::displayMenu() {
    bool cont = true;
    do {
        cout << "=============================" << endl;
        cout << "          " << inputDate << " " << endl;
        cout << "=============================" << endl;
        cout << "1. Reserve a room" << endl;
        cout << "2. Room Display Menu" << endl;
        cout << "3. Display Current Revenue" << endl;
        cout << "4. End of Day Report" << endl;
        cout << "5. Exit without saving" << endl;
        cout << "=============================" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number between 1-5. \n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                roomsMenu();
                break;
            case 3:
                displayRev();
                break;
            case 4:
                endDay();
                cont = false;
                break;
            case 5:
                cout << "Thank you and have a good rest of your day!" << endl;
                cont = false;
                break;
            default:
                cout << "Please enter a number between 1-5.\n";
                choice = -1;
                break;
        }
    } while(cont);
}

void Menu::bookRoom() {
    cout << "Please enter a room type to book: " << endl;
    cout << "1. Courtyard" << endl;
    cout << "2. Scenic" << endl;
    cout << "3. Deluxe Suite" << endl;
    cout << "4. Penthouse" << endl;
    cout << "5. Custom Number" << endl;
    cout << "6. Exit without saving" << endl;
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
        cin.clear();
        cout << "Please enter a number between 1-6. \n";
    }

    switch (choice) {
        case 1:
            hotel.bookCourt();
            break;
        case 2:
            hotel.bookScenic();
            break;
        case 3:
            hotel.bookDeluxe();
            break;
        case 4:
            hotel.bookPent();
            break;
        case 5:
            hotel.customBook();
            break;
        case 6:
            cout << endl << endl;
            break;
        default:
            cout << "Please enter a number between 1-6.\n";
            choice = -1;
            break;
    }
}

void Menu::roomsMenu() {
    cout << "Please enter a which option to display: " << endl;
    cout << "1. Available rooms" << endl;
    cout << "2. Occupied rooms" << endl;
    cout << "3. All rooms" << endl;
    cout << "4. Exit without saving" << endl;
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
        cin.clear();
        cout << "Please enter a number between 1-4. \n";
    }

    switch (choice) {
        int count;
        case 1:
            count = hotel.availableDisplay();
        cout << "There are " << count << " rooms available" << endl;
        break;
        case 2:
            count = hotel.occupiedDisplay();
        cout << "There are " << count << " rooms occupied" << endl;
        break;
        case 3:
            count = hotel.fullDisplay();
        cout << "There are " << count << " rooms in total" << endl;
        break;
        case 4:
            cout << endl << endl;
        break;
        default:
            cout << "Please enter a number between 1-4.\n";
        choice = -1;
        break;
    }
}

void Menu::displayRev() {
    cout << "\n=============================" << endl;
    cout << " Currently, we have made: " << endl;
    cout << " $" << hotel.getRev() << endl;
    if (hotel.getRev() > 0) {
        cout << " Keep up the good work!" << endl;
    }
    cout << "=============================" << endl;
}

void Menu::endDay() {
    cout << "\n=============================" << endl;
    cout << " It's the end of the day!\n We were able to generate: " << endl;
    cout << " $" << hotel.getRev() << " worth of revenue." << endl;
    cout << "=============================" << endl;
    cout << " We booked " << hotel.countOccupiedRooms() << " rooms in total.\n";
    map<string, int> bookedCounts = hotel.countBookedByType();
    const vector<string> orderedKeys = {"Courtyard", "Scenic", "Deluxe Suite", "Penthouse"};
    for (const auto& key : orderedKeys) {
        if (auto it = bookedCounts.find(key); it != bookedCounts.end()) {
            cout << " " << it->second << " of them ";
            if (it->second == 1) {cout << "was a ";} else {cout << "were ";}
            cout << it->first;
            if (it->second != 1) {cout << "s";}
            cout << endl;
        }

    }
    hotel.saveToFile(inputDate);
    cout << "=============================" << endl;
    cout << "Have a good night and see you tomorrow!\n";
}
