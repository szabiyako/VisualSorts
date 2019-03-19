#include "Heap_Sort_STATE.h"



Heap_Sort_STATE::Heap_Sort_STATE() : current(-1), isSort(false), correctTree(false), current_Tree(-1)
{
	this->text->setString("Heap_Sort (delay off)");
	this->renderUpdateTime = 0.02f;
}


Heap_Sort_STATE::~Heap_Sort_STATE()
{
}

void Heap_Sort_STATE::resetSort()
{
	this->current = -1;
	this->current_Tree = -1;
	this->isSort = false;
	this->correctTree = false;
}

void Heap_Sort_STATE::stepSort()
{

}

void Heap_Sort_STATE::update(float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if (this->delay)
			this->text->setString("Heap_Sort(delay on = 0.02 sec)");
		else
			this->text->setString("Heap_Sort (delay off)");

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

void Heap_Sort_STATE::render(sf::RenderTarget & window)
{
	window.draw(*this->text);
	if (!this->rainbow)
		this->array->render(window, this->current, sf::Color::Green, -1, sf::Color::Red);
	else
		this->array->renderRainbow(window, this->current, sf::Color::White, -1, sf::Color::White);
}
