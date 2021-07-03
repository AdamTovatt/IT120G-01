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

int PlayMatch()
{
	int playerRounds = 0;
	int computerRounds = 0;

	while (playerRounds < 2 && computerRounds < 2)
	{
		int roundResult = PlayRound();
		cout << "\n";
		if (roundResult == 0)
		{
			cout << "Det blev oavgjort, ingen f�r po�ng och rundan spelas om\n";
		}
		else if (roundResult == 1)
		{
			cout << "Du vann den h�r rundan!\n";
			playerRounds++;
		}
		else if (roundResult == 2)
		{
			cout << "Datorn vann den h�r rundan\n";
			computerRounds++;
		}

		if (playerRounds < 2 && computerRounds < 2)
		{
			cout << "\n(Tryck p� enter f�r att spela n�sta runda)\n";
			getchar();
		}
	}

	if (playerRounds == 2)
	{
		cout << "Grattis, du har vunnit matchen!";
		return 1;
	}

	cout << "Datorn vann tyv�rr matchen";
	return 2;
}

int TakeIntInput(string promt, int min, int max)
{
	int input;
	cin >> input;

	while (!cin || input < min || input > max)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input;
	}

	return input;
}

int accountBalance = 0;

int main()
{
	SetConsoleOutputCP(65001);
	srand(time(0));

	cout << "V�lj ett alternativ genom att skriva siffran f�r alternativet:\n";
	cout << "1. Spela en match\n";
	cout << "2. S�tt in pengar\n";

	if (TakeIntInput("", 1, 2) == 1)
	{
		cout << "spela en match";
	}
	else
	{
		cout << "s�tt in pengar";
	}

	PlayMatch();
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
