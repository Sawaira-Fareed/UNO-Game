#include <iostream>
#include <windows.h> // for colors
#include <cstdlib> // for clearing screen
#include <conio.h> //for getch();
#include <fstream> //for file handling
#include <ctime> //for srand

using namespace std;

//UNO GAME PF PROJECT

// Color codes
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;


// Function to set console text and background color
void setColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void MainScreen(int n) {

	//Clear Screen
	system("CLS");

	setColor(RED, BLACK);

cout<<"UNO";

	setColor(WHITE, BLACK);

	if (n == 1)
		setColor(YELLOW, BLACK);
	cout<<"start";
	if (n == 1) cout << "\t\t\t\t\t-------------------------------------" << endl;
	else cout << endl;

	setColor(WHITE, BLACK);

	if (n == 2)
		setColor(YELLOW, BLACK);
	cout<<"Score";
	if (n == 2) cout << "\t\t\t\t\t---------------------------------------" << endl;

	setColor(WHITE, BLACK);
}

void ExitPrompt() {
	system("CLS");
	setColor(BLACK, RED);
	cout << "\n\n\n\n\t\t                                           ";
	cout << "\n\t\t    Do you want to exit the Game ? (Y/N) : ";
	cout << "\n\t\t                                           ";
	char ch;
	ch = _getch();
	if (ch == 'Y' || ch == 'y') {
		cout << "\n\n\t\tThank you for playing the game  :)\n\n";
		setColor(WHITE, BLACK);
		exit(0);
	}
	else {
		setColor(WHITE, BLACK);
		return;
	}
}

bool ReturnMainMenuPrompt() {
	system("CLS");
	setColor(BLACK, RED);
	cout << "\n\n\n\n\t\t                                                                      ";
	cout << "\n\t\t    Do you want to exit to main menu(Progress Wont be Saved)? (Y/N) : ";
	cout << "\n\t\t                                                                      ";
	setColor(WHITE, BLACK);
	char ch;
	ch = _getch();
		return true;
}

int Menu() {
	int x = 1;
	char c;
	do {
		MainScreen(x);
		c = _getch();
		//Check if Up key pressed
		if (c == 'w' || c == 'a' || c == 'A' || c == 'W') {
			x = 1;
		}
		else if (c == 's' || c == 'd' || c == 'S' || c == 'D') {
			x = 2;
		}
		else if (c == 'e' || c == 'E') {
			ExitPrompt();
		}
	} while (c != 13); //Enter key pressed
	return x;
}

bool EnterPressed()
{
	char ch;
	ch = _getch();
	while (ch != 13)
	{
		ch = _getch();
	}
	return true;
}

void initialize_deck(int deck[4][15])
{
	//Run a loop to initialize all cards to 1(Valid), The Values are not Garbage
	// 0 = Red, 1 = Blue, 2 = Green, 3 = Yellow,
	for (int i = 0; i < 4; i++)
	{
		//0 - 9 are Number Cards and 10 - 14 are Special Cards
		// 10 = Reverse, 11 = Skip, 12 = Draw 2, 13 = Draw 4, 14 = Wild Card
		for (int j = 0; j <= 9; j++)
		{
			if (j == 0)//There is only one Zero of each Colour
				deck[i][j] = 1;
			else
				deck[i][j] = 2;
		}
		//Initialize Special Cards
		deck[i][10] = 2; //Reverse
		deck[i][11] = 2; //Skip
		deck[i][12] = 2; //Draw 2
		deck[i][13] = 1; //Draw 4
		deck[i][14] = 1; //Wild Card
	}

}

void shuffle_deck(int deck[4][15], int shuffled_deck[108][2])
{
	srand(time(0));
	int n = 0;
	while (n < 108)
	{
		int color = rand() % 4;
		int number = rand() % 15;
		if (deck[color][number] >= 1)
		{
			//Add to shuffled deck
			shuffled_deck[n][0] = color;
			shuffled_deck[n][1] = number;
			deck[color][number]--;//Remove the card from deck
			n++;
		}
	}
}

