#include <iostream>
#include <windows.h>
#include <limits>    // Include for numeric_limits
#include <fstream>   // to use file handling
#include <iomanip>   // to manipulate onput and output for a better looking (Ex: tables)
#include <vector>    // to use vector data structure
#include <sstream>   // to use flexible string data retreival and searches on data reciewing from the file
#include <algorithm> // to use remove_if() function
using namespace std;

//! -- All Function Declaration Goes here
struct UserData
{
    string firstName;
    string lastName;
    string dateOfBirth;
    string nationalIdNumber;
    string username;
    string password;
};

// a sub main function for development and testing perposes
void subMain();

// Login Screen - 1
int loginScreen(int from);

// Home Screen - 2
int homeScreen(int from);

// create new account - 3
int createNewAccount(int from);
// create new account components
bool isStrongPassword(const string &password);
// Function to check if username exists in the file
bool usernameExists(const string &username);
// Read user data from file
vector<UserData> readUserDataFromFile();
// Check Balance - 4
int balanceInquiry(int from);

// deposite cash - 5
int depositeCash(int from);

// withdraw cash - 6
int withdrawCash(int from);

// fund transfer - 7
int fundTransfer(int from);

// transaction history - 8
int transactionHistory(int from);

// account deactivation - 9
int accountDeactivation(int from);

// Login screen components
string takePassword(); // function to take password without exposing
int verifyLogin();     // to verify username and password are correct
int quitContinue();    // function for asking user if they want to continue or quit

// logo print
void logoPrint();

// Home Screen Components
void optionDisplay(); // To display the options in the home screen
int primaryOption();  // To taek user input of which option they want to select

//! -- Main Function

//? main - 0
int main()
{
    subMain();
    // Access user data using a loop or by index
    // vector<UserData> users = readUserDataFromFile();
    // for (const UserData &user : users)
    // {
    //     cout << "First Name: " << user.firstName << endl;
    //     cout << "Last Name: " << user.lastName << endl;
    //     // ... and so on for other fields
    //     cout << endl;
    // }
    return 0;
}
// Using this submain for all the real app callings.
// so in the developing phase we can just call this function if we want to
// run the actual program and without calling this we can just call other functions to test
// a perticular part in the code
void subMain()
{
    system("cls"); // cearing the cmd for a clean look
    logoPrint();
    loginScreen(0);
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
        // to diplay the avalable options
        optionDisplay();
        cout << endl;
        primaryOptionHold = primaryOption();
        // calling curespoding function acording to the user's call
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
            withdrawCash(2);
        }
        else if (primaryOptionHold == 5)
        {
            fundTransfer(2);
        }
        else if (primaryOptionHold == 6)
        {
            transactionHistory(2);
        }
        else if (primaryOptionHold == 7)
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

    } while (primaryOptionHold != 8);

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

void optionDisplay()
{
    // number of options
    int numOfOpt = 8; // using a variable for easy future updates if needed
    // using an array so i could use a loop for displaying the options
    string options[numOfOpt] = {"Create new Account",
                                "Balance Inquiry",
                                "Cash Deposite",
                                "Cash Withdraw",
                                "Fund Transfer",
                                "Transaction History",
                                "Account Deactivation",
                                "Logout"};
    // using <iomanip> input and output manipulation builtin library for a table like output
    // cout << setw(20) << left << "Option Number" << setw(50) << left << "Option Description" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "Option Number" << setw(2) << left << "|" << setw(23) << left << "Options"
         << setw(40) << "|" << endl;
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
    for (int i = 0; i < numOfOpt; i++)
    {
        cout << setw(2) << left << "|" << setw(15) << right << i + 1 << setw(2) << left << "|" << setw(23) << left << options[i]
             << setw(2) << left << "|" << endl;
    }
    cout << setw(2) << left << "|" << setw(15) << right << "--------------" << setw(2) << left << "|" << setw(23) << left << "--------------"
         << setw(40) << "|" << endl;
}

