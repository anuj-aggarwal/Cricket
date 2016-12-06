#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

#include "Team.h"
#include "Result.h"
#include "Ball.h"
#include "Input.h"
#include "Database.h"
#include "Help.h"
#include "Game.h"

using namespace std;


int displayMenu();


const string fileName = "../Cricket/Details.txt";
const vector<string> helpFileNames = { "../Cricket/Help/Help.txt", "../Cricket/Help/DatabaseHelp.txt", "../Cricket/Help/RulesHelp.txt", "../Cricket/Help/GamePlayHelp.txt" };


Database database(fileName);
vector<Team>& teams = database.getTeams();

Game game(teams);

Help help(helpFileNames);

int main()
try {
	char ch;

	do {
		int choice;
		choice = displayMenu();

		switch (choice) {

		case 1:
			database.menu();
			break;

		case 2:
			game.play();
			break;

		case 3:
			help.displayHelp();
			break;

		case 4:
			cout << "\nEND OF PROGRAM\n";
			return 0;

		default:
			cout << "Wrong choice!!\n";
			break;
		}


		ch = getChar("\nDo you want to go to MAIN MENU(y/n)?:\n");

	} while (ch == 'y' || ch == 'Y');


	//Team t("FIRST", vector<Player>{ Player("a", 5,5, 0, 0), Player("b", 5,5, 100, 3) }, Work::BAT);
	//Team t1("SECOND", { Player("c",5, 5, 0, 0), Player("d", 5, 5,100, 3) }, Work::BOWL);

	//vector<Team> teams = { t, t1 };
	//write("Details.dat", teams);

	//vector<Team> readTeams;
	//read("Details.dat", readTeams);
	//cout << innings(readTeams[0], readTeams[1]);

	///*cout << innings(t, t1);*/

	wait();
	return 0;
}
catch (exception& e) {
	cerr << endl << e.what() << endl;
	wait("~");
	return 1;
}
catch (...) {
	cerr << "OOps, Unknown error!!\n";
	wait("~~");
	return 2;
}







int displayMenu()
{
	system("cls");
	int choice;
	cout << "***** MENU *****\n";
	cout << "\n1. Database";
	cout << "\n2. Play";
	cout << "\n3. Help";
	cout << "\n4. Exit";
	choice = getNum("\nEnter the choice:\n");
	return choice;
}
