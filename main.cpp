#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

// ======================================
// ROOM CLASS
// ======================================

class Room {

private:
    int roomNumber;
    string roomType;
    string status;
    double price;

public:

    Room(int roomNumber,
         string roomType,
         string status,
         double price)
    {
        this->roomNumber = roomNumber;
        this->roomType = roomType;
        this->status = status;
        this->price = price;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    string getRoomType() {
        return roomType;
    }

    string getStatus() {
        return status;
    }

    double getPrice() {
        return price;
    }

    void setRoomType(string roomType) {
        this->roomType = roomType;
    }

    void setStatus(string status) {
        this->status = status;
    }

    void setPrice(double price) {
        this->price = price;
    }
};

// ======================================
// PRINT MENU
// ======================================

void printMenu(vector<string> items) {

    Table table;

    table.add_row({"NO", "HOTEL MENU"});

    for (int i = 0; i < items.size(); i++) {

        table.add_row({
            to_string(i + 1),
            items[i]
        });
    }

    table[0]
        .format()
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);

    table.column(0)
        .format()
        .font_color(Color::cyan);

    table.column(1)
        .format()
        .font_color(Color::green);

    cout << table << endl;
}

// ======================================
// DISPLAY ROOM TABLE
// ======================================

void printRoomTable(vector<Room> rooms) {

    if (rooms.empty()) {

        cout << "No Room Data Found ❌"
             << endl;

        return;
    }

    Table table;

    table.add_row({
        "Row",
        "Room No",
        "Room Type",
        "Status",
        "Price"
    });

    int row = 1;

    for (Room room : rooms) {

        table.add_row({

            to_string(row),
            to_string(room.getRoomNumber()),
            room.getRoomType(),
            room.getStatus(),
            "$" + to_string((int)room.getPrice())
        });

        row++;
    }

    table[0]
        .format()
        .font_style({FontStyle::bold})
        .font_color(Color::yellow)
        .background_color(Color::blue);

    cout << table << endl;
}

// ======================================
// SAVE DATA TO CSV FILE
// ======================================

void saveRoomsToFile(
    string filename,
    vector<Room> rooms)
{
    ofstream file(filename);

    for (Room room : rooms) {

        file
        << room.getRoomNumber() << ","
        << room.getRoomType() << ","
        << room.getStatus() << ","
        << room.getPrice()
        << endl;
    }

    file.close();

    cout << "Saved Successfully ✅"
         << endl;
}

// ======================================
// LOAD DATA FROM CSV FILE
// ======================================

vector<Room> loadRoomsFromFile(
    string filename)
{
    vector<Room> rooms;

    ifstream file(filename);

    string line;

    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);

        string roomNo;
        string type;
        string status;
        string price;

        getline(ss, roomNo, ',');
        getline(ss, type, ',');
        getline(ss, status, ',');
        getline(ss, price, ',');

        Room room(
            stoi(roomNo),
            type,
            status,
            stod(price)
        );

        rooms.push_back(room);
    }

    file.close();

    return rooms;
}

// ======================================
// MAIN FUNCTION
// ======================================

int main() {

    system("clear");

    string filename = "hoteldata.csv";

    vector<string> programMenu = {

        "Add New Room",
        "Delete Room",
        "Show All Rooms",
        "Search Room",
        "Sort Room By Price",
        "Exit"
    };

    int option;

    vector<Room> roomLists =
        loadRoomsFromFile(filename);

    do {

        printMenu(programMenu);

        cout << "Choose Option : ";
        cin >> option;

        switch (option) {

        // ==================================
        // ADD ROOM
        // ==================================

        case 1:
        {
            int roomNumber;
            string roomType;
            string status;
            double price;

            cout << "Enter Room Number : ";
            cin >> roomNumber;

            cin.ignore();

            cout << "Enter Room Type : ";
            getline(cin, roomType);

            cout << "Enter Status : ";
            getline(cin, status);

            cout << "Enter Price : ";
            cin >> price;

            Room newRoom(
                roomNumber,
                roomType,
                status,
                price
            );

            roomLists.push_back(newRoom);

            saveRoomsToFile(
                filename,
                roomLists
            );
        }
        break;

        // ==================================
        // DELETE ROOM
        // ==================================

        case 2:
        {
            printRoomTable(roomLists);

            int row;

            cout << "Enter Row To Delete : ";
            cin >> row;

            if (row > 0 &&
                row <= roomLists.size())
            {
                roomLists.erase(
                    roomLists.begin() + row - 1
                );

                saveRoomsToFile(
                    filename,
                    roomLists
                );

                cout << "Deleted Successfully ✅"
                     << endl;
            }
            else {

                cout << "Invalid Row ❌"
                     << endl;
            }
        }
        break;

        // ==================================
        // SHOW ALL ROOMS
        // ==================================

        case 3:
        {
            printRoomTable(roomLists);
        }
        break;

        // ==================================
        // SEARCH ROOM
        // ==================================

        case 4:
        {
            int searchRoom;

            cout << "Enter Room Number : ";
            cin >> searchRoom;

            bool found = false;

            vector<Room> result;

            for (Room room : roomLists) {

                if (room.getRoomNumber()
                    == searchRoom)
                {
                    result.push_back(room);

                    found = true;
                }
            }

            if (found) {

                printRoomTable(result);

            } else {

                cout << "Room Not Found ❌"
                     << endl;
            }
        }
        break;

        // ==================================
        // SORT ROOM
        // ==================================

        case 5:
        {
            sort(
                roomLists.begin(),
                roomLists.end(),

                [](Room a, Room b) {

                    return a.getPrice()
                        < b.getPrice();
                }
            );

            printRoomTable(roomLists);
        }
        break;

        // ==================================
        // EXIT
        // ==================================

        case 6:
        {
            cout << "Exiting Program..."
                 << endl;
        }
        break;

        // ==================================
        // DEFAULT
        // ==================================

        default:
        {
            cout << "Invalid Option ❌"
                 << endl;
        }

        }

    } while (option != 6);

    return 0;
}