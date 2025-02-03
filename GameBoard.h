#pragma once
#define NOMINMAX
#include<iostream>
#include<vector>
#include<windows.h>
#include<algorithm>
#include"Tile.h"
#include<time.h>
#include"Queue.h"

using namespace sf;
using namespace std;

class GameBoard
{
private:

	RenderWindow* window;
	vector<Tile*> tilesVec;
	float keyTime, keyTimeMax;
	Vector2f mousePosView;
	float tileSize;
	bool exitGame;
	bool restarting;
	int tilesSelected;
	int nrOfActiveTiles;
	int correct;
	int incorrect;
	float displayTimer;
	float timer;

	//Texts

	Font font;
	Text CorrectGuess;
	Text IncorrectGuess;


	//Queues

	Queue activeTiles;
	Queue SelectedTiles;
	Queue dummyQueue;

	//Sound

	Sound correctSound;
	Sound incorrectSound;
	SoundBuffer cbuffer;
	SoundBuffer ibuffer;

	//private functions

	void createBoard(const int board_width, const int board_height);
	void randomizeBoard();
	void displayOrder();
	const bool checkSelection();
	void updateKeyTime();
	void updateBoard(RenderWindow& window);

	inline const bool checkKeyTime() const { return keyTime >= keyTimeMax; }
	inline void resetKeyTime() { keyTime = 0.f; }

public:

	GameBoard();
	GameBoard(RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active);
	~GameBoard();

	inline const bool checkExit() const { return exitGame; }
	void restart();
	void update(RenderWindow& window);
	void render(RenderTarget& target);

};

