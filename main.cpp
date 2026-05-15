#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tabulate/table.hpp>
#include <map>

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


class Booking {

private:
    string username;
    int roomNumber;

public:

    Booking(
        string username,
        int roomNumber
    )
    {
        this->username =
            username;

        this->roomNumber =
            roomNumber;
    }

    string getUsername()
    {
        return username;
    }

    int getRoomNumber()
    {
        return roomNumber;
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

    "Login",
    "Register",
    "Exit"
    };

    int option;

    string username;
    string password;

    string adminUsername = "admin";
    string adminPassword = "123";
    map<string, string> guestAccounts;

    bool isLogin = false;
    guestAccounts["guest"] = "123";
    vector<Room> roomLists =
        loadRoomsFromFile(filename);
        vector<Booking> bookings;

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
    cout << "Enter Username : ";
    cin >> username;

    cout << "Enter Password : ";
    cin >> password;

    if (username == adminUsername &&
        password == adminPassword)
    {
        cout
        << "\nLogin Successful ✅\n";

        isLogin = true;

        while(isLogin)
        {
            vector<string> adminMenu = {

    "Add New Room",
    "Update Room",
    "Delete Room",
    "Show All Rooms",
    "Search Room",
    "Sort Room By Price",
    "View All Bookings",
    "Logout"
};

            int adminOption;

            printMenu(adminMenu);

            cout
            << "Choose Option : ";

            cin >> adminOption;

            switch(adminOption)
            {

            case 1:
            {
                int roomNumber;
                string roomType;
                string status;
                double price;

                cout
                << "Enter Room Number : ";

                cin >> roomNumber;

                cin.ignore();

                cout
                << "Enter Room Type : ";

                getline(cin,
                        roomType);

                cout
                << "Enter Status : ";

                getline(cin,
                        status);

                cout
                << "Enter Price : ";

                cin >> price;

                Room newRoom(
                    roomNumber,
                    roomType,
                    status,
                    price
                );

                roomLists.push_back(
                    newRoom
                );

                saveRoomsToFile(
                    filename,
                    roomLists
                );
            }
            break;

            case 2:
{
    printRoomTable(
        roomLists
    );

    int roomNumber;

    cout
    << "Enter Room Number To Update : ";

    cin
    >> roomNumber;

    bool found = false;

    for(Room &room :
        roomLists)
    {
        if(room
            .getRoomNumber()
            ==
            roomNumber)
        {
            string newType;
            string newStatus;
            double newPrice;

            cin.ignore();

            cout
            << "New Room Type : ";

            getline(
                cin,
                newType
            );

            cout
            << "New Status : ";

            getline(
                cin,
                newStatus
            );

            cout
            << "New Price : ";

            cin
            >> newPrice;

            room.setRoomType(
                newType
            );

            room.setStatus(
                newStatus
            );

            room.setPrice(
                newPrice
            );

            saveRoomsToFile(
                filename,
                roomLists
            );

            cout
            << "Room Updated ✅"
            << endl;

            found = true;
        }
    }

    if(!found)
    {
        cout
        << "Room Not Found ❌"
        << endl;
    }
}
break;

            case 3:
{
    int row;

    printRoomTable(
        roomLists
    );

    cout
    << "Enter Row To Delete : ";

    cin
    >> row;

    if(row > 0 &&
       row <= roomLists.size())
    {
        roomLists.erase(
            roomLists.begin()
            + row - 1
        );

        saveRoomsToFile(
            filename,
            roomLists
        );

        cout
        << "Room Deleted Successfully ✅"
        << endl;
    }

    else {

        cout
        << "Invalid Row ❌"
        << endl;
    }
}
break;

            case 4:
            {
                printRoomTable(
                    roomLists
                );
            }
            break;

            case 5:
            {
                int searchRoom;

                cout
                << "Enter Room Number : ";

                cin
                >> searchRoom;

                bool found = false;

                for (Room room :
                    roomLists)
                {
                    if(room
                        .getRoomNumber()
                        ==
                        searchRoom)
                    {
                        vector<Room>
                        result;

                        result
                        .push_back(
                            room
                        );

                        printRoomTable(
                            result
                        );

                        found = true;
                    }
                }

                if(!found)
                {
                    cout
                    << "Room Not Found ❌"
                    << endl;
                }
            }
            break;

            case 6:
            {
                sort(
                    roomLists.begin(),
                    roomLists.end(),

                    [](Room a,
                       Room b)
                {
                    return
                    a.getPrice()
                    <
                    b.getPrice();
                });

                printRoomTable(
                    roomLists
                );
            }
            break;
        case 7:
        {
          cout
          << "\nAll Bookings:\n";
        
          if(bookings.empty())
         {
              cout
              << "No Booking Found ❌"
              << endl;
          }
      
         for(
              Booking booking :
              bookings
          )
          {
               cout
               << "Username : "
               << booking.getUsername()
               << " | Room Number : "
               << booking.getRoomNumber()
               << endl;
           }
        }
        break;

            case 8:
            {
                isLogin = false;

                cout
                << "Logout Successful ✅"
                << endl;
            }
            break;
            }
        }
    }

else if(
    guestAccounts.find(username)
    != guestAccounts.end()
    &&
    guestAccounts[username]
    == password
)
{
    cout
    << "\nGuest Login Successful ✅\n";
    
    string currentGuest =
    username;

    bool guestLogin = true;

    while(guestLogin)
    {
        vector<string>
      guestMenu = {

    "View Rooms",
    "Search Room",
    "Book Room",
    "My Booking",
    "Cancel Booking",
    "Logout"
};

        int guestOption;

        printMenu(
            guestMenu
        );

        cout
        << "Choose Option : ";

        cin
        >> guestOption;

        switch(
            guestOption
        )
        {
        case 1:
        {
            printRoomTable(
                roomLists
            );
        }
        break;

        case 2:
        {
            int searchRoom;

            cout
            << "Enter Room Number : ";

            cin
            >> searchRoom;

            vector<Room>
            result;

            for(
                Room room :
                roomLists
            )
            {
                if(room
                    .getRoomNumber()
                    ==
                    searchRoom)
                {
                    result
                    .push_back(
                        room
                    );
                }
            }

            printRoomTable(
                result
            );
        }
        break;

        case 3:
{
    printRoomTable(
        roomLists
    );

    int roomNumber;

    cout
    << "Enter Room Number To Book : ";

    cin
    >> roomNumber;

    bool found = false;

    for(Room &room :
        roomLists)
    {
        if(room
            .getRoomNumber()
            ==
            roomNumber)
        {
            bookings.push_back(

                Booking(
                    currentGuest,
                    roomNumber
                )
            );

                   room.setStatus(
           "Booked"
        );

        saveRoomsToFile(
           filename,
           roomLists
        );

            cout
            << "Room Booked Successfully ✅"
            << endl;

            found = true;
        }
    }

    if(!found)
    {
        cout
        << "Room Not Found ❌"
        << endl;
    }
}
break;

        case 4:
{
    bool found = false;

    cout
    << "\nMy Bookings:\n";

    for(
        Booking booking :
        bookings
    )
    {
        if(
            booking
            .getUsername()
            ==
            currentGuest
        )
        {
            cout
            << "Room Number : "
            << booking
                .getRoomNumber()
            << endl;

            found = true;
        }
    }

    if(!found)
    {
        cout
        << "No Booking Found ❌"
        << endl;
    }
}
break;


case 5:
{
    int roomNumber;

    cout
    << "Enter Room Number To Cancel : ";

    cin
    >> roomNumber;

    bool found = false;

    for(
        int i = 0;
        i < bookings.size();
        i++
    )
    {
        if(
            bookings[i]
            .getUsername()
            ==
            currentGuest
            &&
            bookings[i]
            .getRoomNumber()
            ==
            roomNumber
        )
        {
            bookings.erase(
                bookings.begin()
                + i
            );

                   for(Room &room :
           roomLists)
        {
           if(room
               .getRoomNumber()
               ==
               roomNumber)
           {
               room.setStatus(
                   "Available"
               );
           }
        }

        saveRoomsToFile(
           filename,
           roomLists
        );

            cout
            << "Booking Cancelled ✅"
            << endl;

            found = true;

            break;
        }
    }

    if(!found)
    {
        cout
        << "Booking Not Found ❌"
        << endl;
    }
}
break;

case 6:
{
    guestLogin = false;

    cout
    << "Logout Successful ✅"
    << endl;
}
break;
    
        }
    }
}

else {

    cout
    << "Invalid Login ❌"
    << endl;
}
}
break;

case 2:
{
    string newUsername;
    string newPassword;

    cout
    << "Create Username : ";

    cin
    >> newUsername;

    cout
    << "Create Password : ";

    cin
    >> newPassword;

    guestAccounts[
        newUsername
    ]
    =
    newPassword;

    cout
    << "Registered Successfully ✅"
    << endl;
}
break;
       
case 3:
{
    cout
    << "Exiting Program..."
    << endl;
}
break;
    }

   } while(option != 3);

    return 0;
}