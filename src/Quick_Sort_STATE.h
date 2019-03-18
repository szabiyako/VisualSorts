#pragma once

#include <stack>
#include "State.h"
class Quick_Sort_STATE :
	public State
{
protected:
	int main_element;
	int main_index;
	bool reset_step;
	bool isSort;

	int left;
	int right;
	int middle;

	int main_left;
	int main_right;

	struct Positions
	{
		unsigned short int left;
		unsigned short int right;

		Positions()	{}
		Positions(unsigned short int l, unsigned short int r) : left(l), right(r)
		{
		}
		void set(unsigned short int l, unsigned short int r)
		{
			left = l;
			right = r;
		}
	};

	std::stack<Positions> *Stack;
public:
	Quick_Sort_STATE();
	virtual ~Quick_Sort_STATE();

	void resetSort();

	void split(int left, int right);
	void stepSort();

	void update(float &dt);
	void render(sf::RenderTarget &window);
};