void DisplayCardsinHand(int player_cards[100][2], int counter, int player, int hide = 0)
{
	//system("CLS");
	cout << "\t\t\tPlayer " << player << ", ";
	cout << " Cards: \n\n";
	for (int l = 0; l <= counter / 10; l++)
	{
		int line = 10;
		if (l == counter / 10)
			line = counter % 10;

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < line; j++)
			{
				int cardIndex = l * 10 + j;
				// Set Color of Card
				switch (player_cards[cardIndex][0])
				{
				case 0: setColor(BLACK, RED); break;
				case 1: setColor(BLACK, BLUE); break;
				case 2: setColor(BLACK, GREEN); break;
				case 3: setColor(BLACK, YELLOW); break;
				case 4: setColor(WHITE, BLACK); break;
				}

				// Display card structure row by row
				if (i == 0) cout << "-------";
				else if (i == 1) cout << "-     -";
				else if (i == 2) {
					char ch;
					if (player_cards[cardIndex][1] >= 0 && player_cards[cardIndex][1] <= 9)
						ch = player_cards[cardIndex][1] + '0';
					else if (player_cards[cardIndex][1] == 10)
						ch = 'R';
					else if (player_cards[cardIndex][1] == 11)
						ch = 'S';
					else if (player_cards[cardIndex][1] == 12)
						ch = 'p';//Draw 2
					else if (player_cards[cardIndex][1] == 13)
						ch = 'o';//Draw 4
					else if (player_cards[cardIndex][1] == 14)
						ch = 'W';
					if (hide == 1)
						ch = 'U';

					if (ch == 'p')
						cout << "-  " << "D2" << " -";
					else if (ch == 'o')
						cout << "-  " << "D4" << " -";
					else
						cout << "-  " << ch << "  -";

				}
				else if (i == 3) cout << "-     -";
				else if (i == 4) cout << "-------";

				setColor(WHITE, BLACK);  // Reset to default color
				if (i == 5)
				{
					if (cardIndex <= 9)
						cout << "   " << cardIndex + 1 << "   ";  // Display card number
					else
						cout << "   " << cardIndex + 1 << "  ";  // Display card number
				}
				cout << "  ";
			}
			cout << endl;  // Move to the next line after a row of cards
		}
		cout << endl;  // Extra newline between batches of cards
	}
}

void DealCards(int shuffled_deck[108][2], int player1_cards[100][2], int player2_cards[100][2], int& counter1, int& counter2, int startingCards)
{
	int x;
	//Deal 7 Cards to each player
	for (int i = 0; i < startingCards * 2; i++)
	{
		player1_cards[counter1][0] = shuffled_deck[i][0];
		player1_cards[counter1][1] = shuffled_deck[i][1];
		counter1++;
		system("CLS");
		DisplayCardsinHand(player1_cards, counter1, 1, 0);
		DisplayCardsinHand(player2_cards, counter2, 2, 1);//Hide PlayerTwo Cards
		i++;
		player2_cards[counter2][0] = shuffled_deck[i][0];
		player2_cards[counter2][1] = shuffled_deck[i][1];
		counter2++;

		system("CLS");
		DisplayCardsinHand(player1_cards, counter1, 1, 1);//Hide PlayerOne Cards
		DisplayCardsinHand(player2_cards, counter2, 2, 0);
	}

}

void setTopCard(int topCard[2], int shuffled_deck[108][2], int& n, int discardedPile[108][2], int discardCount)
{
	topCard[0] = shuffled_deck[n][0];
	topCard[1] = shuffled_deck[n][1];
	//Add to Discarded Pile
	discardedPile[discardCount][0] = shuffled_deck[n][0];
	discardedPile[discardCount][1] = shuffled_deck[n][1];

	discardCount++;
	n++;
}

