#include"GameBoard.h"
#include<cstdlib>

using namespace sf;
using namespace std;

int main() 
{
	//Window resolution
	const int window_width = 700;
	const int window_height = 700;

	//Grid size
	int board_width;
	int board_height;


	float tile_size;
	int Active_tiles;

	srand(time(0));

	//Window

	RenderWindow window(VideoMode(window_width, window_height), "Memory Game");
	window.setFramerateLimit(60);


	//Texts, Main screen

	bool MainMenu = true;
	Vector2f mousePosView;
	GameBoard *gameboard = nullptr;

	Font font;
	Text easy;
	Text med;
	Text hard;
	Text escKey;
	Sprite mainmenu;
	Texture tmain;

	tmain.loadFromFile("mainmenu.jpg");
	mainmenu.setTexture(tmain);
	font.loadFromFile("AmaticFont.ttf");


	escKey.setFont(font);
	escKey.setCharacterSize(20);
	escKey.setPosition(520,660);
	escKey.setFillColor(Color::White);
	escKey.setString("Press Esc to return to menu!");
	escKey.setStyle(Text::Bold);


	easy.setFont(font);
	easy.setCharacterSize(40);
	easy.setPosition(290, 370);
	easy.setFillColor(Color::White);
	easy.setString("EASY");
	easy.setStyle(Text::Bold);
	

	med.setFont(font);
	med.setCharacterSize(40);
	med.setPosition(290, 450);
	med.setFillColor(Color::White);
	med.setString("MEDIUM");
	med.setStyle(Text::Bold);
	

	hard.setFont(font);
	hard.setCharacterSize(40);
	hard.setPosition(290, 530);
	hard.setFillColor(Color::White);
	hard.setString("HARD");
	hard.setStyle(Text::Bold);
	


	// Main Game Loop

	while (window.isOpen()) {

		//If statement for showing the main menu
		
		if (MainMenu) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
			}

			mousePosView = window.mapPixelToCoords(Mouse::getPosition(window)); //Gets mouse cursor pos wrt window

			window.clear();
			window.draw(mainmenu);
			window.draw(easy);
			window.draw(med);
			window.draw(hard);
			window.draw(escKey);
			window.display();

			//MODES LOGIC

			//IF EASY MODE IS SELECTED
			if (easy.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 5;
				board_height = 5;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 4;
				MainMenu = false;
				gameboard = new GameBoard(&window, tile_size, board_width, board_height, Active_tiles);
			}
			//IF MEDIUM MODE IS SELECTED
			else if (med.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 6;
				board_height = 6;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 5;
				MainMenu = false;
				gameboard = new GameBoard(&window, tile_size, board_width, board_height, Active_tiles);
			}
			//IF HARD MODE IS SELECTED
			else if (hard.getGlobalBounds().contains(mousePosView) && Mouse::isButtonPressed(Mouse::Left)) {
				board_width = 7;
				board_height = 7;
				tile_size = min(window_width / (float)board_width, window_height / (float)board_height);
				Active_tiles = 6;
				MainMenu = false;
				gameboard = new GameBoard(&window, tile_size, board_width, board_height, Active_tiles);
			}
		}

		//Else statement to run the actual game

		else 
		{
			Event event;
			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
				}
				// Return to Main Menu if escape key is pressed
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
					
					system("cls"); //Clears the cmd
					delete gameboard;
					gameboard = nullptr;
					MainMenu = true;
					break;
				}
			}
			//Runs the game
			if (!MainMenu) {
				gameboard->update(window);

				window.clear();
				gameboard->render(window);
				window.display();
			}
		}
	}	
	if (gameboard) {
		delete gameboard;
	}
	window.close();
}