#pragma once

#include "State.h"
class Shell_Sort_STATE :
	public State
{
protected:
	int current;
	int start;
	int step;
	bool isSort;
	int stop_element;
public:
	Shell_Sort_STATE();
	virtual ~Shell_Sort_STATE();

	void resetSort();

	void stepSort();

	void update(float &dt);
	void render(sf::RenderTarget &window);
};

