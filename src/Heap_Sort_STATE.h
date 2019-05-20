#pragma once

#include "State.h"
class Heap_Sort_STATE :
	public State
{
protected:
	int current;
	
	bool isSort;
	bool correctTree;
	int current_Tree;

	int phase;
public:
	Heap_Sort_STATE();
	virtual ~Heap_Sort_STATE();

	void resetSort();

	void stepSort();
	void stepTree(int i, int n);

	void update(float &dt);
	void render(sf::RenderTarget &window);
};

