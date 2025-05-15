#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int tryal = 0;

struct date
{
    int day, month, year;
};

struct attendant_info
{
    string name, email, password;
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

fstream file;

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

bool search(string);

void exit_program()
{
    cout << "Exiting the program; have a nice day!" << endl;
    exit(0);
};

void register_attendant();
void sign_in();

void attendant_op();

void vehicle_owner_op() {
    /*
    prompt user: entering or exiting checker
    file: entered vehicles / exited vehicles
    time tracker for both enter and exit
    if entering goto entering_vehicle()
    else exiting goto exiting_vehicles()
    */
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

void entering_vehicle() {

};

void exiting_vehicles() {

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


void id_checker() {
    /*search attendant's ID and password */
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
                    cout << "Sign in successfully! " << endl;
                    // Take action
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
        goto Y;
    }

    infile.close();
}

void attendant_action() {
    /*summery:trasaction history
                (ownwner info / feedback and rating)
                display parking slot info(available, reserved, occupied, expired(passed the time limit)) slots
                display entry and exit time
                display price
                search for vehicle owner(by ID, vehicle name, type)
    */
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