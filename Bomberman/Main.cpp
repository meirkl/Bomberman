////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Menu.h"

#include <iostream>

////////////////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#else
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#endif


////////////////////////////////////////////////////////////
int main() try {
	Menu::getInstance().activate();
} catch (std::exception& e) {
	std::cerr << "Exception has been thrown: " << e.what() << '\n';
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Unknown exception has been thrown" << '\n';
	return EXIT_FAILURE;
}

