#include "State.h"



State::State() : rainbow(false), renderUpdateTime(0.3f), currentRenderUpdateTime(0.f), delay(false)
{
	this->array = new Array<int>(256);
	this->array->FillNatural();

	this->font = new sf::Font();
	this->font->loadFromFile("resources/fonts/arial.ttf");
	this->text = new sf::Text("", *this->font, 10);

	this->text->setPosition(sf::Vector2f(400.f, 0.f));
}


State::~State()
{
	delete this->array;

	delete this->text;
	delete this->font;
}
