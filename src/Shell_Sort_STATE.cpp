#include "Shell_Sort_STATE.h"



Shell_Sort_STATE::Shell_Sort_STATE() : current(-1), step(-2), isSort(false), start(0), stop_element(0)
{
	this->text->setString("Shell_Sort (delay off)");
	this->renderUpdateTime = 0.005f;
}


Shell_Sort_STATE::~Shell_Sort_STATE()
{
}

void Shell_Sort_STATE::resetSort()
{
	this->start = 0;
	this->current = -1;
	this->step = -2;
	this->isSort = false;
	this->stop_element = -1;
}

void Shell_Sort_STATE::stepSort()
{
	if (step == 0) //reset
	{
		resetSort();
	}
	else if (this->current < this->array->getSize() && this->current >= 0) //Sort
	{
		if (this->current >= this->step)
		{
			if (this->array->getArr(this->current) < this->array->getArr(this->current - this->step))
			{
				this->array->swapArr(this->current, this->current - this->step);
				this->stop_element = this->current;
				this->current -= this->step;
			}
			else
			{
				if (this->stop_element == -1)
					this->current += this->step;
				else
				{
					this->current = this->stop_element + this->step;
					this->stop_element = -1;
				}
			}
		}
		else
		{
			if (this->stop_element == -1)
				this->current += this->step;
			else
			{
				this->current = this->stop_element + this->step;
				this->stop_element = -1;
			}
		}
	}
	else
	{
		if (this->start < this->step * 2 - 1)
		{
			this->current = ++this->start;
		}
		else
		{
			this->step /= 2;
			this->current = this->start = step;
		}
	}
}

void Shell_Sort_STATE::update(float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if (this->delay)
			this->text->setString("Shell_Sort (delay on = 0.005 sec)");
		else
			this->text->setString("Shell_Sort (delay off)");

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		int size = this->array->getSize();
		if (size <= 630)
		{
			this->array->recreateArray(size + 10);
			this->array->FillNatural();
			this->array->setRenderScale(sf::VideoMode(1280, 720));

			this->resetSort();

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
		}
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
			this->step = this->array->getSize() / 2;
			this->current = this->step;
			this->start = this->current;
			this->stop_element = -1;
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

void Shell_Sort_STATE::render(sf::RenderTarget & window)
{
	window.draw(*this->text);
	if (!this->rainbow)
	{
		if (this->current == -1 && this->step == -2)
			this->array->render(window, -1, sf::Color::Green, -1, sf::Color::Red);
		else
			this->array->render(window, this->current, sf::Color::Green, this->current - this->step, sf::Color::Red);
	}
	else
	{
		if (this->current == -1 && this->step == -2)
			this->array->renderRainbow(window, -1, sf::Color::White, -1, sf::Color::White);
		else
			this->array->renderRainbow(window, this->current, sf::Color::White, this->current - this->step, sf::Color::White);
	}
}
