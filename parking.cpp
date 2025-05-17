#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

fstream file;
int tryal = 0;

struct attendant_info
{
    string name, email, password;
    int attendant_id, contact_info;
};

struct vehicle_owner
{
    string name, vehicle_brand, plate_number, phone_num;
    int slotID;
};

class parking
{
public:
    string vehicle_type, status = "free";
    int slot_id;
    double price;
    struct vehicle_owner;
};

// initialize parking slots in a 2D array.
const int n = 10;
parking parking_slots[3][n];

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
    if (tryal > 4)
    {
        cout << "Too many invalid inputs ; Program is terminating!\n";
        exit(0);
    }
    else
    {
        cout << "Invalid Input! Please Enter a valid input (Integer)." << endl;
    }
};

int option1()
{
    cout << "Hello! Please choose your role: " << endl;
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
parking get_free_parking_slot(int type_vh)
{
    for (int i = 0; i < n; i++)
    {
        if (parking_slots[type_vh][i].status == "free")
        {
            return parking_slots[type_vh][i];
        }
    }
    cout << "No parking slots available currently!\n";
    cout << "Please come back later.\n";
    exit(0);
};

// Gets the current time as a string to store.
void check_time(char *time1)
{
    auto global_time = time(nullptr);
    tm *local_time = localtime(&global_time);
    strftime(time1, 6, "%H:%M", local_time);
};

void register_attendant();
void sign_in();

void attendant_op();

// Entering vehicles' menu and operation
void entering_vehicle()
{
    int entry_time = time(nullptr);
    int vh_type;

    vehicle_owner vehicle1;
    ofstream vehicles_file("vehicles.txt", ios::out);

    if (!vehicles_file)
    {
        cout << "Couldn't open vehicle file!\n";
        exit(0);
    }

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

    cout << "Enter your plate number: \n";
    cin >> vehicle1.plate_number;

    cout << "Enter your phone number: \n";
    cin >> vehicle1.phone_num;

    parking free_slot = get_free_parking_slot(vh_type);
    vehicle1.slotID = free_slot.slot_id;

    free_slot.status = "Occupied";
    vehicles_file
        << vehicle1.name
        << "\t" << vehicle1.slotID
        << "\t" << vehicle1.vehicle_brand
        << "\t" << vehicle1.plate_number
        << "\t" << vehicle1.phone_num << endl;
    vehicles_file.close();
};

// Exiting vehicles' owners
void exiting_vehicles()
{
    int exit_time;
};

void vehicle_owner_op()
{
    /*
    prompt user: entering or exiting checker
    file: entered vehicles / exited vehicles
    time tracker for both enter and exit
    if entering goto entering_vehicle()
    else exiting goto exiting_vehicles()
    feedback
    */
    int vo_choice;
    cout << "Welcome to the Vehicle owners menu!\n";
    cout << "What do you want to do? \n";
vo_input:
    cout << "1. Enter the parking space.\n";
    cout << "2. Exit the parking space.\n";
    cout << "3. Reserve a parking space.\n";
    cout << "4. Exit to main menu.\n";
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
    default:
        break;
    }
};
int attendant_id_generate();
void entering_vehicle();
void exiting_vehicles();

int main()
{
    // menu:
    int choice1 = option1();
    if (choice1 == 1)
        attendant_op();
    else if (choice1 == 2)
        vehicle_owner_op();
    else
    {
        cout << "Exiting the program; have a nice day!" << endl;
        exit(0);
    }
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
        main();
        break;
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
    cout << "\nSign in options ";
    cout << " \n1.Sign with email";
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
    /*summery:trasaction history
                (ownwner info / feedback and rating)
                display parking slot info(available, reserved, occupied, expired(passed the time limit)) slots
                display entry and exit time
                display price
                search for vehicle owner(by ID, vehicle name, type)
    */

    attendant_info att;
    find(&att, email);
    int att_choice;
    cout << "Hello parking attendant " << att.name << "!\n";
    cout << "What would you like to do today: \n\n";
    cout << "1. Display Parking Slot info.\n";
    cout << "2. Display history of entry and exit.\n";
    cout << "3. Search and display vehicle owner information.\n";
    cout << "4. Display transaction history.\n";
    cout << "5. Exit to menu.\n";
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
    }
    break;
    case 2:
    {
    }
    break;
    case 3:
    {
    }
    break;
    case 4:
    {
    }
    break;
    default:
    {
        cout << "Exiting to main menu!\n\n";
        main();
    }
    break;
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
        exit(1);
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
}
