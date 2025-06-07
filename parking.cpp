#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

fstream file;
int tryal = 0;
bool create_slot = false;
double rate[] = {0.004, 0.08, 0.009};

struct attendant_info
{
    string name, email, password;
    int attendant_id, contact_info;
};

struct vehicle_owner
{
    string name = "--", vehicle_brand, plate_number, phone_num;
    int slotID, vh_type;
    long long int entry_time;
};

class parking
{
public:
    string status = "free";
    int slot_id, vehicle_type;
    vehicle_owner owner;
};

// initialize parking slots in a 2D array.
const int n = 10;
parking parking_slots[3][n];

void create_parking_slots()
{
    int slot_ = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            parking_slots[i][j].slot_id = slot_;
            slot_++;
        }
    }
};

// Read and display files.
void display(int choice)
{
    switch (choice)
    {
    case 1:
    {
        cout << "All parking slots information: \n";
        cout << "SlotId\tStatus\t\tVehicle Owner name\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << parking_slots[i][j].slot_id << "\t"
                     << parking_slots[i][j].status
                     << "\t\t" << parking_slots[i][j].owner.name << endl;
            }
        }
    }
    break;
    case 2:
    {
    }
    break;
    case 3:
    {
        ifstream tr_his("transaction.txt", ios::in);
        if (!tr_his)
        {
            cout << "No transactions made yet!\n";
            break;
        }
        string name;
        int slotID, price, entry_time, exit_time;

        cout << "\nTransaction History:\n\n";
        cout << "Name\tSlotID\tPrice Payed($)\n";

        while (tr_his >> name >> slotID >> price)
        {
            cout << name << "\t" << slotID << "\t" << price << endl;
        }
        tr_his.close();
    }
    break;
    default:
        break;
    }
};

// Finds the attendant from file and sets the parameters of the givent stuct to the found id.
void find(attendant_info *att, string email)
{
    ifstream attendant_rec("attendant_file.txt", ios::in);

    string email2, name, password;
    int contact_info, attendant_id;

    while (attendant_rec >> email2 >> name >> attendant_id >> contact_info >> password)
    {
        // Check if the email already exists
        if (email == email2)
        {
            att->attendant_id = attendant_id;
            att->name = name;
            att->email = email;
            att->contact_info = contact_info;
            att->password = password;
            attendant_rec.close();
            return;
        }
    }
    attendant_rec.close();
};

// Implemets all the functionality for the attendants.
void attendant_action(string email);

void err()
{
    tryal += 1;
    cin.clear();
    cin.ignore();
    if (tryal > 4)
    {
        cout << "Too many invalid inputs!\nProgram is terminating!\n";
        exit(0);
    }
    else
    {
        cout << "Invalid Input! Please Enter a valid input (Integer)." << endl;
    }
};

int option1()
{
    cout << "\nHello! Please choose your role: " << endl;
    cout << "Interact with the menu by pressing the number of your choice! " << endl;

    int choice;
a:
    cout << "1. Parking Attendant (Admin)." << endl;
    cout << "2. Vehicle Owner." << endl;
    cout << "3. Exit Program." << endl;
    cout << "Your Choice: ";
    // Accept user Input
    cin >> choice;
    // Validate Input
    if (cin.fail())
    {
        err();
        goto a;
    }
    cout << endl;
    return choice;
};

int option2()
{
    int choice;
b:
    cout << "Have you already Registered in the system ? " << endl;
    cout << "1. Yes (Sign in) " << endl;
    cout << "2. No (Register) " << endl;
    cout << "3. Go to main menu " << endl;
    cout << "Your Choice: ";
    cin >> choice;

    if (cin.fail())
    {
        err();
        goto b;
    }
    return choice;
};

bool search(string);

// Find and give a free slot to the vehicle owner.
int get_free_parking_slot(int type_vh)
{
    for (int i = 0; i < n; i++)
    {
        if (parking_slots[type_vh][i].status == "free")
        {
            return i;
        }
    }
    cout << "No parking slots available currently!\n";
    cout << "Please come back later.\n";
    return -1;
};

