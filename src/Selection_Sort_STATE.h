#pragma once
#include "State.h"
class Selection_Sort_STATE :
	public State
{
private:
	bool isSort;
	int i;
	int j;
	int min;
public:
	Selection_Sort_STATE();
	virtual ~Selection_Sort_STATE();

	void update(float &dt);
	void render(sf::RenderTarget &window);
};

