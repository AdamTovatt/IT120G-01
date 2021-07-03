// DiceRoll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>; 
#include <windows.h>
#include <thread>

#pragma execution_character_set( "utf-8" )

using namespace std;

int RollDice()
{
    return rand() % 6 + 1;
}

int PlayRound()
{
    int playerFirstRoll = RollDice();
    int playerSecondRoll = RollDice();
    int computerFirstRoll = RollDice();
    int computerSecondRoll = RollDice();

    cout << "Du rullar t�rningen... \n" << playerFirstRoll << "\n";
    this_thread::sleep_for(1000ms);
    cout << "Du rullar t�rningen igen... \n" << playerSecondRoll << "\n";
    this_thread::sleep_for(1000ms);
    cout << "Datorn rullar t�rningen... \n" << computerFirstRoll << "\n";
    this_thread::sleep_for(1000ms);
    cout << "Datorn rullar t�rningen igen... \n" << computerSecondRoll << "\n";
    this_thread::sleep_for(1000ms);

    int playerGreatestRoll = max(playerFirstRoll, playerSecondRoll);
    int computerGreatestRoll = max(computerFirstRoll, computerSecondRoll);

    cout << "\nDin b�sta t�rning blev " << playerGreatestRoll << "\n";
    cout << "Datorns b�sta t�rning blev " << computerGreatestRoll << "\n";

    if (playerGreatestRoll == computerGreatestRoll)
        return 0;

    if (playerGreatestRoll > computerGreatestRoll)
        return 1;

    return 2;
}

int main()
{
    SetConsoleOutputCP(65001);
    srand(time(0));

    PlayRound();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
