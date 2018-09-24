#include "pch.h"
#include "kpMap.h"
#include <iostream>

kpMap::kpMap(int _screenWidth, int _screenHeight, bool _debug) {
	debug = _debug;
	screenHeight = _screenHeight;
	screenWidth = _screenWidth;
}

sf::VertexArray kpMap::getRoad() {
	//1200, 600
	sf::VertexArray lines(sf::Lines, 32);
	lines[0].color = sf::Color::Red;
	lines[0].position = sf::Vector2f(0,300);
	lines[1].position = sf::Vector2f(600, 300);


	lines[2].color = sf::Color::Red;
	lines[2].position = sf::Vector2f(600, 0);
	lines[3].position = sf::Vector2f(600, 300);

	lines[4].color = sf::Color::Red;
	lines[4].position = sf::Vector2f(1200, 300);
	lines[5].position = sf::Vector2f(600, 300);

	lines[6].color = sf::Color::Red;
	lines[6].position = sf::Vector2f(600, 600);
	lines[7].position = sf::Vector2f(600, 300);

	//Left, 1
	lines[8].color = sf::Color::Blue;
	lines[8].position = sf::Vector2f(0, 200);
	lines[9].position = sf::Vector2f(500, 200);

	//Left, 2
	lines[10].color = sf::Color::Blue;
	lines[10].position = sf::Vector2f(0, 400);
	lines[11].position = sf::Vector2f(500, 400);

	//Up, 1
	lines[12].color = sf::Color::Blue;
	lines[12].position = sf::Vector2f(500, 0);
	lines[13].position = sf::Vector2f(500, 200);

	//Up, 2
	lines[14].color = sf::Color::Blue;
	lines[14].position = sf::Vector2f(700, 0);
	lines[15].position = sf::Vector2f(700, 200);

	//Down, 1
	lines[16].color = sf::Color::Blue;
	lines[16].position = sf::Vector2f(500, 600);
	lines[17].position = sf::Vector2f(500, 400);

	//Down, 2
	lines[18].color = sf::Color::Blue;
	lines[18].position = sf::Vector2f(700, 600);
	lines[19].position = sf::Vector2f(700, 400);

	//Right, 1
	lines[20].color = sf::Color::Blue;
	lines[20].position = sf::Vector2f(1200, 200);
	lines[21].position = sf::Vector2f(700, 200);

	//Right, 2
	lines[22].color = sf::Color::Blue;
	lines[22].position = sf::Vector2f(1200, 400);
	lines[23].position = sf::Vector2f(700, 400);
	return lines;


}
sf::VertexArray kpMap::getDebugLines(int space) {
	int linesWLen, linesHLen;

	linesWLen = screenWidth / space * 2;
	linesHLen = screenHeight / space * 2;

	sf::VertexArray linesW(sf::Lines, linesWLen);
	int i;
	for (i = 0; i < linesWLen; i+=2) {
		linesW[i].position = sf::Vector2f(i * space, 0);
		linesW[i + 1].position = sf::Vector2f(i * space, screenHeight);
		linesW[i].color = sf::Color(0, 255, 0, 30);
		linesW[i+1].color = sf::Color(0, 255, 0, 30);

	}

	sf::VertexArray linesH(sf::Lines, linesHLen);
	for (i = 0; i < linesHLen; i += 2) {
		linesH[i].position = sf::Vector2f(0, i * space);
		linesH[i+1].position = sf::Vector2f(screenWidth, i * space);

		linesH[i].color = sf::Color(0, 255, 0, 30);
		linesH[i+1].color = sf::Color(0, 255, 0, 30);

	}

	sf::VertexArray linesWH(sf::Lines, linesWLen + linesHLen);
	for (i = 0; i < linesWLen; i++) {
		linesWH[i] = linesW[i];
		
	}
	for (i = 0; i < linesHLen; i++) {
		linesWH[linesWLen + i] = linesH[i];
	}
	return linesWH;
}