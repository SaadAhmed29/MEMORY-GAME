#include "Tile.h"

Tile::Tile()
{
	active = false;
	pressed = false;
	alphaIdle = 0;
	alphaHover = 0;
	alphaPressed = 0;
}

Tile::Tile(Vector2f position, float size, bool active)
{
	colorActive = Color(255,0,0,200);
	colorInactive = Color(0,71,171);
	colorCorrect = Color(76, 175, 80);
	colorIncorrect = Color(229, 57, 53);
	shape.setSize(Vector2f(size, size));
	shape.setFillColor(colorInactive);
	shape.setPosition(position);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(Color::White);
	this->active = active;
	pressed = false;
	alphaIdle = 100;
	alphaHover = 255;
	alphaPressed = 50;

	pbuff.loadFromFile("pop.wav");
	pop.setBuffer(pbuff);

}

Tile::~Tile()
{
}

void Tile::setActive(const bool active)
{
	this->active = active;
}

void Tile::setColorActive()
{
	this->shape.setFillColor(this->colorActive);
}

void Tile::setColorInActive()
{
	this->shape.setFillColor(this->colorInactive);
}

void Tile::setColorCorrect()
{
	this->shape.setFillColor(this->colorCorrect);
}

void Tile::setColorIncorrect()
{
	this->shape.setFillColor(this->colorIncorrect);
}


//Function to check for tile selection

void Tile::update(Vector2f& mousePosView, const bool lmb_pressed)
{

	pressed = false;
	const Color shapeColor = shape.getFillColor();

	if (shape.getGlobalBounds().contains(mousePosView)) {  //Hover
		shape.setFillColor(Color(shapeColor.r, shapeColor.g, shapeColor.b, alphaHover));

		if (lmb_pressed) { //Mouse Click
			pop.play();
			shape.setFillColor(Color(shapeColor.r, shapeColor.g, shapeColor.b, alphaPressed)); //Tile pressed
			pressed = true;
		}
	}
	else { //Idle
		shape.setFillColor(Color(shapeColor.r, shapeColor.g, shapeColor.b, alphaIdle));
	}

}

void Tile::render(RenderTarget& target)
{
	target.draw(shape);
}