void printTopCard(int topCard[2], int CardsCount)
{
	//Print Top Card as Well as Deck Cards
	cout << "\n";
	for (int i = 0; i < 9; i++)
	{
		// Set Color of Card
		if (i == 0)
			cout << "-To Draw a Card from the Card Deck,  ";
		else if (i == 1)
			cout << "      Press 'Q' or 'q'               ";
		else if (i == 2)
			cout << "-To Throw a Card From Hand,          ";
		else if (i == 3)
			cout << "     Press 'H' or 'h'                ";
		else if (i == 4)
			cout << "-To Call UNO, Press 'U' or 'u'       ";
		else if (i == 5)
			cout << "-To Pause the Game, Press 'P' or 'p' ";
		else if (i == 6)
			cout << "-To Save the Game, Press 'S' or 's'  ";
		else if (i == 7)
			cout << "-To Exit the Game, Press 'E' or 'e'  ";
		else if (i == 8)
			cout << "                                    ";

		cout << "\t\t";
		for (int k = 0; k < 2; k++) {

			switch (topCard[0])
			{
			case 0: setColor(BLACK, RED); break;
			case 1: setColor(BLACK, BLUE); break;
			case 2: setColor(BLACK, GREEN); break;
			case 3: setColor(BLACK, YELLOW); break;
			case 4: setColor(WHITE, BLACK); break;
			}
			if (k == 1)
				setColor(RED, BLACK);
			// Display card structure row by row
			if (i == 0 && k == 0) cout << "-----------";
			else if (k == 0 && (i == 1 || i == 2 || i == 3) ) cout << "-         -";
			else if ( i == 4 && k == 1) {//Deck
				int d = 108 - CardsCount;
				cout << "Cards left in Deck : " << d;
					
			}
			else if (k == 0 && i == 4 ) {
				char ch;
				if (topCard[1] >= 0 && topCard[1] <= 9)
					ch = topCard[1] + '0';
				else if (topCard[1] == 10)
					ch = 'R';
				else if (topCard[1] == 11)
					ch = 'S';
				else if (topCard[1] == 12)
					ch = 'p';
				else if (topCard[1] == 13)
					ch = 'o';
				else if (topCard[1] == 14)
					ch = 'W';


				if (ch == 'p')
					cout << "-    " << "D2" << "   -";
				else if (ch == 'o')
					cout << "-    " << "D4" << "   -";
				else
					cout << "-    " << ch << "    -";
			}
			else if (k == 0 && (i == 5 || i == 6 || i == 7 )) cout << "-         -";
			else if (i == 8 && k == 0) cout << "-----------";

			setColor(WHITE, BLACK);
			cout << "\t\t\t";
		}


		setColor(WHITE, BLACK);  // Reset to default color
		cout << endl;
	}
}

void PrintBoard(int topCard[2], int player1_cards[100][2], int counter1, int player2_cards[100][2], int counter2, int CardsCounter, int player = 1)
{
	system("CLS");

	cout << "\t\tPlayer " << player << "'s Turn\n\n";

	int hide = 0;
	if (player == 2)//If player 2 turn, hide player 1 cards
		hide = 1;
	//Display Player 1 Cards
	DisplayCardsinHand(player1_cards, counter1, 1, hide);

	//Display Top Card
	printTopCard(topCard, CardsCounter);

	hide = 0;
	if (player == 1)//If player 1 turn, hide player 2 cards
		hide = 1;
	//Display Player 2 Cards
	DisplayCardsinHand(player2_cards, counter2, 2, hide);
}

void loadGameResult(int& score1, int& score2)
{
	ifstream fin("Score.txt");
	if (fin.is_open())
	{
		fin >> score1 >> score2;
		fin.close();
	}
	else
	{
		score1 = 0;
		score2 = 0;
	}
}

void saveGameResult(int score1, int score2, int winner, string movesPlayed[250], int movesCounter)
{
	ofstream fout("Score.txt");
	if (fout.is_open())
	{
		if (winner == 1)
			score1++;
		else
			score2++;
		fout << score1 << " " << score2 << endl;
		for (int i = 0; i < movesCounter; i++)
		{
			fout << i + 1 << ". " << movesPlayed[i] << "." << endl;
		}
		fout.close();
	}
	else
	{
		cout << "Error in Saving the Game Result" << endl;
	}
}

