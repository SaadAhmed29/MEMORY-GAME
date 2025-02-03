#pragma once
#define NOMINMAX
#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML/Audio.hpp>


using namespace sf;
using namespace std;
class Tile
{
private:
	RectangleShape shape;
	Color colorInactive;
	Color colorActive;
	Color colorCorrect;
	Color colorIncorrect;
	int alphaIdle;
	int alphaHover;
	int alphaPressed;
	bool active;
	bool pressed;

	//Sound

	Sound pop;
	SoundBuffer pbuff;

public:
	Tile();
	Tile(Vector2f position, float size, bool active);
	~Tile();

	inline const bool isPressed() const { return this->pressed; }
	inline const bool isActive() const { return this->active; }

	void setActive(const bool active);
	void setColorActive();
	void setColorInActive();
	void setColorCorrect();
	void setColorIncorrect();

	void update(Vector2f& mousePosView, const bool lmb_pressed);
	void render(RenderTarget& target);

};

