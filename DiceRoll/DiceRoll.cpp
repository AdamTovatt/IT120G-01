#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>

#pragma execution_character_set( "utf-8" )

using namespace std;

int RollDice() //den här funktionen "rullar tärningen"
{
	return rand() % 6 + 1;
}

int PlayRound() //den här funktionen spelar en runda
{
	int playerFirstRoll = RollDice(); //alla tärningsrullningar
	int playerSecondRoll = RollDice();
	int computerFirstRoll = RollDice();
	int computerSecondRoll = RollDice();

	cout << "Du rullar tärningen... \n" << playerFirstRoll << "\n"; //skriver ut resultatet av rullningar
	this_thread::sleep_for(500ms); //väntar lite mellan så det ska bli lite mer spännande
	cout << "Du rullar tärningen igen... \n" << playerSecondRoll << "\n";
	this_thread::sleep_for(500ms);
	cout << "Datorn rullar tärningen... \n" << computerFirstRoll << "\n";
	this_thread::sleep_for(500ms);
	cout << "Datorn rullar tärningen igen... \n" << computerSecondRoll << "\n";
	this_thread::sleep_for(500ms);

	int playerGreatestRoll = max(playerFirstRoll, playerSecondRoll); //hittar det största värdet bland spelarens tärningsrullningar
	int computerGreatestRoll = max(computerFirstRoll, computerSecondRoll); //samma som föregående rad fast för datorn

	cout << "\nDin bästa tärning blev " << playerGreatestRoll << "\n"; //skriver vad som hänt lite
	cout << "Datorns bästa tärning blev " << computerGreatestRoll << "\n";

	if (playerGreatestRoll == computerGreatestRoll) //här blev det lika
		return 0;

	if (playerGreatestRoll > computerGreatestRoll) //här vann spelaren
		return 1;

	return 2; //här vann datorn
}

int PlayMatch() //funktion som spelar en match
{
	cin.ignore(100, '\n'); //ignorerar eventuella felaktiga tidigare inputs

	int playerRounds = 0; //hur många rundor spelaren har vunnit
	int computerRounds = 0; //hur många rundor datorn vunnit

	while (playerRounds < 2 && computerRounds < 2) //vi ska vara i loopen så länge ingen vunnit två eller fler rundor
	{
		int roundResult = PlayRound(); //spelar en runda för att få resultatet
		cout << "\n";
		if (roundResult == 0) //här blev det oavgjort
		{
			cout << "Det blev oavgjort, ingen får poäng och rundan spelas om\n";
		}
		else if (roundResult == 1) //här vann man rundan
		{
			cout << "Du vann den här rundan!\n";
			playerRounds++;
		}
		else if (roundResult == 2) //här vann datorn rundan
		{
			cout << "Datorn vann den här rundan\n";
			computerRounds++;
		}

		cout << "Du har vunnit " << playerRounds << ((playerRounds != 1) ? " rundor\n" : " runda\n"); //här skriver vi ut hur många rundor vardera spelare har vunnit
		cout << "Datorn har vunnit " << computerRounds << ((computerRounds != 1) ? " rundor\n" : " runda\n");

		if (playerRounds < 2 && computerRounds < 2) //bara om ingen vunnit matchen ska vi göra det som är i ifsatsen
		{ //ingen har vunnit matchen, då ska vi vänta på input för att starta nästa runda så att användaren hinner läsa vad som händer
			cout << "\n(Tryck på enter för att spela nästa runda)\n";
			cin.get();
		}
	}

	if (playerRounds == 2) //här vann man matchen
	{
		cout << "Grattis, du har vunnit matchen!\n";
		return 1;
	}

	cout << "Datorn vann tyvärr matchen\n"; //här har datorn vunnit matchen
	return 2;
}