void displayOnlyTopCard(int topCard[2]) {
	//Print Only the Top Card
	cout << "\n";
	for (int i = 0; i < 9; i++)
	{
		cout << "\t\t\t\t";
		switch (topCard[0])
		{
		case 0: setColor(BLACK, RED); break;
		case 1: setColor(BLACK, BLUE); break;
		case 2: setColor(BLACK, GREEN); break;
		case 3: setColor(BLACK, YELLOW); break;
		case 4: setColor(WHITE, BLACK); break;
		}
		// Display card structure row by row
		if (i == 0) cout << "-----------";
		else if (i == 1 || i == 2 || i == 3) cout << "-         -";
		else if (i == 4) {
			char ch;
			if (topCard[1] >= 0 && topCard[1] <= 9)
				ch = topCard[1] + '0';
			else if (topCard[1] == 10)
				ch = 'R';
			else if (topCard[1] == 11)
				ch = 'S';
			else if (topCard[1] == 12)
				ch = 'p';
			else if (topCard[1] == 13)
				ch = 'o';
			else if (topCard[1] == 14)
				ch = 'W';
			if (ch == 'p')
				cout << "-    " << "D2" << "   -";
			else if (ch == 'o')
				cout << "-    " << "D4" << "   -";
			else
				cout << "-    " << ch << "    -";
		}
		else if (i == 5 || i == 6 || i == 7) cout << "-         -";
		else if (i == 8) cout << "-----------";
		setColor(WHITE, BLACK);  // Reset to default color
		cout << endl;
	}
}

void DisplayScore(int score1, int score2) {
	system("CLS");
	cout << "\n\n";
	setColor(RED, BLACK);
	
	cout << "\t\t\t SCORE BOARD\n\n\n";
	setColor(GREEN, BLACK);
	cout << "\t\tPlayer 1: " << score1 << "\n\n\n\t\tPlayer 2: " << score2 << endl;
}

void addCards(int player_cards[100][2], int& counter, int shuffled_deck[108][2], int& CardsCounter, int amount)
{
	for (int i = 0; i < amount && counter < 100 && CardsCounter < 108; i++)
	{
		player_cards[counter][0] = shuffled_deck[CardsCounter][0];
		player_cards[counter][1] = shuffled_deck[CardsCounter][1];
		counter++;
		CardsCounter++;
	}
}

void updateDiscardPile(int topCard[2], int col, int cardtype, int discardPile[108][2], int& discardCounter)
{
	topCard[0] = col;
	topCard[1] = cardtype;

	//Add to Discarded Pile
	discardPile[discardCounter][0] = col;
	discardPile[discardCounter][1] = cardtype;

	discardCounter++;
}

bool isValidPlay(int topCard[2], int color, int cardType)
{
	//Placation Valid when
	// 1. The Colour is Same ( for 0 to 12 ) Numbers, Skip, Reverse, Draw 2
	// 2. The Card is Wild Card or Draw 4
	// 3. The Number is Same
	// 4. The Card types are Same ( Skip, Reverse, Draw 2)

	//The color is the same
	if (color == topCard[0] && cardType <= 12)
		return true;

	//The card is a Wild Card or Draw 4
	if (cardType == 14 || cardType == 13)
		return true;

	//The number is the same (for number cards 0-9)
	if (cardType <= 9 && cardType == topCard[1])
		return true;

	//The card types are the same (Skip, Reverse, Draw 2)
	if ((cardType >= 10 && cardType <= 12) && cardType == topCard[1])
		return true;

	// If none of the conditions are met, the play is invalid
	return false;
}

void refillDeck(int shuffled_deck[108][2], int& CardsCounter, int discardPile[108][2], int& discardCounter)
{
	//Refill the Deck using random cards from the discard pile
	//Start filling from end of the deck

	discardCounter--;//No need to check the last card, it will remain discarded

	int n = 107;
	int index = 0;
	int count = 0;
	CardsCounter = 107 - discardCounter;


	while (count < discardCounter) {
		index = rand() % discardCounter;
		if (discardPile[index][0] != -1)
		{
			shuffled_deck[n][0] = discardPile[index][0];
			shuffled_deck[n][1] = discardPile[index][1];
			discardPile[index][0] = -1;
			discardPile[index][1] = -1;
			n--;
			count++;
		}
	}

	discardPile[0][0] = discardPile[discardCounter][0];
	discardPile[0][1] = discardPile[discardCounter][1];
	discardCounter = 1;


}



