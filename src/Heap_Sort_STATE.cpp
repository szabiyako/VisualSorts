#include "Heap_Sort_STATE.h"



Heap_Sort_STATE::Heap_Sort_STATE() : current(-1), isSort(false), correctTree(false), current_Tree(-1), phase(0)
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
	this->phase = 0;
}

void Heap_Sort_STATE::stepSort()
{
	int n = this->array->getSize();
	if (phase == 0)
	{
		current = n / 2 - 1;
		phase = 1;
	}
	// Build heap (rearrange array) 
	else if (phase == 1)
	{
		/*for (int i = n / 2 - 1; i >= 0; i--)
			stepTree(i, n);*/
		if (current >= 0)
		{
			stepTree(current, n);
			current--;
		}
		else
		{
			phase = 2;
			current = n - 1;
		}
	}

	//// One by one extract an element from heap 
	//for (int i = n - 1; i >= 0; i--)
	//{
	//	// Move current root to end 
	//	this->array->swapArr(0, i);

	//	// call max heapify on the reduced heap 
	//	stepTree(0, i);
	//}
	else if (phase == 2)
	{
		if (current >= 0)
		{
			this->array->swapArr(0, current);
			stepTree(0, current);
			current--;
		}
		else
		{
			phase = 3;
		}
	}
	else if (phase == 3)
		this->isSort = false;
}

void Heap_Sort_STATE::stepTree(int i, int n)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && array->getArr(l) > array->getArr(largest))
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && array->getArr(r) > array->getArr(largest))
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		array->swapArr(i, largest);

		// Recursively heapify the affected sub-tree 
		this->stepTree(largest, n);
	}
}

void Heap_Sort_STATE::update(float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if (this->delay)
			this->text->setString("Heap_Sort (delay on = 0.02 sec)");
		else
			this->text->setString("Heap_Sort (delay off)");

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