//? create new account - 3
// Function to create a new user account within the system
int createNewAccount(int from)
{
    // Prompt user for necessary information
    // firstName - 0, lastName - 1, dateOfBirth - 2, nationalIdNumber - 3, userName - 4, password - 5
    int numOfData = 6; // using a variable in case if we need another field we can just incriment one and add that field to keys and work
    // To use a for loop to take the inputs
    string keys[numOfData] = {"First Name", "Last Name", "Date Of Birth [yyy-mm-dd]", "National Id Number", "Username", "Password"};
    // to store the values user have entered
    string values[numOfData];

    // Discard a part of input beign in the buffer including newline
    // in order to this to work we have to include <limits> header file
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Get user input for each field upto national id number
    for (int i = 0; i < numOfData - 2; i++)
    {
        cout << "Enter your " << keys[i] << " - ";
        getline(cin, values[i]);
    }
    // using a temperory username to take username and check if it's already exist
    string username;
    cout << "Enter your Username: ";
    getline(cin, username); // Username index
    while (true)
    {
        // Check if username already exists
        if (usernameExists(username))
        {
            cout << "Username already exists. Please choose another username." << endl;
            cout << "Enter your Username: ";
            getline(cin, username); // Username index
        }
        else
        {
            values[4] = username;
            break;
        }
    }

    // Taking separate input and Validate user input to ensure secure password creation
    // temporarily storing password for checking
    string password, confirmPassword;
    // Loop to get a strong and matching 2 passwords password from the user
    do
    {
        // Prompt for password and get user input
        cout << "Enter your Password (Must be at least 8 characters and include uppercase, lowercase, digits, and special characters) - ";
        getline(cin, password);

        // Validate password strength
        while (!isStrongPassword(password))
        {
            cout << "Password is weak. Please ensure it meets the complexity requirements." << endl;
            // Re-prompt for password if it's weak
            cout << "Enter your Password (Must be at least 8 characters and include uppercase, lowercase, digits, and special characters) - ";
            getline(cin, password);
        }
        // Prompt for password confirmation
        cout << "Confirm your Password: ";
        getline(cin, confirmPassword);
        if (confirmPassword != password)
        {
            cout << "Passwords doesn't match!!" << endl;
        }
        else
        {
            values[numOfData - 1] = password;
        }
    } while (confirmPassword != password); // Repeat until passwords match

    // Store user information in a file

    // Open "accounts.txt" in append mode
    ofstream file("accounts.txt", ios::app);
    // creating a new file for user to store his transaction
    ofstream userTransactionFile("accounts/" + values[4] + ".txt");
    userTransactionFile.close();
    // Check if file open was successful
    if (!file.is_open())
    {
        // sending an error message
        cerr << "Error opening file!" << endl;
        return 1; // Indicate error
    }
    // Write user information to the file
    for (int i = 0; i < numOfData; i++)
    {
        file << keys[i] << " - " << values[i] << "\n";
    }
    // adding a new line to maek keep up a gap betwwen datas
    file << "\n";

    // Handle potential errors during account creation (e.g., username already exists)
    cout << "New account created successfully!" << endl;

    // Close the file
    file.close();
    return 3;
}

//* create new account Components