// Gets the current time as a string to store.
void check_time(char time1[6])
{
    auto global_time = time(nullptr);
    tm *local_time = localtime(&global_time);
    strftime(time1, 6, "%H:%M", local_time);
};

void register_attendant();
void sign_in();

void attendant_op();

// reserve a parkin slot using all the informations from the vehicle owner
void reserve_slot()
{
    int entry_time = time(nullptr);
    int vh_type;

    vehicle_owner vehicle1;
    ofstream vehicles_file("vehicles.txt", ios::app);

    if (!vehicles_file)
    {
        cout << "Couldn't open vehicle file!\n";
        return;
    }

    cout << endl;
    cout << "Welcome!\n";

    cout << "Enter your name: \n";
    cin >> vehicle1.name;

    cout << "Enter the brand of your vehicle: \n";
    cin >> vehicle1.vehicle_brand;
vehicle_type_input:
    cout << "Enter your vehicle size: \n";
    cout << "1. Light weight (upto 4500 Kg) :\n";
    cout << "2. Heavy weight (4500+ kg): \n";
    cout << "3. Very Light (Motorbikes, Three wheeled): \n";
    cout << "Your choice: ";
    cin >> vh_type;

    if (cin.fail())
    {
        err();
        goto vehicle_type_input;
    }

    vh_type--;

    cout << "Enter your plate number: \n";
    cin >> vehicle1.plate_number;

    cout << "Enter your phone number: \n";
    cin >> vehicle1.phone_num;

    int free_slot = get_free_parking_slot(vh_type);
    if (free_slot == -1)
    {
        return;
    }
    parking_slots[vh_type][free_slot].owner = vehicle1;
    vehicle1.slotID = parking_slots[vh_type][free_slot].slot_id;
    vehicle1.entry_time = entry_time;

    parking_slots[vh_type][free_slot].status = "reserved";
    vehicles_file
        << vehicle1.name
        << "\t" << vehicle1.slotID
        << "\t" << vehicle1.vehicle_brand
        << "\t" << vehicle1.plate_number
        << "\t" << vehicle1.phone_num << endl;

    vehicles_file.close();
    cout << "You have successfully Reserved a parking slot, with ID: " << vehicle1.slotID << endl;
};

// Make a reserved slot free.
void unreserve(int slotID)
{
    bool found = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (parking_slots[i][j].slot_id == slotID && parking_slots[i][j].status == "reserved")
            {
                parking_slots[i][j].status = "free";
                cout << "\nSuccessfully Unreserved Slot!\n";
                found = true;
            }
        }
    }
    if (!found)
    {
        cout << "\nSlot isn't reserved!\n";
    }
};

// finds the reserved slot for the vehicle owner by using slot ID
void reserve_finder()
{
    int slot_id, vh_type, index;
    cout << "Enter slot ID: ";
    cin >> slot_id;
    cout << "Enter your vehicle size: \n";
    cout << "1. Light weight (upto 4500 Kg) :\n";
    cout << "2. Heavy weight (4500+ kg): \n";
    cout << "3. Very Light (Motorbikes, Three wheeled): \n";
    cout << "Your choice: ";
    cin >> vh_type;

    bool valid = false;
    for (int i = 0; i < n; i++)
    {
        if (parking_slots[vh_type - 1][i].status == "reserved" && parking_slots[vh_type - 1][i].slot_id == slot_id)
        {
            index = 0;
            cout << "Slot found! Hello " << parking_slots[vh_type - 1][i].owner.name << "!\n";
            cout << "Please go to your slot." << endl;
            parking_slots[vh_type - 1][i].status = "occupied";
            valid = true;
            break;
        }
    }
    if (!valid)
    {
        cout << "Sorry Slot ID not found\n";
    }
};

// this function finds and returns the vehicle owner in the slots.
void find_vehicle_owner(int slotid, vehicle_owner *owner)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (parking_slots[i][j].slot_id == slotid)
            {
                parking_slots[i][j].status = "free";
                owner->name = parking_slots[i][j].owner.name;
                owner->entry_time = parking_slots[i][j].owner.entry_time;
                owner->slotID = parking_slots[i][j].slot_id;
                owner->vh_type = parking_slots[i][j].owner.vh_type;
                return;
            }
        }
    }
};

