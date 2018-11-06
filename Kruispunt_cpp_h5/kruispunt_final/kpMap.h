#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "kpConfig.h"
#include "kpDebug.h"

class kpMap {
private:
	bool debug;
	int screenWidth;
	int screenHeight;

	kpConfig _kpConfig;
	kpDebug _kpDebug;
public:
	kpMap(int _screenWidth, int _screenHeight, bool _debug);
	sf::VertexArray getDebugLines(int space);
	sf::VertexArray getRoad();
};