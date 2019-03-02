#pragma once

#include <stack>
#include "State.h"

class Merge_Sort_STATE :
	public State
{
protected:
	bool isSort;
	int left;
	int middle;
	int right;
	int current;

	struct Positions
	{
		unsigned short int left;
		unsigned short int right;

		Positions(unsigned short int l, unsigned short int r) : left(l), right(r)
		{
		}
	};

	std::stack<Positions> *Stack;
	Array<int> *temp;
public:
	Merge_Sort_STATE();
	virtual ~Merge_Sort_STATE();

	void resetSort();

	void split(int& left, int& middle, int& right);
	void stepSort();

	void update(float &dt);
	void render(sf::RenderTarget &window);
};