// Function to check password strength
// making it a constant to prevent modifications
// passwing the address of password directly inside to
// use the actual password to prevent errors while copying the string
bool isStrongPassword(const string &password)
{
    int hasUpper = 0;
    int hasLower = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    // Check for minimum length (adjust as needed)
    if (password.length() < 8)
    {
        return false;
    }

    // Check for character types
    for (char c : password) // for every (Char c) in password
    {
        if (isupper(c))
        {
            hasUpper = 1;
        }
        else if (islower(c))
        {
            hasLower = 1;
        }
        else if (isdigit(c))
        {
            hasDigit = 1;
        }
        else if (ispunct(c))
        {
            hasSpecial = 1;
        }
    }

    // Ensure password meets complexity requirements (adjust as needed)
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
// Function to check if username exists in the file
bool usernameExists(const string &username)
{
    // Open the accounts.txt file in read mode
    ifstream file("accounts.txt");
    // Check if the file opened successfully
    if (file.is_open())
    {
        string line;
        // Loop through each line in the file
        while (getline(file, line))
        {
            // Search for the line containing "Username"
            if (line.find("Username") != string ::npos)
            {
                // Extract the username value after the "-" delimiter
                string value = line.substr(line.find("-") + 2);
                // Compare the provided username with the extracted value
                if (username == value)
                {
                    // Username found, close the file and return true
                    file.close();
                    return true;
                }
            }
        }
        // Username not found in the file, close the file and return false
        file.close(); // Close the file even if username not found

        return false;
    }
    else
    {
        // Error opening the file, indicate error and return false
        cerr << "Error opening file accounts.txt!" << endl;
        return false;
    }
}

// Read user data from file
vector<UserData> readUserDataFromFile()
{
    // Open the "accounts.txt" file in read mode
    ifstream file("accounts.txt");
    vector<UserData> users; // Stores user data extracted from the file

    // Check if the file opened successfully
    if (file.is_open())
    {
        string line;
        int lineNumber = 0; // Track line number for potential error handling

        // Read lines until end of file (including the empty line)
        UserData user;
        while (getline(file, line))
        {
            lineNumber++;
            // if there is an empty line one user's data is over
            // so add that user data to users and reset user
            // and Skip empty lines between user records
            if (line.empty())
            {
                users.push_back(user); // Add user data to the vector
                user = UserData();     // Reset user struch for the next user
                continue;              // skiping the empty line
            }
            // Split the line based on the delimiter "-"
            string value = line.substr(line.find("-") + 2); // Extract data after - sign

            // Assign data to user struct fields based on line number (modulo 7)
            switch (lineNumber % 7)
            {
            case 1:
                user.firstName = value;
                break;
            case 2:
                user.lastName = value;
                break;
            case 3:
                // Handle potential date format issue
                user.dateOfBirth = value;
                // You can add validation or correction logic here if needed
                break;
            case 4:
                user.nationalIdNumber = value;
                break;
            case 5:
                user.username = value;
                break;
            case 6:
                user.password = value;
                break;

            default:
                // Handle unexpected data (optional)
                cerr << "Warning: Unexpected data on line " << lineNumber << endl;
                break;
            }
        }
        // forthe last user record (if not the empty line is missed)
        if (!user.firstName.empty())
        {
            users.push_back(user);
        }
        file.close();
    }
    else
    {
        cerr << "Error opening file!" << endl;
    }

    return users;
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
    int numOfData = 4;
    string keys[numOfData] = {"username", "purpose", "ammount", "type"};
    string values[numOfData];
    values[3] = "deposite";
    string username, ConfirmUsername;
    do
    {
        do
        {
            // Discard a part of input beign in the buffer including newline
            // in order to this to work we have to include <limits> header file
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Prompt for username and get user input
            cout << "Enter account username to deposite - ";
            getline(cin, username);
            // checking if the username is a valid username before depositing the amount
            if (usernameExists(username))
            {
                break;
            }
            else
            {
                // if the user name does not exist before asking to enter the username once again
                // asking user if you want to create a new account
                char newAcc;
                cout << "This username does not exist!" << endl;
                while (true)
                {
                    cout << "Do you want to create a new account? (Y/N) - ";
                    cin >> newAcc;

                    if (newAcc == 'y' || newAcc == 'Y')
                    {
                        createNewAccount(5);
                        break;
                    }
                    else if (newAcc == 'n' || newAcc == 'N')
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid Input!" << endl;
                    }
                }
            }

        } while (true);

        // Prompt for password confirmation
        cout << "Confirm your Username -  ";
        getline(cin, ConfirmUsername);
        if (ConfirmUsername != username)
        {
            cout << "Username doesn't match!!" << endl;
        }
        else
        {
            values[0] = username;
        }
    } while (username != ConfirmUsername); // Repeat until username match

    cout << "Enter the purpose of the deposite - ";
    getline(cin, values[1]);
    char confirm;
    do
    {
        // Discard a part of input beign in the buffer including newline
        // in order to this to work we have to include <limits> header file
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the ammount you want to deposite - ";
        getline(cin, values[2]);

        cout << "Confirm if the ammount is correct (Y/N) - ";
        cin >> confirm;
        float depositeAmount;
        stringstream buffer(values[2]);
        buffer >> depositeAmount;
        if (depositeAmount < 0)
        {
            cout << "Invalid deposite ammount!!" << endl;
        }
        if (confirm == 'y' || confirm == 'Y')
        {
            break;
        }
        else if (confirm == 'n' || confirm == 'N')
        {
        }
        else
        {
            cout << "Invalid Input!!" << endl;
        }
    } while (true);

    ofstream depositeFile("accounts/" + values[0] + ".txt", ios::app);

    if (depositeFile.is_open())
    {
        for (int i = 0; i < numOfData; i++)
        {
            depositeFile << keys[i] << " - " << values[i] << endl;
        }
        depositeFile << endl;
    }
    // Prompt user for deposit amount
    // Validate deposit amount (e.g., non-negative value)
    // Update account balance in the data store based on deposit amount
    cout << "Cash Deposited!"; // <<  Get deposit amount from user  << " successfully!" << endl;
    return 5;
}

//? Withdraw cash - 6
int withdrawCash(int from)
{
    return 6;
}

//? fund transfer - 7
// Function to enable transferring funds to another account
int fundTransfer(int from)
{
    // Prompt user for recipient account information (e.g., username or account number)
    // Validate recipient information
    // Prompt user for transfer amount
    // Validate transfer amount (e.g., sufficient balance)
    // Update account balances (sender and recipient) in the data store
    cout << "Successfully transferred "; // << /* Get transfer amount from user */ << " to recipient." << endl;
    return 7;
}

//? transaction history - 8
// Function to display past transactions associated with the account
int transactionHistory(int from)
{
    // Access transaction history data based on logged-in user credentials
    // Display a formatted list of past transactions (e.g., date, amount, type)
    // Allow user to navigate through transaction history (optional)
    cout << "Displaying transaction history..." << endl;
    // Implement logic to display transactions
    return 8;
}

//? account deactivation - 9
// Function to permanently deactivate the logged-in user account
int accountDeactivation(int from)
{
    // Prompt user for confirmation to deactivate
    // Provide clear information about the irreversible nature of deactivation
    // Deactivate the account by removing or marking it as inactive in the data store
    cout << "Your account has been deactivated." << endl;
    return 9;
}
