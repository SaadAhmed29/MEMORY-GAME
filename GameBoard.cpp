#include "GameBoard.h"

//Function that creates the board

void GameBoard::createBoard(const int board_width, const int board_height)
{
	float x = 0.f;
	float y = 0.f;
	for (size_t i = 0;i < board_height;i++) { //Outer loop sets the y coordinate

		for (size_t k = 0;k < board_width;k++) { //Inner loop sets the x coordinate
			tilesVec.push_back(new Tile(Vector2f(x, y), tileSize, false));
			x += tileSize;
		}
		y += tileSize;
		x = 0.f;
	}
}


//Function that makes the pattern to be displayed

void GameBoard::randomizeBoard()
{
	//Resetting the board

	activeTiles.clear();  //Clears the previous round pattern

	for (size_t i = 0;i < tilesVec.size();i++) {
		tilesVec[i]->setActive(false);
		tilesVec[i]->setColorInActive();
	}

	//Generating random patterns on board

	vector<int>index_vector;
	for (size_t i = 0;i < tilesVec.size();i++) {
		index_vector.push_back(i);
	}

	int tiles_added = 0;
	int index = -1;

	while (tiles_added != nrOfActiveTiles) {
		index = rand() % index_vector.size();
		tilesVec[index_vector[index]]->setActive(true);
		activeTiles.Enqueue(index_vector[index]); 
		dummyQueue.Enqueue(index_vector[index]);
		index_vector.erase(index_vector.begin() + index);
		tiles_added++;
	}
}

//Function that first displays normal grid, then the pattern, then again normal grid

void GameBoard::displayOrder()
{
	static int frameRate;
	float phase1 = 50.f;
	float phase2 = 150.f;
	float phase3 = 200.f;

	//Setting the time ranges for patterns to be displayed

	if (displayTimer < phase1) {
		for (size_t i = 0;i < tilesVec.size();i++) {
			tilesVec[i]->setColorInActive();
		}
	}
	else if (displayTimer >= phase1 && displayTimer < phase2) {
		if (!activeTiles.isEmpty()) {  

			// Highlight the current active tile
			tilesVec[activeTiles.queue_front()]->setColorActive();

			// Increment frame counter to control display duration of the current tile
			frameRate++;
			if (frameRate >= ((phase2-phase1)/nrOfActiveTiles)) {  
				frameRate = 0;
				activeTiles.Dequeue(); // Move to the next active tile
			}
		}
	}
	else if (displayTimer >= phase2 && displayTimer < phase3) {
		for (size_t i = 0;i < tilesVec.size();i++) {
			tilesVec[i]->setColorInActive();
		}
	}
	else {
		restarting = false;
		frameRate = 0;
	}

	displayTimer += 1.f;  //Change this to change the duration of the board and active tiles being displayed

}


//Function to check if the user's pattern matches with the pattern that was displayed

const bool GameBoard::checkSelection()  
{
	while (!SelectedTiles.isEmpty()) {
		int temp1, temp2;
		temp1 = SelectedTiles.Dequeue();
		temp2 = dummyQueue.Dequeue();

		if (temp1 != temp2) {
			return false;
		}
	}
	return true;
}

void GameBoard::updateKeyTime()
{
	if (keyTime < keyTimeMax) {
		keyTime += 1.f;
	}
}


//Called after the pattern is displayed, stores the pattern that user has made and calls the checkSelection function

void GameBoard::updateBoard(RenderWindow& window)
{
	if (restarting) {
		displayOrder();
	}
	else {
		if (tilesSelected < nrOfActiveTiles) {
			for (size_t i = 0;i < tilesVec.size();i++) {
				this->tilesVec[i]->update(this->mousePosView, Mouse::isButtonPressed(Mouse::Left));

				if (tilesVec[i]->isPressed() && checkKeyTime()) {
					SelectedTiles.Enqueue(i);     
					tilesVec[i]->setColorActive();
					tilesSelected++;
					resetKeyTime();
				}
			}
		}
		else {
			timer = 0.f;
			if (checkSelection()) {
				correctSound.play();
				correct++;
				for (size_t i = 0;i < tilesVec.size();i++) {
					tilesVec[i]->setColorCorrect();
				}
				while (timer < 50.f) {
					render(window);
					window.draw(CorrectGuess);
					window.display();
					timer += 1.f;
				}
			}
			else {
				incorrectSound.play();
				incorrect++;
				for (size_t i = 0;i < tilesVec.size();i++) {
					tilesVec[i]->setColorIncorrect();
				}
				while (timer < 50.f) {
					render(window);
					window.draw(IncorrectGuess);
					window.display();
					timer+=1.f;
				}
			}
			
			cout << "Score: " << correct<< endl;
			restart();
		}
	}
}

GameBoard::GameBoard()
{
	window = nullptr;
	tileSize = 0.f;
	exitGame = false;
	keyTimeMax = 0.f;
	keyTime = 0.f;
	nrOfActiveTiles = 0;
	tilesSelected = 0;
	restarting = false;
	displayTimer = 0.f;
	correct = 0;
	incorrect = 0;
}

GameBoard::GameBoard(RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active) :window(window)
{
	font.loadFromFile("ChrustyRock.ttf");
	tileSize = tile_size;
	exitGame = false;
	keyTimeMax = 10.f;
	keyTime = keyTimeMax;
	nrOfActiveTiles = nr_active;
	tilesSelected = 0;
	restarting = true;
	displayTimer = 0.f;
	correct = 0;
	incorrect = 0;
	createBoard(board_width, board_height);
	randomizeBoard();
	cbuffer.loadFromFile("correct.wav");
	ibuffer.loadFromFile("negative.wav");
	incorrectSound.setBuffer(ibuffer);
	correctSound.setBuffer(cbuffer);

	//Texts
	CorrectGuess.setFont(font);
	CorrectGuess.setCharacterSize(60);
	CorrectGuess.setPosition(200, 290);
	CorrectGuess.setFillColor(Color::White);
	CorrectGuess.setString("CORRECT");
	CorrectGuess.setStyle(Text::Bold);

	IncorrectGuess.setFont(font);
	IncorrectGuess.setCharacterSize(60);
	IncorrectGuess.setPosition(170,290);
	IncorrectGuess.setFillColor(Color::White);
	IncorrectGuess.setString("INCORRECT");
	IncorrectGuess.setStyle(Text::Bold);
}

//Deleting all tiles as the game is closed

GameBoard::~GameBoard()
{
	for (size_t i = 0;i < tilesVec.size();i++) {
		delete tilesVec[i];
	}
}


//Resets stuff after each round

void GameBoard::restart()
{
	tilesSelected = 0;
	restarting = true;
	displayTimer = 0.f;
	SelectedTiles.clear();
	dummyQueue.clear();
	randomizeBoard();
}


void GameBoard::update(RenderWindow& window)
{
	this->mousePosView = window.mapPixelToCoords(Mouse::getPosition(window)); //Get mouse pos wrt the game window
	updateKeyTime();
	updateBoard(window);
}

//Renders tiles on the window

void GameBoard::render(RenderTarget& target)
{
	for (size_t i = 0;i < tilesVec.size();i++) {
		tilesVec[i]->render(target);
	}
}
