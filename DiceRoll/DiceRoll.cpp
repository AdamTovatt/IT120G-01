#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>

#pragma execution_character_set( "utf-8" )

using namespace std;

int RollDice() //den h�r funktionen "rullar t�rningen"
{
	return rand() % 6 + 1;
}

int PlayRound() //den h�r funktionen spelar en runda
{
	int playerFirstRoll = RollDice(); //alla t�rningsrullningar
	int playerSecondRoll = RollDice();
	int computerFirstRoll = RollDice();
	int computerSecondRoll = RollDice();

	cout << "Du rullar t�rningen... \n" << playerFirstRoll << "\n"; //skriver ut resultatet av rullningar
	this_thread::sleep_for(500ms); //v�ntar lite mellan s� det ska bli lite mer sp�nnande
	cout << "Du rullar t�rningen igen... \n" << playerSecondRoll << "\n";
	this_thread::sleep_for(500ms);
	cout << "Datorn rullar t�rningen... \n" << computerFirstRoll << "\n";
	this_thread::sleep_for(500ms);
	cout << "Datorn rullar t�rningen igen... \n" << computerSecondRoll << "\n";
	this_thread::sleep_for(500ms);

	int playerGreatestRoll = max(playerFirstRoll, playerSecondRoll); //hittar det st�rsta v�rdet bland spelarens t�rningsrullningar
	int computerGreatestRoll = max(computerFirstRoll, computerSecondRoll); //samma som f�reg�ende rad fast f�r datorn

	cout << "\nDin b�sta t�rning blev " << playerGreatestRoll << "\n"; //skriver vad som h�nt lite
	cout << "Datorns b�sta t�rning blev " << computerGreatestRoll << "\n";

	if (playerGreatestRoll == computerGreatestRoll) //h�r blev det lika
		return 0;

	if (playerGreatestRoll > computerGreatestRoll) //h�r vann spelaren
		return 1;

	return 2; //h�r vann datorn
}

int PlayMatch() //funktion som spelar en match
{
	cin.ignore(100, '\n'); //ignorerar eventuella felaktiga tidigare inputs

	int playerRounds = 0; //hur m�nga rundor spelaren har vunnit
	int computerRounds = 0; //hur m�nga rundor datorn vunnit

	while (playerRounds < 2 && computerRounds < 2) //vi ska vara i loopen s� l�nge ingen vunnit tv� eller fler rundor
	{
		int roundResult = PlayRound(); //spelar en runda f�r att f� resultatet
		cout << "\n";
		if (roundResult == 0) //h�r blev det oavgjort
		{
			cout << "Det blev oavgjort, ingen f�r po�ng och rundan spelas om\n";
		}
		else if (roundResult == 1) //h�r vann man rundan
		{
			cout << "Du vann den h�r rundan!\n";
			playerRounds++;
		}
		else if (roundResult == 2) //h�r vann datorn rundan
		{
			cout << "Datorn vann den h�r rundan\n";
			computerRounds++;
		}

		cout << "Du har vunnit " << playerRounds << ((playerRounds != 1) ? " rundor\n" : " runda\n"); //h�r skriver vi ut hur m�nga rundor vardera spelare har vunnit
		cout << "Datorn har vunnit " << computerRounds << ((computerRounds != 1) ? " rundor\n" : " runda\n");

		if (playerRounds < 2 && computerRounds < 2) //bara om ingen vunnit matchen ska vi g�ra det som �r i ifsatsen
		{ //ingen har vunnit matchen, d� ska vi v�nta p� input f�r att starta n�sta runda s� att anv�ndaren hinner l�sa vad som h�nder
			cout << "\n(Tryck p� enter f�r att spela n�sta runda)\n";
			cin.get();
		}
	}

	if (playerRounds == 2) //h�r vann man matchen
	{
		cout << "Grattis, du har vunnit matchen!\n";
		return 1;
	}

	cout << "Datorn vann tyv�rr matchen\n"; //h�r har datorn vunnit matchen
	return 2;
}

