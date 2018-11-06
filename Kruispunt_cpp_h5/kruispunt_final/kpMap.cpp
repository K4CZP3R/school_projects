#include "pch.h"
#include "kpMap.h"

kpMap::kpMap(int _screenWidth, int _screenHeight, bool _debug) {
	_kpDebug.setLocation("kpMap");
	debug = _debug;
	screenHeight = _screenHeight;
	screenWidth = _screenWidth;
}
sf::VertexArray kpMap::getRoad() {
	//_kpDebug.sendMessage("[..] Generating roadlines", _kpConfig.VERBOSE);

	//1200, 600
	sf::VertexArray lines(sf::Lines, 32);
	lines[0].color = sf::Color::Red; //Line links
	lines[0].position = sf::Vector2f(0, 315);
	lines[1].position = sf::Vector2f(600, 315);


	lines[2].color = sf::Color::Red; //Line up
	lines[2].position = sf::Vector2f(600, 0);
	lines[3].position = sf::Vector2f(600, 300);

	lines[4].color = sf::Color::Red;
	lines[4].position = sf::Vector2f(1200, 315);
	lines[5].position = sf::Vector2f(600, 315);

	lines[6].color = sf::Color::Red;
	lines[6].position = sf::Vector2f(600, 600);
	lines[7].position = sf::Vector2f(600, 300);

	//Left, 1
	lines[8].color = sf::Color::Blue; //y:250
	lines[8].position = sf::Vector2f(0, 250);
	lines[9].position = sf::Vector2f(535, 250);

	//Left, 2
	lines[10].color = sf::Color::Blue; //y:380 so: y-y/2 = 65
	lines[10].position = sf::Vector2f(0, 380);
	lines[11].position = sf::Vector2f(535, 380);

	//Up, 1
	lines[12].color = sf::Color::Blue; //x:530
	lines[12].position = sf::Vector2f(535, 0);
	lines[13].position = sf::Vector2f(535, 250);

	//Up, 2
	lines[14].color = sf::Color::Blue; //x:660 so: y-y/2 = 65
	lines[14].position = sf::Vector2f(665, 0);
	lines[15].position = sf::Vector2f(665, 250);

	//Down, 1
	lines[16].color = sf::Color::Blue; //y:535
	lines[16].position = sf::Vector2f(535, 600);
	lines[17].position = sf::Vector2f(535, 380);

	//Down, 2
	lines[18].color = sf::Color::Blue; //y:660 so: y-y/2 = 65
	lines[18].position = sf::Vector2f(665, 600);
	lines[19].position = sf::Vector2f(665, 380);

	//Right, 1
	lines[20].color = sf::Color::Blue; //y:250 
	lines[20].position = sf::Vector2f(1200, 250);
	lines[21].position = sf::Vector2f(665, 250);

	//Right, 2
	lines[22].color = sf::Color::Blue; //y:380 /65
	lines[22].position = sf::Vector2f(1200, 380);
	lines[23].position = sf::Vector2f(665, 380);

	//_kpDebug.sendMessage("[ok] Generating roadlines", _kpConfig.VERBOSE);
	return lines;


}
sf::VertexArray kpMap::getDebugLines(int space) {
	//_kpDebug.sendMessage("[..] Generating debuglines", _kpConfig.VERBOSE);
	int linesWLen, linesHLen;

	linesWLen = screenWidth / space * 2;
	linesHLen = screenHeight / space * 2;

	sf::VertexArray linesW(sf::Lines, linesWLen);
	int i;
	for (i = 0; i < linesWLen; i += 2) {
		linesW[i].position = sf::Vector2f(i * space, 0);
		linesW[i + 1].position = sf::Vector2f(i * space, screenHeight);
		linesW[i].color = sf::Color(0, 255, 0, 30);
		linesW[i + 1].color = sf::Color(0, 255, 0, 30);

	}

	sf::VertexArray linesH(sf::Lines, linesHLen);
	for (i = 0; i < linesHLen; i += 2) {
		linesH[i].position = sf::Vector2f(0, i * space);
		linesH[i + 1].position = sf::Vector2f(screenWidth, i * space);

		linesH[i].color = sf::Color(0, 255, 0, 30);
		linesH[i + 1].color = sf::Color(0, 255, 0, 30);

	}

	sf::VertexArray linesWH(sf::Lines, linesWLen + linesHLen);
	for (i = 0; i < linesWLen; i++) {
		linesWH[i] = linesW[i];

	}
	for (i = 0; i < linesHLen; i++) {
		linesWH[linesWLen + i] = linesH[i];
	}
	//_kpDebug.sendMessage("[ok] Generating debuglines", _kpConfig.VERBOSE);

	return linesWH;
}