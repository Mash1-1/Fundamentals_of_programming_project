#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int tryal = 0;

struct date
{
    int day, month, year;
};

struct attendant_info
{
    string name;
    int attendant_id, contact_info;
};

struct vehicle_owner
{
    string name;
    int owner_id, vehicle_num, owner_phone_num;
};

struct parking_slot
{
    string slot_id, vehicle_type, status;
    double price;
    struct vehicle_owner;
};

struct transaction
{
};

vector<attendant_info> attendant;

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

bool search();

void exit_program()
{
    cout << "Exiting the program; have a nice day!" << endl;
    exit(0);
};

void register_attendant()
{
    cout << "Registered";
};
void sign_in()
{
    cout << "Enter name and ID";
};

void attendant_op();

void vehicle_owner_op() {
    /*
    enterinr or exiting checker
    file: entered vehicles / exited vehicles

    */
};

int main()
{
    // menu:
    int choice1 = option1();
    if (choice1 == 1)
        attendant_op();
    else if (choice1 == 2)
        vehicle_owner_op();
    else
        exit_program();
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

bool search()
{
    /*
    search for attendant (by email)) and vehicle owner
    */
};

void id_checker(){
    /*search attendant's ID and password */
};

void sign_in() {
    /*
        input: email
        function: read info from file and check if email existed
            if search():input attendant_Id, password 
                    if id_checker(): function attendant_action()
                    else: print wrong pass and renter
            else: print error message and goto option2()(with some modefication)
    */
};

void attendant_action(){
    /*summerry:trasaction history
                (ownwner info / feedback and rating)
                display parking slot info(available, reserved, occupied, expired(passed the time limit)) slots
                display entry and exit time
                display price
                search for vehicle owner(by ID, vehicle name, type) 
    */
};

void register_attendant() {
    /*
        input: name, email;
        generate ID;
        search for attendant using search() 
            if search print "acount already existed, pls sign in" goto sign_in()
            else create password and confirmation
            print successfully registered
    */
};
