#include <iostream>
#include <windows.h>
using namespace std;

// -- All Function DEclaration Goes here

// Login Screen - 1
int loginScreen(int from);
// Home Screen - 2
int homeScreen(int from);

// Home Screen Components

int primaryOption(); // To display the options in the home screen

// Login screen components
string takePassword(); // function to take password without exposing
int verifyLogin();     // to verify username and password are correct

// -- Main Function

//? main - 0
int main()
{
    system("cls"); // cearing the cmd for a clean look
    loginScreen(0);

    return 0;
}

// -- All other function initializations goes here

//* Login Screen Compinents

//? Login Screen - 1
int loginScreen(int from)
{
    // checking if retured value is 0
    // if it is not 0 telling error message and
    // asking username and password again
    while (verifyLogin() != 0)
    {
        cout << "Your username or Password is incorrect!" << endl;
    }

    homeScreen(1);

    return 0;
}

//? Home Screen - 2
int homeScreen(int from)
{
    system("cls");
    // Primary operation will be repeated until user enters 7 to logout
    while ((primaryOption()) != 7)
    {
        // clearing the screen
        system("cls");
    }
    return 0;
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

//* Login screen Components
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
        return 0;
    }
    else
    {
        return 1;
    }
}