int cardThrowTurn(int topCard[2], int player1_cards[100][2], int cardsinHand, int player)//Will Return Index of the Valid Card Thrown, else -1 
{
	system("CLS");
	cin.clear();
	int validCard = -1;
	int color, cardType;
	color = topCard[0]; cardType = topCard[1];

	bool invalidPlay = false;
	int x = 0;
	while (1) {
		system("CLS");
		DisplayCardsinHand(player1_cards, cardsinHand, player, 0);
		displayOnlyTopCard(topCard);
		if (invalidPlay == true)
			cout << "\n\n\tInvalid Card, Please Enter Again: ";
		cout << "\n\n\tEnter the Card Number to Throw or 0 to go back : ";
		cin >> x;
		if (x == 0)
			return -1;
		
			//Check if the Card is Valid
			if (isValidPlay(topCard, player1_cards[x - 1][0], player1_cards[x - 1][1]) == true) {
				invalidPlay = false;
				validCard = x - 1;
				break;
			}
			else
			{
				invalidPlay = true;
				continue;
			}
	}
	cout << "\n\n\tCard Thrown Successfully  : " << validCard + 1 << endl;
	cout << "\n\tPress Enter key to continue...";
	EnterPressed();
	return validCard;
}

void removeCardfromHand(int cardIndex, int player_cards[100][2], int& counter)
{
	for (int i = cardIndex; i < counter - 1; i++)
	{
		player_cards[i][0] = player_cards[i + 1][0];
		player_cards[i][1] = player_cards[i + 1][1];
	}
	counter--;
}

bool checkPlayerWon(int player, int count) {
	if (count == 0)
	{
		system("CLS");
		cout << "\n\nCongrats You Won";
		cout << "\n\n\n";

		cout << "Player " << player << " Won ... :) ";
		cout << "\n\nPress Enter Key to Continue...";
		EnterPressed();
		return true;
	}
	return false;
}

bool callUno(int count) {
	if (count == 2)
	{
		system("CLS");

		setColor(YELLOW, BLACK);

		cout << "\n";
		cout << "\t\tUno Called Successfully\n\n";
		cout << "\n\nYou can Win this :) ";
		cout << "\n\n\tUNO Called Successfully, Press Enter to Continue...";
		EnterPressed();
		return true;
	}
	return false;
}


//If Returns 2, 4, that means the oponents draws 2 or 4 cards
//if returns 1, the oponents turn is skipped
// if returns 0, the turn is normal
// if return 3, the player has to change the color
int handleSpecialCard(int cardType) {
	if (cardType == 10) {
		cout << "\n\n\tOponent's Turn Skipped, Press Enter to Continue...";
		EnterPressed();
		return 1;
	}
	else if (cardType == 11) {
		cout << "\n\n\tOponent's Turn Skipped, Press Enter to Continue...";
		EnterPressed();
		return 1;
	}
	else if (cardType == 12) {
		cout << "\n\n\tOponent Draws 2 Cards, Press Enter to Continue...";
		EnterPressed();
		return 2;
	}
	else if (cardType == 13) {
		cout << "\n\n\tOponent Draws 4 Cards, Press Enter to Continue...";
		EnterPressed();
		return 4;
	}
	else if (cardType == 14) {
		cout << "\n\n\tYou can choose any color now, Press Enter to Continue...";
		EnterPressed();
		return 3;
	}
	return 0;
}