int TakeIntInput(string promt, int min, int max) //detta �r en funktion f�r att ta indata fr�n anv�ndaren som s�kerst�lls till att vara av typen int och inte mer �n max och inte mindre �n min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland �r det tomt men d� skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" �r false om tex en bokstav skrevs in. Vi kollar ocks� s� att v�rdet �r inom vad det f�r vara
	{
		cin.clear(); //om vi kommer hit kan det vara s� att ett felaktigt tecken dvs typ en bokstav skrivits in s� vi �terst�ller och rensar cin
		cin.ignore(100, '\n'); //ignorerar det felaktiga tecken
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int accountBalance = 0; //variabel som anv�nds f�r att h�lla koll p� hur mycket pengar man har p� sitt konto
int totalEarnings = 0; //hur mycket pengar man tj�nat/f�rlorat

int main() //mainfunktionen, h�r b�rjar programmet
{
	SetConsoleOutputCP(65001); //g�r s� det g�r att skriva till konsolen antar jag (den h�r raden var h�r fr�n b�rjan n�r jag startade visual studio)
	srand(time(0)); //initialiserar random

	bool keepRunning = true; //avg�r om programmet ska g� tillbaks till huvudmenyn eller avslutas

	while (keepRunning)
	{
		cout << "------------V�lkommen------------\n"; //huvudmenyn skrivs ut
		cout << "H�r kan du spela bort dina pengar\n";
		cout << "---------------------------------\n";
		cout << "Du har " << accountBalance << "kr p� kontot\n\n";
		cout << "V�lj ett alternativ genom att skriva siffran f�r alternativet:\n";
		cout << "1. Spela en match\n";
		cout << "2. S�tt in pengar\n";
		cout << "3. Avsluta programmet\n";

		int choiceInput = TakeIntInput("", 1, 3); //h�r f�r man v�lja ett alternativ i huvudmenyn
		if (choiceInput == 1) //h�r har man d� valt att spela en match
		{
			cout << "Hur mycket pengar vill du satsa?\n";

			int wagerOptions[3] = { 100, 300, 500 }; //detta �r de olika m�ngderna man kan satsa
			for (int i = 0; i < sizeof(wagerOptions) / sizeof(*wagerOptions); i++) //loopar igenom arrayen med m�ngderna man kan satsa och skriver ut dem som alternativ
				cout << i + 1 << ". " << wagerOptions[i] << "kr\n";

			int wager = wagerOptions[TakeIntInput("V�lj ett alternativ genom att skriva siffran f�r alternativet:\n", 1, 3) - 1]; //tar input f�r hur mycket man vill satsa

			if (wager > accountBalance) //man kan inte satsa mer pengar �n man har
			{
				cout << "Du har inte s� mycket pengar som du f�rs�kte satsa.\nDu kommer tas tillbaka till huvudmenyn s� att du kan s�tta in mer pengar\n";
			}
			else
			{
				cout << "Du har valt att satsa " << wager << "kr p� den h�r matchen\n\n";

				accountBalance -= wager; //drar de pengar man satsat fr�n kontot
				int matchResult = PlayMatch(); //spelar en match

				if (matchResult == 1) //h�r vann man matchen
				{
					cout << "Du f�r tillbaka dina satsade pengar (" << wager << "kr) och f�r lika mycket av datorn\n";
					accountBalance += wager * 2; //man f�r tillbaka dubbla det man satsade (eftersom datorn ocks� har satsat lika mycket antar man)
					totalEarnings += wager; //totala vinsten �kas med det man satasade och d�rmed vann
				}
				else //h�r f�rlorade man matchen
				{
					cout << "Dator vinner pengarna som satsats p� matchen\n"; //vi har redan dragit pengar fr�n kontot till poolen av pengar som spelats om s� vi beh�ver inte g�ra n�got med kontot h�r
					totalEarnings -= wager; //h�r minskas den totala vinsten med det man f�rlorade
				}

				if (totalEarnings < 0) //h�r skrivs det ut hur mycket man vunnit/f�rlorat totalt
				{
					cout << "Du har f�rlorat " << totalEarnings << "kr totalt\n";
				}
				else
				{
					cout << "Du var vunnit " << totalEarnings << "kr totalt\n";
				}

				cout << "Du har " << accountBalance << "kr p� kontot\n"; //information om hur mycket pengar man har
			} //nu kommer koden g� tillbaks till starten av loopen och d�rmed huvudmenyn
		}
		else if(choiceInput == 2) //h�r har man valt att s�tta in pengar
		{
			accountBalance += TakeIntInput("Ange hur mycket pengar du vill s�tta in mellan (minst 100kr och max 5000kr)\n", 100, 5000);	//vi l�gger till s� mycket pengar till kontot som anv�ndaren valde att s�tta in		
			cout << "Dina pengar f�rs �ver...\n|";
			for (int i = 0; i < 50; i++) //h�r �r en loop som �r till f�r att rita ut en liten "loading bar"
			{
				if (rand() % 2 == 1) //det �r 50% chans att den v�ntar 70ms ist�llet f�r 20ms s� att det ska vara lite slumpm�ssigt hur l�ng tid varje del av laddningen tar (extremt viktig detalj i programmet, det skulle praktiskt taget vara oanv�ndbart annars)
				{
					this_thread::sleep_for(70ms);
				}
				else
				{
					this_thread::sleep_for(20ms);
				}
				cout << "-";
			}
			cout << "|\nDina pengar har nu f�rts �ver\n"; //nu kommer koden g� tillbaks till starten av loopen och d�rmed huvudmenyn
		}
		else //h�r har man valt att st�nga av programmet
		{
			keepRunning = false; //s�tter keepRunning till false och l�ter koden g� tillbaks till b�rjan av loopen som nu kommer avslutas och d�rmed avslutas programmet
		}

		cout << "\n";
	}
}