// Entering vehicles' menu and operation
void entering_vehicle()
{
    auto entry_time = time(nullptr);
    int vh_type;

    vehicle_owner vehicle1;
    ofstream vehicles_file("vehicles.txt", ios::app);

    if (!vehicles_file)
    {
        cout << "Couldn't open vehicle file!\n";
        return;
    }

    cout << endl;
    cout << "Welcome!\n";
    cout << "Enter your name: \n";
    cin >> vehicle1.name;

    cout << "Enter the brand of your vehicle: \n";
    cin >> vehicle1.vehicle_brand;
vehicle_type_input:
    cout << "Enter your vehicle size: \n";
    cout << "1. Light weight (upto 4500 Kg) :\n";
    cout << "2. Heavy weight (4500+ kg): \n";
    cout << "3. Very Light (Motorbikes, Three wheeled): \n";
    cout << "Your choice: ";
    cin >> vh_type;

    if (cin.fail())
    {
        err();
        goto vehicle_type_input;
    }

    vh_type--;
    vehicle1.vh_type = vh_type;
    cout << "Enter your plate number: \n";
    cin >> vehicle1.plate_number;

    cout << "Enter your phone number: \n";
    cin >> vehicle1.phone_num;

    int free_slot = get_free_parking_slot(vh_type);
    if (free_slot == -1)
    {
        return;
    }
    parking_slots[vh_type][free_slot].owner = vehicle1;

    vehicle1.slotID = parking_slots[vh_type][free_slot].slot_id;
    vehicle1.entry_time = entry_time;
    parking_slots[vh_type][free_slot].status = "Occupied";

    vehicles_file
        << vehicle1.name
        << "\t" << vehicle1.slotID
        << "\t" << vehicle1.vehicle_brand
        << "\t" << vehicle1.plate_number
        << "\t" << vehicle1.phone_num << endl;

    vehicles_file.close();
    cout << "You have successfully entered, \n\nPlease head to slot number " << vehicle1.slotID << endl;
};

// Exiting vehicles' owners
void exiting_vehicles()
{
    long long int exit_time = time(nullptr);
    double price;

    ofstream transaction("transaction.txt", ios::app);
    ifstream vehicles("vehicles.txt", ios::in);

    if (!transaction || !vehicles)
    {
        cout << "Error opening the file !" << endl;
        exit(0);
    }

    int slot;
    cout << "Enter slot ID: \n";
    cin >> slot;

    vehicle_owner owner;
    find_vehicle_owner(slot, &owner);
    if (owner.name == "--")
    {
        cout << "No vehicle owner in this slot!\n";
        return;
    }
    cout << owner.name << "\t" << owner.entry_time << endl;
    price = rate[owner.vh_type] * (exit_time - owner.entry_time);
    cout << "Exit time: " << exit_time << "\t" << "Entry time: " << owner.entry_time << endl;
pay:
    int choice;
    cout << "Hello " << owner.name << "!" << endl;
    cout << "You are charged " << price << " amount by the rate of " << rate[slot - 1] << " per second!\nPlease pay the amount:\n";
    cout << "1. Pay " << price << "$\nYour Choice: ";
    cin >> choice;

    if (cin.fail())
    {
        err();
        goto pay;
    }

    transaction << owner.name
                << "\t" << owner.slotID
                << "\t" << price << endl;

    cout << "Transaction successfully done !\n";
    cout << "Have a nice day!\n";

    transaction.close();
    vehicles.close();
};

void vehicle_owner_op()
{
    int vo_choice;
    cout << "Welcome to the Vehicle owners menu!\n";
    cout << "What do you want to do? \n";
vo_input:
    cout << "1. Enter the parking space.\n";
    cout << "2. Exit the parking space.\n";
    cout << "3. Reserve a parking space.\n";
    cout << "4. Enter a reserved parking slot.\n";
    cout << "5. Exit to main menu.\n";
    cout << "Your choice: ";
    cin >> vo_choice;
    if (cin.fail())
    {
        err();
        goto vo_input;
    }
    switch (vo_choice)
    {
    case 1:
    {
        entering_vehicle();
    }
    break;
    case 2:
    {
        exiting_vehicles();
    }
    break;
    case 3:
    {
        reserve_slot();
    }
    break;
    case 4:
    {
        reserve_finder();
    }
    break;
    default:
        break;
    }
};

