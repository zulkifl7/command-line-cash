#include <iostream>
using namespace std;

//* Login Screen Compinents

//? Login Screen - 1
int loginScreen(int from)
{
    if (true)
    {
        homeScreen(1);
    }
}

//* Home Screen Components
int primaryOption()
{
    int primaryOptions = 0;
    cout << "Enter the operation you want to perform - ";
    cin >> primaryOptions;

    return primaryOptions;
}
//? Home Screen - 2
int homeScreen(int from)
{
    // Primary operation will be repeated until user enters 7 to logout
    while ((primaryOption()) != 7)
    {
        system("cls");
    }
    return 0;
}

//? main - 0
int main()
{
    system("cls"); // cearing the cmd for a clean look
    loginScreen(0);

    return 0;
}