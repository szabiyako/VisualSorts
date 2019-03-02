#include "Merge_Sort_STATE.h"



Merge_Sort_STATE::Merge_Sort_STATE() : isSort(false), left(-1), middle(-1), right(-1), current(-1), temp(nullptr)
{
	this->text->setString("Merge_Sort (delay off)");
	this->renderUpdateTime = 0.02f;
	this->Stack = new std::stack<Positions>();
}


Merge_Sort_STATE::~Merge_Sort_STATE()
{
	delete this->Stack;
}

void Merge_Sort_STATE::resetSort()
{
	this->isSort = false;
	this->left = -1;
	this->current = -1;
	this->right = -1;
	this->middle = -1;
	if (this->temp != nullptr)
	{
		delete this->temp;
		this->temp = nullptr;
	}
	if (this->Stack != nullptr)
	{
		delete this->Stack;
		this->Stack = new std::stack<Positions>();
	}
}

void Merge_Sort_STATE::split(int &left, int &middle, int &right)
{
	if (right - left + 1 == 3)
	{
		Positions temp((unsigned short int)left, (unsigned short int)(left + 1));
		this->Stack->push(temp);
	}
	else if (left < right - 1)
	{
		int mid_temp_r = (int)((right + middle) / 2 + 1);
		Positions temp((unsigned short int)middle, (unsigned short int)right);
		if (middle != right)
		{
			this->Stack->push(temp);
			split(middle, mid_temp_r, right);
		}

		int right_l = middle - 1;
		int mid_temp_l = (int)((right_l + left) / 2 + 1);
		temp.left = (unsigned short int)left;
		temp.right = (unsigned short int)right_l;

		if (left != right_l)
		{
			this->Stack->push(temp);
			split(left, mid_temp_l, right_l);
		}
	}
}

void Merge_Sort_STATE::stepSort()
{
	if (this->temp == nullptr)
	{
		//initialisation
		this->current = this->Stack->top().left;
		int size = this->Stack->top().right - this->current + 1;

		this->temp = new Array<int>(size);
		this->temp->copyFill(this->array, this->current);

		this->middle = (int)((size - 1) / 2 + 1);

		this->left = 0;
		this->right = middle;
	}
	else
	{
		//Sort
		int size = this->temp->getSize();

		if (this->left < this->middle && this->right < size)
		{
			int l = this->temp->getArr(this->left);
			int r = this->temp->getArr(this->right);

			if (l < r)
			{
				this->array->setArr(this->current++, l);
				this->left++;
			}
			else
			{
				this->array->setArr(this->current++, r);
				this->right++;
			}
		}
		else if (this->right < size)
		{
			int r = this->temp->getArr(this->right);
			this->array->setArr(this->current++, r);
			this->right++;
		}
		else if (this->left < this->middle)
		{
			int l = this->temp->getArr(this->left);
			this->array->setArr(this->current++, l);
			this->left++;
		}
		else
		{
			delete this->temp;
			this->temp = nullptr;
			this->Stack->pop();
		}
	}
}

void Merge_Sort_STATE::update(float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if  (this->delay)
			this->text->setString("Merge_Sort (delay on = 0.02 sec)");
		else
			this->text->setString("Merge_Sort (delay off)");

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		int size = this->array->getSize();
		this->array->recreateArray(size + 10);
		this->array->FillNatural();
		this->array->setRenderScale(sf::VideoMode(1280, 720));

		this->resetSort();

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		int size = this->array->getSize();
		if (size > 10)
		{
			this->array->recreateArray(size - 10);
			this->array->FillNatural();
			this->array->setRenderScale(sf::VideoMode(1280, 720));

			this->resetSort();

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		int size = this->array->getSize();
		this->array->recreateArray(size);
		this->array->FillNatural();
		this->array->RandomSwaps(1);

		this->resetSort();

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->rainbow = this->rainbow ? false : true;
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::R));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || this->isSort)
	{
		if (!this->isSort)
		{
			this->isSort = true;
			this->left = 0;
			this->right = this->array->getSize() - 1;
			this->current = 0;
			
			int mid_temp = ((this->right - this->left) / 2 + 1);
			Positions temp((unsigned short int)this->left, (unsigned short int)this->right);
			this->Stack->push(temp);
			this->split(this->left, mid_temp, this->right);
		}

		if (delay)
			this->currentRenderUpdateTime += dt;

		if (delay)
		{
			if (this->currentRenderUpdateTime > this->renderUpdateTime)
			{
				this->currentRenderUpdateTime = 0;

				if (!Stack->empty())
					this->stepSort();
				else
					this->isSort = false;
			}
		}
		else
		{
			if (!Stack->empty())
				this->stepSort();
			else
				this->isSort = false;
		}
	}
}

void Merge_Sort_STATE::render(sf::RenderTarget & window)
{
	window.draw(*this->text);
	if (!this->rainbow)
		this->array->render(window, this->current, sf::Color::Green, -1, sf::Color::White);
	else
		this->array->renderRainbow(window, this->current, sf::Color::White, -1, sf::Color::White);
}
