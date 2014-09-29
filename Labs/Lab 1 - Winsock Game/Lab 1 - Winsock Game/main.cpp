#include <WinSock2.h>
#include "Net.h"
#include <iostream>

using namespace std;
void playerA(Net*);
void playerB(Net*);
void gameLoop();

char message[200] = "";
char playerMove[1] = "";
int portA = 28000;
int portB = 28001;
bool opponentSetup;

int bomb = 21;

int main() {

	Net* n = new Net();
	n->initialise();

	cout << "You are playing Bomb Squad!" << endl
		<< "Rules:" << endl
		<< "The bomb has 21 ticks." << endl
		<< "You can only tick down up to 3 ticks before passing to the opponent." << endl
		<< "Input a number between 1 & 3 and hit enter to tick down." << endl
		<< "If you're holding onto the bomb when it explodes..." << endl << "Well there won't be much left!" << endl
		<< "But first, are you Player a or b ?" << endl;

	string input = "";
	cin >> input;

	if (input == "a"){
		playerA(n);
	}
	else if (input == "b"){
		playerB(n);
	}
};

void  playerA(Net* n){
	//Enter Own IP here
	char* ip = "127.0.0.1";

	n->setupUDP(portA, ip);

	//Enter oppoonent IP here;
	char* opponentIP = "127.0.0.1";

	cout << "Port number: " << n->portNum << endl << "IP address: " << n->getSenderIP() << endl;

	//Wait for opponent to setup winsocket
	while (opponentSetup == false){

		n->receiveData(message); //Continously checks to receive a message
		n->sendData(opponentIP, portB, "Player A Confirmed"); //Continusly sends the message

		if (message[0] != '\0'){
			cout << message << endl;
			opponentSetup = true;
			goto yourTurn; //Player A has first move
		}
	}

	//Start game
	while (opponentSetup == true)
	{
	enemyTurn:
		while (true)
		{

			n->receiveData(playerMove);
			if (playerMove[0] == '1' || playerMove[0] == '2' || playerMove[0] == '3'){
				cout << playerMove << endl;
				bomb -= (int)playerMove[0] - 48;
				if (bomb <= 0)
				{
					cout << "YOU WIN!" << endl;
				}
				cout << "Tick Tock " << bomb << endl;
				playerMove[0] = '0';
				goto yourTurn;
			}
		}

	yourTurn:
		{
			gameLoop();
			n->sendData(opponentIP, portB, playerMove);
			playerMove[0] = '0';
			goto enemyTurn;
		}
	}
}

void playerB(Net* n){
	//Enter Own IP here
	char* ip = "127.0.0.1";

	n->setupUDP(portB, ip);

	//Enter oppoonent IP here;
	char* opponentIP = "127.0.0.1";

	cout << "Port number: " << n->portNum << endl << "IP address: " << n->getSenderIP() << endl;

	//Wait for opponent to setup winsocket
	while (opponentSetup == false)
	{
		n->receiveData(message);
		n->sendData(opponentIP, portA, "Player B Confirmed");
		if (message[0] != '\0'){
			cout << message << endl;
			opponentSetup = true;
			goto enemyTurn; //Player B has second turn
		}
	}

	//Start game
	while (opponentSetup == true)
	{
	enemyTurn:
		while (true)
		{

			n->receiveData(playerMove);
			if (playerMove[0] == '1' || playerMove[0] == '2' || playerMove[0] == '3')
			{
				cout << playerMove << endl; //Outputs the move the opponent makes
				bomb -= (int)playerMove[0] - 48;
				if (bomb <= 0)
				{
					cout << "YOU WIN!";
				}
				cout << "Tick Tock " << bomb << endl;
				playerMove[0] = '0';
				goto yourTurn;
			}
		}

	yourTurn:
		{
			gameLoop();
			n->sendData(opponentIP, portA, playerMove);
			playerMove[0] = '0';
			goto enemyTurn;
		}
	}
}

void gameLoop()
{
	cin >> playerMove;

check:
	if (playerMove[0] == '1')
	{
		bomb--;
	}
	else if (playerMove[0] == '2')
	{
		bomb -= 2;
	}
	else if (playerMove[0] == '3')
	{
		bomb -= 3;
	}
	else
	{
		cout << "Please input a value between 1 & 3" << endl;
		cin >> playerMove;
		goto check;
	}

	if (bomb <= 0)
	{
		cout << "KABOOM!" << endl;
	}
	else
	{
		cout << "Tick Tock " << bomb << endl;
	}
}