#pragma once

#include"Array.h"

class State
{
protected:
	Array<int> *array;

	sf::Font *font;
	sf::Text *text;

	bool delay;
	bool rainbow;
	float renderUpdateTime;

	float currentRenderUpdateTime;
public:
	State();
	virtual ~State();

	virtual void update(float &dt) = 0;
	virtual void render(sf::RenderTarget &window) = 0;
};

