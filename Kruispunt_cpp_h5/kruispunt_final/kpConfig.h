#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class kpConfig {
public:
	bool debugInfoEnabled = true;
	bool hudEnabled = true;
	bool fpsLimitEnabled = false;
	

	int VERBOSE = 1;
	int DEBUG = 2;
	int INFO = 3;
	int ERROR = 4;
	int debugMinimumLevel = DEBUG;

	int windowWidth = 1200;
	int windowHeight = 600;
	sf::VideoMode windowVideoMode = sf::VideoMode(windowWidth, windowHeight);
	sf::String windowTitle = sf::String("Kruispunt");

	bool kpMap_debugLines = true;

	std::string fontFile = "res/font_consolas.ttf";

	int carModel = 0;

};