#include "Window.h"

//Hide console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	randomize();

	Window window;
	window.run();

	return 0;
}