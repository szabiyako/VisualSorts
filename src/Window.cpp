#include "Window.h"

//Initialazers
void Window::InitWindow()
{
	std::ifstream input("configs/window.ini");

	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);
	unsigned short int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (input.is_open())
	{
		std::getline(input, title);
		input >> window_bounds.width >> window_bounds.height;
		input >> framerate_limit >> vertical_sync_enabled;
	}

	input.close();

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Window::InitSFMLevent()
{
	sfEvent = new sf::Event();
}

void Window::InitClock()
{
	dtClock = new sf::Clock();
}

void Window::InitFPS()
{
	fps = new FPS("resources/fonts/arial.ttf");
}

void Window::InitSTATE()
{
	if (this->state != nullptr)
		delete this->state;

	if (sortType == 0)
		this->state = new Selection_Sort_STATE();
	else if (sortType == 1)
		this->state = new Merge_Sort_STATE();
}

//Constructor/destructor
Window::Window() : dt(0), sortType(0)
{
	this->InitWindow();
	this->InitSFMLevent();
	this->InitClock();
	this->InitFPS();

	this->InitSTATE();
}

//Functions
Window::~Window()
{
	delete this->window;
	delete this->dtClock;
	delete this->fps;
	delete this->sfEvent;

	delete this->state;
}

void Window::updateState()
{
	int count_sorts = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->sortType = this->sortType == 0 ? count_sorts - 1 : sortType - 1;
		this->InitSTATE();

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->sortType = this->sortType == count_sorts - 1 ? 0 : sortType + 1;
		this->InitSTATE();
		
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	}
}

void Window::updateDt()
{
	this->dt = dtClock->restart().asSeconds();
}

void Window::updateSFMLevents()
{
	while (this->window->pollEvent(*this->sfEvent))
	{
		if (this->sfEvent->type == sf::Event::Closed)
			this->window->close();
	}
}

void Window::update()
{
	this->updateSFMLevents();
	this->fps->setFpsSmooth(dt);
	this->updateState();

	this->state->update(dt);
}

void Window::render()
{
	this->window->clear();

	///Render
	this->state->render(*this->window);
	this->fps->render(*this->window);

	this->window->display();
}

void Window::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
