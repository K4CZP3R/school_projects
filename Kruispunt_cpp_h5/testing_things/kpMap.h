#pragma once
#include <SFML/Graphics.hpp>

class kpMap {
private:
	bool debug;
	int screenWidth;
	int screenHeight;
public:
	kpMap(int _screenWidth, int _screenHeight, bool _debug);
	sf::VertexArray getDebugLines(int space);
	sf::VertexArray getRoad();
};