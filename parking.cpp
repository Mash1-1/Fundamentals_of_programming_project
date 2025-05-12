#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int tryal = 0;

struct date{
    int day, month, year;
};

struct attendant_info{
    string name;
    int attendant_id, contact_info;
};

struct vehicle_owner {
    
    string name;
    int owner_id, vehicle_num, owner_phone_num;
};

struct parking_slot {
    string slot_id, vehicle_type, status;
    double price;
    struct vehicle_owner;
};

struct transaction {
    
};

 vector <attendant_info> attendant; 

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
    cout << "Have you already Registered in the system ? " << endl;
    cout << "1. Yes (Sign in): " << endl;
    cout << "2. No (Register): " << endl;
    cout << "Your Choice: ";
b:
    cin >> choice;
    if (cin.fail())
    {
        err();
    }
};

void exit_program() {
    cout << "Exiting the program; have a nice day!" << endl;
    exit(0);
};

void attendant_op()
{
    int choice2 = option2();
    string name;
    int attendant_id, contact_info;

    switch (choice2)
    {
        case 1:
        cout << "Enter name: ";
        cin >> name;
        break;

    default:
        break;
    }
};

void vehicle_owner_op() {};

int main()
{
    int choice1 = option1();
    if (choice1 == 1) attendant_op();
    else if (choice1 == 2) vehicle_owner_op();
    else exit_program();
}