int main()
{
    if (!create_slot)
    {
        create_parking_slots();
        create_slot = true;
    }

    // menu:
    int choice1 = 1;
    do
    {
        choice1 = option1();
        if (choice1 == 1)
            attendant_op();
        else if (choice1 == 2)
            vehicle_owner_op();
        else
        {
            cout << "Exiting the program; have a nice day!" << endl;
            exit(0);
        }
    } while (choice1 != 3);
}

void attendant_op()
{
    int choice2 = option2();

    switch (choice2)
    {
    case 1:
        sign_in();
        break;
    case 2:
        register_attendant();
        break;
    case 3:
        return;
    default:
        err();
        break;
    }
};

bool search(string email2)
{
    ifstream attendant_rec("attendant_file.txt", ios::in);
    if (!attendant_rec.is_open())
    {
        // Handle file opening exceptions
        cout << "File not opened properly!";
        return false;
    }
    // Initialize attributes to read from the file
    string name, email, password;
    int attendant_id, contact_info;

    while (attendant_rec >> email >> name >> attendant_id >> contact_info >> password)
    {
        // Check if the email already exists
        if (email == email2)
        {
            return true;
        }
    }
    return false;
};

void sign_in()
{
    ifstream infile("attendant_file.txt");
    attendant_info attendant;
    string email, password;
    int id, choice;
    bool email_found = false;
    bool id_found = false;
Y:
    cout << "\nSign in options: ";
    cout << "\n1.Sign with email";
    cout << "\n2.Sign with id" << endl;
    cout << "Your choice : ";
    cin >> choice;

    if (!infile)
    {
        cout << " unable to open 'attendent_file.txt' file ";
        return;
    }
A:
    if (choice == 1)
    {
        cout << "Enter your email : ";
        cin >> email;
    Z:
        cout << "Enter your password : ";
        cin >> password;

        infile.clear();
        infile.seekg(0);

        while (infile >> attendant.email >> attendant.name >> attendant.attendant_id >> attendant.contact_info >> attendant.password)
        {
            if (attendant.email == email)
            {
                email_found = true;
                if (attendant.password == password)
                {
                    cout << "Sign in successfully! \n"
                         << endl;
                    attendant_action(attendant.email);
                    return;
                }
                else
                {
                    cout << "Incorrect password Please enter the correct password! " << endl;
                    goto Z;
                }
            }
        }
        if (!email_found)
        {
            cout << "Incorrect email please enter the correct email again " << endl;
            goto A;
        }
    }
    else if (choice == 2)
    {
    B:
        cout << "Enter your id : ";
        cin >> id;

        cout << "Enter your password : ";
        cin >> password;

        infile.clear();
        infile.seekg(0);

        while (infile >> attendant.email >> attendant.name >> attendant.attendant_id >> attendant.contact_info >> attendant.password)
        {
            if (attendant.attendant_id == id)
            {
                id_found = true;
                if (attendant.password == password)
                {
                    cout << "Sign in successfully !" << endl;
                    attendant_action(attendant.email);
                    return;
                }
                else
                {
                    cout << "Incorrect password Please enter the correct password! " << endl;
                    goto B;
                }
            }
        }
        if (!id_found)
        {
            cout << "Invalid id !" << endl;
            goto B;
        }
    }
    else
    {
        cout << "Please enter a valid choice!\n";
        cin.clear();
        cin.ignore();
        goto Y;
    }

    infile.close();
}

