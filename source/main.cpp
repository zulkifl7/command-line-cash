#include <iostream>
#include <windows.h>
#include <limits>  // Include for numeric_limits
#include <fstream> // to use file handling
using namespace std;

//! -- All Function Declaration Goes here

// Login Screen - 1
int loginScreen(int from);

// Home Screen - 2
int homeScreen(int from);

// create new account - 3
int createNewAccount(int from);

// Check Balance - 4
int balanceInquiry(int from);

// deposite cash - 5
int depositeCash(int from);

// fund transfer - 6
int fundTransfer(int from);

// transaction history - 7
int transactionHistory(int from);

// account deactivation - 8
int accountDeactivation(int from);

// Home Screen Components
int primaryOption(); // To display the options in the home screen

// Login screen components
string takePassword(); // function to take password without exposing
int verifyLogin();     // to verify username and password are correct
int quitContinue();    // function for asking user if they want to continue or quit

// logo print
void logoPrint();

//! -- Main Function

//? main - 0
int main()
{
    system("cls"); // cearing the cmd for a clean look
    logoPrint();
    loginScreen(0);

    return 0;
}

//! -- All other function initializations goes here

void logoPrint()
{
    string fileName = "./logo.txt";
    string line = "";
    ifstream inFile;

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "Welcome to Command-Line Cash!" << endl;
    }
    inFile.close();
}

//? Login Screen - 1
int loginScreen(int from)
{
    // system("cls"); // clear the screen

    // checking if retured value is 0
    // if it is not 0 telling error message and
    // asking username and password again
    int verifyLoginHold = 1;

    while (verifyLoginHold != 0)
    {
        // if the user is rederected to login page from the home screen using logout button
        // before asking to login, asking him if we want to continue or exit.
        if (from == 2)
        {
            int quitCon = 2;

            while (true)
            {
                quitCon = quitContinue();
                // Discard a part of input beign in the buffer including newline
                // in order to this to work we have to include <limits> header file
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (quitCon == 0 || quitCon == 1)
                {
                    break;
                }
            }
            if (quitCon == 1)
            {
                break;
            }
        }

        // checking the value returned from the verification and
        // sending to homescreen or asking username password again
        verifyLoginHold = verifyLogin();
        if (verifyLoginHold == 0)
        {
            homeScreen(1);
        }
        else
        {
            cout << "Your username or Password is incorrect!" << endl;
        }
        from = 0;
    }

    return 1;
}
//* Login screen Components
// function for asking user if they want to continue or quit
int quitContinue()
{
    // taking character input from user
    char quitCon;
    cout << "Do you want to continue? (C - Continue/ Q - Quit) - ";
    cin >> quitCon;
    // if user input is c or C return 0
    if (quitCon == 'c' || quitCon == 'C')
    {
        return 0;
    }
    // if user input is q or Q return 1
    else if (quitCon == 'q' || quitCon == 'Q')
    {
        return 1;
    }
    // anything else will return 2
    else
    {
        return 2;
    }
}

string takePassword()
{
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    // Create a restore point Mode
    // is know 503
    GetConsoleMode(hStdInput, &mode);

    // Enable echo input
    // set to 499
    SetConsoleMode(
        hStdInput,
        mode & (~ENABLE_ECHO_INPUT));

    // Take input
    string ipt;
    cout << "Enter Password - ";
    getline(cin, ipt);

    // Otherwise next cout will print
    // into the same line
    cout << endl;

    // Restore the mode
    SetConsoleMode(hStdInput, mode);

    return ipt;
}

// to take username and password from user and
// verify if username and password are correct

int verifyLogin()
{
    // fixed username and password
    static string username = "group6", password = "group6@123";
    string gotUsername, gotPassword;

    // getting username from user

    cout << "Enter username - ";
    getline(cin, gotUsername);
    // getting password from user
    gotPassword = takePassword();

    // verifying if the username and password is correct
    if (username == gotUsername && password == gotPassword)
    {
        // if usrname and password is correct returning 0
        return 0;
    }
    else
    {
        // if it is wrong returning 1
        return 1;
    }
}
//? Home Screen - 2
int homeScreen(int from)
{
    system("cls");
    // Primary operation will be repeated until user enters 7 to logout

    int primaryOptionHold = 0;
    do
    {
        // clearing the screen
        system("cls");
        primaryOptionHold = primaryOption();
        if (primaryOptionHold == 1)
        {
            createNewAccount(2);
        }
        else if (primaryOptionHold == 2)
        {
            balanceInquiry(2);
        }
        else if (primaryOptionHold == 3)
        {
            depositeCash(2);
        }
        else if (primaryOptionHold == 4)
        {
            fundTransfer(2);
        }
        else if (primaryOptionHold == 5)
        {
            transactionHistory(2);
        }
        else if (primaryOptionHold == 6)
        {
            accountDeactivation(2);
        }
        else if (primaryOptionHold == 7)
        {
            loginScreen(2);
        }
        else
        {
            cout << "Invalid input!!";
        }

    } while (primaryOptionHold != 7);

    return 2;
}

//* Home Screen Components

// this function will display the options user have
// and get input from user! and return that option
int primaryOption()
{
    int primaryOptions = 0;
    cout << "Enter the operation you want to perform - ";
    cin >> primaryOptions;

    return primaryOptions;
}

//? create new account - 3
// Function to create a new user account within the system
int createNewAccount(int from)
{
    // Prompt user for necessary information (e.g., username, password, security questions)
    // Validate user input to ensure secure password creation
    // Store user information in a secure data store (e.g., database)
    // Handle potential errors during account creation (e.g., username already exists)
    cout << "New account created successfully!" << endl;
    return 3;
}

//? Check Balance - 4
// Function to retrieve the current balance associated with the logged-in account
int balanceInquiry(int from)
{
    // Access account data based on logged-in user credentials
    // Retrieve and display the current balance
    cout << "Your current balance is: "; // << /* Get balance from data store */ << endl;
    return 4;
}

//? deposite cash - 5
// Function to allow depositing cash into the account
int depositeCash(int from)
{
    // Prompt user for deposit amount
    // Validate deposit amount (e.g., non-negative value)
    // Update account balance in the data store based on deposit amount
    cout << "Deposited "; // <<  Get deposit amount from user  << " successfully!" << endl;
    return 5;
}

//? fund transfer - 6
// Function to enable transferring funds to another account
int fundTransfer(int from)
{
    // Prompt user for recipient account information (e.g., username or account number)
    // Validate recipient information
    // Prompt user for transfer amount
    // Validate transfer amount (e.g., sufficient balance)
    // Update account balances (sender and recipient) in the data store
    cout << "Successfully transferred "; // << /* Get transfer amount from user */ << " to recipient." << endl;
    return 6;
}

//? transaction history - 7
// Function to display past transactions associated with the account
int transactionHistory(int from)
{
    // Access transaction history data based on logged-in user credentials
    // Display a formatted list of past transactions (e.g., date, amount, type)
    // Allow user to navigate through transaction history (optional)
    cout << "Displaying transaction history..." << endl;
    // Implement logic to display transactions
    return 7;
}

//? account deactivation - 8
// Function to permanently deactivate the logged-in user account
int accountDeactivation(int from)
{
    // Prompt user for confirmation to deactivate
    // Provide clear information about the irreversible nature of deactivation
    // Deactivate the account by removing or marking it as inactive in the data store
    cout << "Your account has been deactivated." << endl;
    return 8;
}