void playTurn(int& turn, int& currPLayer, int& oponent, int  topCard[2], int  player1_cards[100][2], int& counter1, int  player2_cards[100][2], int& counter2, int& CardsCounter, bool& gobackMainMenu, int  shuffled_deck[108][2], int  discaredPile[108][2], int& discaredCounter, int score1, int score2, string  movesPlayed[1010], int& movesCounter, int& retFlag)
{
	retFlag = 1;
	bool unoCalled = false;
	if (turn % 2 == 1) {
		currPLayer = 1;
		oponent = 2;
	}
	else {
		currPLayer = 2;
		oponent = 1;
	}
	string move = "::)";

	char ch;
	while (1)
	{

		PrintBoard(topCard, player1_cards, counter1, player2_cards, counter2, CardsCounter, currPLayer);
		ch = _getch();
		if (ch == 'E' || ch == 'e') {//Go to Main Menu
			if (ReturnMainMenuPrompt() == true) {//Exit to Main Menu
				gobackMainMenu = true;
				break;
			}
		}
		else if (ch == 'q' || ch == 'Q') {//Draw a card from the deck
			int cardstopick = 1;
			if (unoCalled == true) {
				system("CLS");
				cout << "\n\n\You called Uno and didn't throw a card, hence you will pick two(2) cards, Press Enter to Continue...";
				EnterPressed();
				cardstopick = 2;
			}

			if (CardsCounter >= 108) {
				system("CLS");
				cout << "Refiller Called";
				refillDeck(shuffled_deck, CardsCounter, discaredPile, discaredCounter);
				EnterPressed();
			}
			move = "Picked a Card from Deck";
			if (currPLayer == 1)
				addCards(player1_cards, counter1, shuffled_deck, CardsCounter, cardstopick);
			else
				addCards(player2_cards, counter2, shuffled_deck, CardsCounter, cardstopick);
			break;
		}
		
		else if (ch == 's' || ch == 'S') {//Save the Game
			system("CLS");
			cout << "\n\n Are you sure you want to save the game? (Y/N) : ";
			char ch;
			ch = _getch();
			if (ch == 'Y' || ch == 'y') {
				saveGameResult(score1, score2, 0, movesPlayed, movesCounter);
				cout << "\n\nGame Saved Successfully" << endl;
				cout << "Press any key to continue";
				EnterPressed();
				//gobackMainMenu = true;
				break;
			}
		}
		else if (ch == 'h' || ch == 'H') {// Throw a card from hand
			int cardIndex = -1;
			int num = -1;
			if (currPLayer == 1)
				num = cardThrowTurn(topCard, player1_cards, counter1, currPLayer);
			else
				num = cardThrowTurn(topCard, player2_cards, counter2, currPLayer);
			if (num == -1 && unoCalled == true) {
				cout << "\n\n\tYou called UNO and didn't throw a card, you will pick two cards now, Press Enter to Continue...";
				EnterPressed();
				break;
			}
			if (num == -1)
				continue;
			//Remove the Card from Player Deck, Update The Discarded Pile, Check if Player Won

			move = "Threw a Card from Hand";
			int cardThrownColor = 0;
			int cardThrownType = 0;
			if (currPLayer == 1) {
				cardThrownColor = player1_cards[num][0];
				cardThrownType = player1_cards[num][1];
			}
			else {
				cardThrownColor = player2_cards[num][0];
				cardThrownType = player2_cards[num][1];
			}

			updateDiscardPile(topCard, cardThrownColor, cardThrownType, discaredPile, discaredCounter);

			if (currPLayer == 1)
				removeCardfromHand(num, player1_cards, counter1);
			else
				removeCardfromHand(num, player2_cards, counter2);

			if (currPLayer == 1)
			{
				if (checkPlayerWon(currPLayer, counter1) == true)
				{
					move = "WON";
					movesPlayed[movesCounter++] = move;
					saveGameResult(score1, score2, currPLayer, movesPlayed, movesCounter);
					gobackMainMenu = true;
					break;
				}
			}
			else
			{
				if (checkPlayerWon(currPLayer, counter2) == true)
				{
					move = "WON";
					movesPlayed[movesCounter++] = move;
					saveGameResult(score1, score2, currPLayer, movesPlayed, movesCounter);
					gobackMainMenu = true;
					break;
				}
			}

			//Check if its a special Card

			int specialCard = handleSpecialCard(cardThrownType);
			if (specialCard == 1) {//Skip Turn
				move = "Used Skip/Reverse Card, Oponents Turn Skipped";
				movesPlayed[movesCounter++] = move;
				move = "Skipped";
				turn++;
				break;
			}
			else if (specialCard == 3) {//Change Color
				system("CLS");
				cout << "\n\n\tEnter the Color to Change to: ";
				cout << "\n\n\t 0. Red,\n\t 1. Blue,\n\t 2. Green,\n\t 3. Yellow      : ";
				int color;
				cin >> color;
				while (color < 0 || color > 3)
					cin >> color;
				topCard[0] = color;
				break;
			}
			else if (specialCard == 2 || specialCard == 4) {//Draw 2 or 4
				move = "Oponent Picked Up cards";
				movesPlayed[movesCounter++] = move;
				move = "Skipped";
				if (currPLayer == 1)
				{
					addCards(player2_cards, counter2, shuffled_deck, CardsCounter, specialCard);
				}
				else
					addCards(player1_cards, counter1, shuffled_deck, CardsCounter, specialCard);
				turn++;
				break;
			}
			break;
		}
		else if (ch == 'U' || ch == 'u') {//Call UNO
			if (currPLayer == 1)
				unoCalled = callUno(counter1);
			else
				unoCalled = callUno(counter2);
			if (unoCalled == true)
			{
				continue;
			}
			else {
				system("CLS");
				cout << "\n\n\tYou called UNO while you had more than Two(2) cards, you will have to pick two cards now.\n";
				cout << "\tPress Enter to Continue : ";
				EnterPressed();
				if (currPLayer == 1)
					addCards(player1_cards, counter1, shuffled_deck, CardsCounter, 2);
				else
					addCards(player2_cards, counter2, shuffled_deck, CardsCounter, 2);
				break;
			}
		}
	}
	if (gobackMainMenu == true)
	{
		retFlag = 2; return;
	};
	turn++;
	movesPlayed[movesCounter++] = move;
}

