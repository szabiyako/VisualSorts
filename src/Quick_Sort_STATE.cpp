#include "Quick_Sort_STATE.h"



Quick_Sort_STATE::Quick_Sort_STATE() : Stack(nullptr), isSort(false), reset_step(true), left(0), right(0), middle(0), main_element(0), main_index(0), main_left(0), main_right(0)
{
	this->Stack = new std::stack<Positions>;
	this->text->setString("Quick_Sort (delay off)");
	this->renderUpdateTime = 0.02f;
}


Quick_Sort_STATE::~Quick_Sort_STATE()
{
	delete this->Stack;
}

void Quick_Sort_STATE::resetSort()
{
	this->isSort = false;
	this->reset_step = true;
	this->left = -1;
	this->right = -1;
	this->middle = -1;
	this->main_index = -1;
	this->main_left = 0;
	this->main_right = 0;
	if (this->Stack != nullptr)
	{
		delete this->Stack;
		this->Stack = new std::stack<Positions>();
	}
}

void Quick_Sort_STATE::split(int left, int right)
{
	if (left < right)
	{
		Positions temp(left, right);
		Stack->push(temp);
	}
}

void Quick_Sort_STATE::stepSort()
{
	
	if (this->reset_step)
	{
		if (this->Stack->empty())
		{
			this->resetSort();
		}
		else
		{
			this->main_index = this->Stack->top().left;
			this->main_element = this->array->getArr(main_index);
			Positions temp();
			this->left = main_index + 1;
			this->right = this->Stack->top().right;
			this->main_left = left - 1;
			this->main_right = right;

			this->Stack->pop();
			this->reset_step = false;
		}
		
	}
	if (!this->reset_step)
	{
		if (this->left >= this->right - 1) //Sort next Positions
		{
			if (this->left == this->right)
			{
				if (this->array->getArr(this->left) >= this->main_element)
				{
					this->array->swapArr(this->main_index, this->left - 1);
					this->main_index = this->left - 1;

					this->split(this->main_index + 1, this->main_right);
					this->split(this->main_left, this->main_index - 1);
				}
				else
				{
					this->array->swapArr(this->main_index, this->left);
					this->main_index = this->left;

					this->split(this->main_index + 1, this->main_right);
					this->split(this->main_left, this->main_index - 1);
				}
			}
			else if (this->array->getArr(this->left) < this->main_element && this->array->getArr(this->right) < this->main_element)
			{
				this->array->swapArr(this->main_index, this->right);
				this->main_index = this->right;

				this->split(this->main_index + 1, this->main_right);
				this->split(this->main_left, this->main_index - 1);
			}
			else if (this->array->getArr(this->left) >= this->main_element && this->array->getArr(this->right) >= this->main_element)
			{
				this->array->swapArr(this->main_index, this->left - 1);
				this->main_index = this->left - 1;

				this->split(this->main_index + 1, this->main_right);
				this->split(this->main_left, this->main_index - 1);
			}
			else if (this->array->getArr(this->left) > this->array->getArr(this->right))
			{
				this->array->swapArr(this->left, this->right);

				this->array->swapArr(this->main_index, this->left);
				this->main_index = this->left;

				this->split(this->main_index + 1, this->main_right);
				this->split(this->main_left, this->main_index - 1);
			}
			else
			{
				this->array->swapArr(this->main_index, this->left);
				this->main_index = this->left;

				this->split(this->main_index + 1, this->main_right);
				this->split(this->main_left, this->main_index - 1);
			}
			

			this->reset_step = true;
		}
		else //Sort
		{
			if (this->array->getArr(this->left) < this->main_element)
			{
				this->left++;
			}
			else
			{
				if (this->array->getArr(this->right) >= this->main_element)
				{
					this->right--;
				}
				else if (this->array->getArr(this->left) > this->array->getArr(this->right) && this->array->getArr(this->left) > this->main_element && this->array->getArr(this->right) <= this->main_element)
				{
					this->array->swapArr(this->left++, this->right--);
				}
				else if (this->array->getArr(this->left) >= this->main_element && this->array->getArr(this->right) >= this->main_element)
				{
					this->right--;
				}
				else if (this->array->getArr(this->left) < this->main_element && this->array->getArr(this->right) < this->main_element)
				{
					this->left++;
				}
			}
		}
	}
}

void Quick_Sort_STATE::update(float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if (this->delay)
			this->text->setString("Quick_Sort(delay on = 0.02 sec)");
		else
			this->text->setString("Quick_Sort (delay off)");

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
			this->resetSort();
			this->isSort = true;
			Positions temp(0, this->array->getSize() - 1);
			this->Stack->push(temp);
		}

		if (delay)
			this->currentRenderUpdateTime += dt;

		if (delay)
		{
			if (this->currentRenderUpdateTime > this->renderUpdateTime)
			{
				this->currentRenderUpdateTime = 0;

				this->stepSort();
			}
		}
		else
		{
			this->stepSort();
		}
	}
}

void Quick_Sort_STATE::render(sf::RenderTarget & window)
{
	window.draw(*this->text);
	if (!this->rainbow)
		this->array->render(window, this->left, sf::Color::Green, this->right, sf::Color::Red, this->main_index, sf::Color::Magenta);
	else
		this->array->renderRainbow(window, this->left, sf::Color::White, this->right, sf::Color::White, this->main_index, sf::Color(255, 255, 255, 100));
}