int TakeIntInput(string promt, int min, int max) //detta är en funktion för att ta indata från användaren som säkerställs till att vara av typen int och inte mer än max och inte mindre än min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland är det tomt men då skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" är false om tex en bokstav skrevs in. Vi kollar också så att värdet är inom vad det får vara
	{
		cin.clear(); //om vi kommer hit kan det vara så att ett felaktigt tecken dvs typ en bokstav skrivits in så vi återställer och rensar cin
		cin.ignore(100, '\n'); //ignorerar det felaktiga tecken
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int accountBalance = 0; //variabel som används för att hålla koll på hur mycket pengar man har på sitt konto
int totalEarnings = 0; //hur mycket pengar man tjänat/förlorat

int main() //mainfunktionen, här börjar programmet
{
	SetConsoleOutputCP(65001); //gör så det går att skriva till konsolen antar jag (den här raden var här från början när jag startade visual studio)
	srand(time(0)); //initialiserar random

	bool keepRunning = true; //avgör om programmet ska gå tillbaks till huvudmenyn eller avslutas

	while (keepRunning)
	{
		cout << "------------Välkommen------------\n"; //huvudmenyn skrivs ut
		cout << "Här kan du spela bort dina pengar\n";
		cout << "---------------------------------\n";
		cout << "Du har " << accountBalance << "kr på kontot\n\n";
		cout << "Välj ett alternativ genom att skriva siffran för alternativet:\n";
		cout << "1. Spela en match\n";
		cout << "2. Sätt in pengar\n";
		cout << "3. Avsluta programmet\n";

		int choiceInput = TakeIntInput("", 1, 3); //här får man välja ett alternativ i huvudmenyn
		if (choiceInput == 1) //här har man då valt att spela en match
		{
			cout << "Hur mycket pengar vill du satsa?\n";

			int wagerOptions[3] = { 100, 300, 500 }; //detta är de olika mängderna man kan satsa
			for (int i = 0; i < sizeof(wagerOptions) / sizeof(*wagerOptions); i++) //loopar igenom arrayen med mängderna man kan satsa och skriver ut dem som alternativ
				cout << i + 1 << ". " << wagerOptions[i] << "kr\n";

			int wager = wagerOptions[TakeIntInput("Välj ett alternativ genom att skriva siffran för alternativet:\n", 1, 3) - 1]; //tar input för hur mycket man vill satsa

			if (wager > accountBalance) //man kan inte satsa mer pengar än man har
			{
				cout << "Du har inte så mycket pengar som du försökte satsa.\nDu kommer tas tillbaka till huvudmenyn så att du kan sätta in mer pengar\n";
			}
			else
			{
				cout << "Du har valt att satsa " << wager << "kr på den här matchen\n\n";

				accountBalance -= wager; //drar de pengar man satsat från kontot
				int matchResult = PlayMatch(); //spelar en match

				if (matchResult == 1) //här vann man matchen
				{
					cout << "Du får tillbaka dina satsade pengar (" << wager << "kr) och får lika mycket av datorn\n";
					accountBalance += wager * 2; //man får tillbaka dubbla det man satsade (eftersom datorn också har satsat lika mycket antar man)
					totalEarnings += wager; //totala vinsten ökas med det man satasade och därmed vann
				}
				else //här förlorade man matchen
				{
					cout << "Dator vinner pengarna som satsats på matchen\n"; //vi har redan dragit pengar från kontot till poolen av pengar som spelats om så vi behöver inte göra något med kontot här
					totalEarnings -= wager; //här minskas den totala vinsten med det man förlorade
				}

				if (totalEarnings < 0) //här skrivs det ut hur mycket man vunnit/förlorat totalt
				{
					cout << "Du har förlorat " << totalEarnings << "kr totalt\n";
				}
				else
				{
					cout << "Du var vunnit " << totalEarnings << "kr totalt\n";
				}

				cout << "Du har " << accountBalance << "kr på kontot\n"; //information om hur mycket pengar man har
			} //nu kommer koden gå tillbaks till starten av loopen och därmed huvudmenyn
		}
		else if(choiceInput == 2) //här har man valt att sätta in pengar
		{
			accountBalance += TakeIntInput("Ange hur mycket pengar du vill sätta in mellan (minst 100kr och max 5000kr)\n", 100, 5000);	//vi lägger till så mycket pengar till kontot som användaren valde att sätta in		
			cout << "Dina pengar förs över...\n|";
			for (int i = 0; i < 50; i++) //här är en loop som är till för att rita ut en liten "loading bar"
			{
				if (rand() % 2 == 1) //det är 50% chans att den väntar 70ms istället för 20ms så att det ska vara lite slumpmässigt hur lång tid varje del av laddningen tar (extremt viktig detalj i programmet, det skulle praktiskt taget vara oanvändbart annars)
				{
					this_thread::sleep_for(70ms);
				}
				else
				{
					this_thread::sleep_for(20ms);
				}
				cout << "-";
			}
			cout << "|\nDina pengar har nu förts över\n"; //nu kommer koden gå tillbaks till starten av loopen och därmed huvudmenyn
		}
		else //här har man valt att stänga av programmet
		{
			keepRunning = false; //sätter keepRunning till false och låter koden gå tillbaks till början av loopen som nu kommer avslutas och därmed avslutas programmet
		}

		cout << "\n";
	}
}