int main() {

	while (1)
	{
		int score1 = 0, score2 = 0;
		loadGameResult(score1, score2);

		int x = Menu();

		if (x == 2)
		{

			cout << "You have selected 2nd option" << endl;
			//Checking if a File Named Score.txt exists
			loadGameResult(score1, score2);
			DisplayScore(score1, score2);
			char ch;
			ch = _getch();
			continue;
		}
		else
		{
			//Start The Game

			// 0 - 3 for colors and 4 for Wild Card
			int player1_cards[100][2]; int counter1 = 0; //Counter stores the number of cards in hand
			int player2_cards[100][2];	int counter2 = 0;
			int deck[4][15];
			int startingCards = 7;

			//Initialize Deck
			initialize_deck(deck);

			//Shuffled Deck, 108 Cards, 2D Array, 1st Column for Color(Type), 2nd Column for Number or other type
			int shuffled_deck[108][2];

			//Shuffle the Deck
			shuffle_deck(deck, shuffled_deck);

			//Deal Cards
			DealCards(shuffled_deck, player1_cards, player2_cards, counter1, counter2, startingCards);

			int topCard[2]; //Stores the top card of the deck
			int discaredPile[108][2]; int discaredCounter = 0; //Stores the discarded cards
			int CardsCounter = startingCards * 2;
			setTopCard(topCard, shuffled_deck, CardsCounter, discaredPile, discaredCounter);

			string movesPlayed[1010]; int movesCounter = 0;

			bool gobackMainMenu = false;
			int turn = 1;

			int currPLayer = 1;
			int oponent = 2;
			while (turn < 1000)
			{

				int retFlag;
				playTurn(turn, currPLayer, oponent, topCard, player1_cards, counter1, player2_cards, counter2, CardsCounter, gobackMainMenu, shuffled_deck, discaredPile, discaredCounter, score1, score2, movesPlayed, movesCounter, retFlag);
				if (retFlag == 2) break;
			}
			if (gobackMainMenu == true)
				continue;
		}

	}

	return 0;
}


