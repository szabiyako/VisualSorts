#include "Selection_Sort_STATE.h"



Selection_Sort_STATE::Selection_Sort_STATE() : isSort(false), i(-1), j(-1), min(0)
{
	this->text->setString("Selection_Sort (delay off)");
	this->renderUpdateTime = 0.002f;
}


Selection_Sort_STATE::~Selection_Sort_STATE()
{
}

void Selection_Sort_STATE::update(float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->delay = this->delay ? false : true;
		if (this->delay)
			this->text->setString("Selection_Sort (delay on = 0.002 sec)");
		else
			this->text->setString("Selection_Sort (delay off)");

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

			this->isSort = false;
			this->i = -1;
			this->j = -1;
			this->min = 0;

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

			this->isSort = false;
			this->i = -1;
			this->j = -1;
			this->min = 0;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		this->isSort = false;
		this->array->RandomSwaps(1);
		this->i = -1;
		this->j = -1;
		this->min = 0;
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		this->isSort = false;
		this->array->RandomSwaps(1);
		this->i = -1;
		this->j = -1;
		this->min = 0;
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
			this->i = 0;
			this->j = 1;
			this->min = 0;
		}
		if (delay)
			this->currentRenderUpdateTime += dt;

		if (delay)
		{
			if (this->currentRenderUpdateTime > this->renderUpdateTime)
			{
				this->currentRenderUpdateTime = 0;
				if (this->i < this->array->getSize() - 1)
				{
					if (this->j < this->array->getSize())
					{
						if ((this->array->getArr(j)) < (this->array->getArr(min)))
							min = this->j;

						this->j++;
					}
					else
					{
						this->array->swapArr(i, min);
						this->i++;
						this->j = this->i + 1;
						this->min = this->i;
					}
				}
				else
				{
					this->isSort = false;
					this->i = -1;
					this->j = -1;
					this->min = 0;
				}
			}
		}
		else
		{
			if (this->i < this->array->getSize() - 1)
			{
				if (this->j < this->array->getSize())
				{
					if ((this->array->getArr(j)) < (this->array->getArr(min)))
						min = this->j;

					this->j++;
				}
				else
				{
					this->array->swapArr(i, min);
					this->i++;
					this->j = this->i + 1;
					this->min = this->i;
				}
			}
			else
			{
				this->isSort = false;
				this->i = -1;
				this->j = -1;
				this->min = 0;
			}
		}
	}
}


void Selection_Sort_STATE::render(sf::RenderTarget &window)
{
	window.draw(*this->text);
	if (!this->rainbow)
		this->array->render(window, this->i, sf::Color::Green, this->j, sf::Color::Red);
	else
		this->array->renderRainbow(window, this->i, sf::Color::White, this->j, sf::Color::White);
}
