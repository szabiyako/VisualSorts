#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <fstream>
#include <string>

#include "DeltaTime.h"
#include "FPS.h"

#include "Selection_Sort_STATE.h"
#include "Merge_Sort_STATE.h"
#include "Quick_Sort_STATE.h"
#include "Shell_Sort_STATE.h"
#include "Heap_Sort_STATE.h"

class Window
{
private:
	//Vars
	sf::RenderWindow *window;
	sf::Event *sfEvent;
	sf::Clock *dtClock;
	float dt;
	FPS *fps;

	State *state;
	int sortType;
	//Initialazers
	void InitWindow();
	void InitSFMLevent();
	void InitClock();
	void InitFPS();

	void InitSTATE();
public:
	Window();
	virtual ~Window();

	//Functions
	void updateState();
	void updateDt();
	void updateSFMLevents();
	void update();
	void render();
	void run();
};

#endif
