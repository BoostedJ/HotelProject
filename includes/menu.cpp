#include "Menu.h"
#include <iostream>
#include <limits>
#include <fstream>
using namespace std;

bool isValidDate(const string& date) {
    if (date.length() != 8) { return false; }
    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '-' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '-' ||
        !isdigit(date[6]) || !isdigit(date[7])) {
        return false;
        }
    return true;
}
void processDate(const string& date) {
    string filename = date;
    ifstream existingFile(filename);
    if (existingFile) {
        cout << "Data for " << date << ":" << endl;
        string line;
        while (getline(existingFile, line)) {
            cout << line << endl;
        }
        existingFile.close();
    } else {
        ofstream newFile(filename);
        newFile.close();
    }
}
void Menu::beginDay() {
    string inputDate;
    while(true) {
        cout << "Welcome to the Hotel administrator platform!" << endl;
        cout << "Please enter the desired date! (mm-dd-yy): ";
        cin >> inputDate;
        if (isValidDate(inputDate)) {
            break;
        } else {
            cout << "Invalid date format. Please try again." << endl;
        }
    }

}
void Menu::displayMenu() {
    bool cont = true;

    do {
        cout << "=============================" << endl;
        cout << "        " << date << " " << endl;
        cout << "=============================" << endl;
        cout << "1. Reserve a room" << endl;
        cout << "2. Display Rooms Available" << endl;
        cout << "3. Display Current Revenue" << endl;
        cout << "4. End of Day Report" << endl;
        cout << "5. Exit" << endl;
        cout << "=============================" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number between 1-4. \n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                //displayRooms();
                break;
            case 3:
                //displayRev();
                break;
            case 4:
                //getTotal();
                cont = false;
                break;
            case 5:
                //cout << "Thank you and have a good rest of your day!" << endl;
                cont = false;
                break;
            default:
                cout << "Please enter a number between 1-4.\n";
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
    cout << "6. Exit" << endl;
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
        cin.clear();
        cout << "Please enter a number between 1-6. \n";
    }

    switch (choice) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            cout << endl << endl;
            break;
        default:
            cout << "Please enter a number between 1-4.\n";
            choice = -1;
            break;
    }
}
/*
void Menu::displayRooms() {
    cout << "\n=============================" << endl;
    cout << " Rooms currently available: \n";

    int available = 0;
    for (int i=0; i < sizeof(rooms)/sizeof(rooms[0]); i++) {
        available += rooms[i].getAvailableRooms();
        cout << "   " << rooms[i].getAvailableRooms() << " " << rooms[i].name;
        if (rooms[i].getAvailableRooms() != 1) {
            cout << "s";
        }
        cout << "." << endl;
    }
    cout << " In total, there are " << available << " rooms left\n";
    cout << "=============================" << endl;
    cout << "Please press Enter or any key to continue..." << endl;
    string io;
    getline(cin, io);
}
void Menu::displayRev() const {
    cout << "\n=============================" << endl;
    cout << " Currently, we have made: " << endl;
    cout << " $" << revenue << endl;
    if (revenue > 0) {
        cout << " Keep up the good work!" << endl;
    }
    cout << "=============================" << endl;
    cout << "Please press Enter or any key to continue..." << endl;
    string io;
    getline(cin, io);
}
void Menu::getTotal() const {
    cout << "\n=============================" << endl;
    cout << " It's the end of the day!\n We were able to generate: " << endl;
    cout << " $" << revenue << " worth of revenue.";
    if (revenue < 350) {
        cout << " This is not acceptable!" << endl;
    } else {
        cout << " This is acceptable." << endl;
    }
    cout << "=============================" << endl;

    cout << " We booked " << totSold << " rooms in total.\n";
    for (int i = 0; i < sizeof(rooms)/sizeof(rooms[0]); i++) {
        int dR = rooms[i].getTotalRooms() - rooms[i].getAvailableRooms();
        cout << " " << dR << " of them ";
        if (dR != 1) { cout << "were "; }
        else { cout << "was a "; }
        cout << rooms[i].name;
        if (dR != 1) {
            cout << "s";
        }
        cout << "." << endl;
    }
    cout << "=============================" << endl;
    cout << "Have a good night and see you tomorrow!\n";
}
*/