void attendant_action(string email)
{
    // Store attendant as a structure.
    attendant_info att;

    // Fill the structure with the attendant information.
    find(&att, email);

    int att_choice = 1;
    do
    {
        cout << "\nHello parking attendant " << att.name << "!\n";
        cout << "What would you like to do today: \n\n";

        cout << "1. Display Parking Slot info.\n";
        cout << "2. Display history of entry and exit.\n";
        cout << "3. Search and display vehicle owner information.\n";
        cout << "4. Display transaction history.\n";
        cout << "5. Unreserve a reserved parking slot.\n";
        cout << "6. Exit to menu.\n\n";
    att_inp:
        cout << "Your choice: ";
        cin >> att_choice;

        if (cin.fail())
        {
            err();
            goto att_inp;
        }

        switch (att_choice)
        {
        case 1:
        {
            display(1);
        }
        break;
        case 2:
        {
            display(2);
        }
        break;
        case 3:
        {
            string name;
            bool found = false;

            cout << "Enter vehicle owner name: ";
            cin >> name;

            ifstream vehichles_file("vehicles.txt", ios::in);
            if (!vehichles_file)
            {
                cout << "\nVehicles file not opened properly!\n";
                return;
            }
            vehicle_owner tmp;
            while (vehichles_file >> tmp.name >> tmp.slotID >> tmp.vehicle_brand >> tmp.plate_number >> tmp.phone_num)
            {
                if (tmp.name == name)
                {
                    cout << "\nVehicle owner information: \nName\tSlot ID\t\tVehicle\t\tPlate Number\tPhone Number\n";
                    cout << tmp.name << "\t"
                         << tmp.slotID
                         << "\t\t" << tmp.vehicle_brand
                         << "\t\t" << tmp.plate_number
                         << "\t\t" << tmp.phone_num << endl;
                    found = true;
                }
            }
            if (!found)
                cout << "\nNo vehicle owner with such name!\n";
            vehichles_file.close();
        }
        break;
        case 4:
        {
            display(3);
        }
        break;
        case 5:
        {
            int slotID;
            cout << "Enter slotID to unreserve: ";
            cin >> slotID;
            unreserve(slotID);
        }
        break;
        default:
        {
            cout << "Exiting to main menu!\n\n";
            return;
        }
        break;
        }
    } while (att_choice != 6);
};

int attendant_id_generate()
{
    string name, email, password;
    int attendant_id = 1000, contact_info;

    file.open("attendant_file.txt", ios::in);
    if (file.peek() == ifstream::traits_type::eof())
    {
        file.close();
        return attendant_id;
    }
    else
    {
        while (file >> email >> name >> attendant_id >> contact_info >> password)
        {
        }
        file.close();
        return attendant_id += 1;
    }
};

void register_attendant()
{
    attendant_info att;
    string email, pass1, pass2;
    ofstream file("attendant_file.txt", ios::app);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }
a:
    cout << "Enter email: ";
    cin >> email;
    if (search(email))
    {
        int c = 0;
    b:
        cout << "Account with this email already exist, Do you want to sign in ? \n1. Yes \n2. No \nYour choice: ";
        cin >> c;

        if (c == 1)
        {
            sign_in();
        }
        else if (c == 2)
        {
            cout << "Please Enter a new email to register!" << endl;
            goto a;
        }
        else
        {
            cout << "Invalid input Please enter a valid input !!!";
            goto b;
        }
    }
    else
    {
        att.email = email;
        cout << "Enter name: ";

        cin >> att.name;
        cout << "Enter phone number: ";

        cin >> att.contact_info;
    c:
        cout << "Enter password: " << endl;
        cin >> pass1;

        cout << "Confirm password: " << endl;
        cin >> pass2;

        if (pass1 == pass2)
        {
            att.attendant_id = attendant_id_generate();
            att.password = pass1;
            cout << "Successfuly registered as " << att.name << " with ID: " << att.attendant_id << endl;
            file << att.email << "\t" << att.name << "\t" << att.attendant_id << "\t" << att.contact_info << "\t" << att.password << endl;
        }
        else
        {
            cout << "Password is not the same !!!" << endl;
            goto c;
        }
        file.close();
    }
};

/* Unsolved Problems:
    - Entry time not stored properly!
        - Entry and exit display doesn't work. (Att_act --> choice 2)
    - Slot generation doesn't work through exiting program. 
        * use file to read from it every time program starts.
        * make program never exit.
*/