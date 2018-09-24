#include "pch.h"
#include "kpCarObject.h"
#include "kpLightsSystem.h"
#include "kpMap.h"
#include "kpHud.h"
#include "kpDebug.h"
#include "kpTextures.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	srand(static_cast<long int>(time(NULL)));
	bool _settings_debugLinesEnabled = false;
	bool _settings_hudEnabled = true;
	bool _settings_mouseHudEnabled = true;
	bool _settings_fpsLimitEnabled = true;
	bool _debug_switchlight = false;
	int i;

	std::cout << "Setting debugger...\n";
	kpDebug _kpDebug;
	_kpDebug.setLocation("main");
	_kpDebug.sendMessage("Debugger: OK!");

	_kpDebug.sendMessage("Setting window...");
	int windowWidth = 1200;
	int windowHeight = windowWidth / 2;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kruispunt");
	sf::Vector2i mousePosition;
	sf::Clock deltaClock;
	sf::Clock lightsClock;
	
	_kpDebug.sendMessage("Setting FPS Counter...");
	sf::Clock mClock;
	unsigned int mFrame;
	unsigned int mFps;
	mFrame = 0; mFps = 0;

	_kpDebug.sendMessage("Loading textures...");
	kpTextures _kpTextures;
	_kpTextures.loadTextures();

	_kpDebug.sendMessage("Initializing map...");
	kpMap _kpMap(windowWidth, windowHeight, false);

	_kpDebug.sendMessage("Generating one debug car");
	kpCarObject carsArray[12];
	size_t carsArrayLen = sizeof(carsArray) / sizeof(carsArray[0]);
	_kpDebug.sendMessage("carsArray size is " + std::to_string(carsArrayLen));

	carsArray[0].initCar(windowWidth, windowHeight, 0, 1, "Consolas.ttf");
	carsArray[1].initCar(windowWidth, windowHeight, 0, 2, "Consolas.ttf");
	carsArray[2].initCar(windowWidth, windowHeight, 0, 3, "Consolas.ttf");
	carsArray[3].initCar(windowWidth, windowHeight, 1, 0, "Consolas.ttf");
	carsArray[4].initCar(windowWidth, windowHeight, 1, 2, "Consolas.ttf");
	carsArray[5].initCar(windowWidth, windowHeight, 1, 3, "Consolas.ttf");
	carsArray[6].initCar(windowWidth, windowHeight, 2, 0, "Consolas.ttf");
	carsArray[7].initCar(windowWidth, windowHeight, 2, 1, "Consolas.ttf");
	carsArray[8].initCar(windowWidth, windowHeight, 2, 3, "Consolas.ttf");
	carsArray[9].initCar(windowWidth, windowHeight, 3, 0, "Consolas.ttf");
	carsArray[10].initCar(windowWidth, windowHeight, 3, 1, "Consolas.ttf");
	carsArray[11].initCar(windowWidth, windowHeight, 3, 2, "Consolas.ttf");



	/*_kpDebug.sendMessage("Generating cars...");
	kpCarObject carsArray[10];
	size_t carsArrayLen = sizeof(carsArray) / sizeof(carsArray[0]);
	_kpDebug.sendMessage("carsArray size is "+std::to_string(carsArrayLen));
	int i;
	for (i = 0; i < static_cast<int>(carsArrayLen); i++) {
		
		bool generatedTwoDifferent = false;
		int startDirection, endDirection;
		while (!generatedTwoDifferent) {
			startDirection = rand() % (3 - 0 + 1) + 0;
			endDirection = rand() % (3 - 0 + 1) + 0;
			if (startDirection != endDirection) {
				generatedTwoDifferent = true;
			}
		}
		
		_kpDebug.sendMessage("Generating");
		carsArray[i].initCar(startDirection, endDirection);
	}
	*/
	_kpDebug.sendMessage("Generating lights...");
	kpLightsSystem _kpLightsSystem(
		_kpTextures.getTexture(0, 0),
		_kpTextures.getTexture(0, 1),
		_kpTextures.getTexture(0, 2),
		_kpTextures.getTexture(0, 3));
	int _LightsState[4];
	for (i = 0; i < 4; i++) {
		_LightsState[i] = _kpLightsSystem.getLightState(i);
	}
	


	_kpDebug.sendMessage("Initializing HUD...");
	kpHud _kpHud("Consolas.ttf", 12, sf::Color::Red, sf::Vector2f(0, 0), 12, sf::Color::Green);
	_kpHud.updateHud("Hello World\nAnother line!\nVersion: -1");

	
	//lightsClock
	lightsClock.restart().asSeconds();

	int daycycle = 0;
	while (window.isOpen())
	{
		
		if (daycycle > 256) {
			daycycle = 0;
		}
		else {
			daycycle++;
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//deltaClock
		float dt = deltaClock.restart().asSeconds();

		//Mouse Handling
		mousePosition = sf::Mouse::getPosition(window);

		//Keyboard Handling
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			_settings_debugLinesEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_settings_debugLinesEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_settings_mouseHudEnabled = false;
			_settings_hudEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_settings_mouseHudEnabled = true;
			_settings_hudEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			_settings_fpsLimitEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			_settings_fpsLimitEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			_debug_switchlight = true;
		}

		//Perform logic

		///Lights
		if (lightsClock.getElapsedTime().asSeconds() > 1.f) {
			lightsClock.restart().asSeconds();
			_kpLightsSystem.performLogic();
			for (i = 0; i < 4; i++) {
				_LightsState[i] = _kpLightsSystem.getLightState(i);
			}
		}
		///Cars
		for (i = 0; i < static_cast<int>(carsArrayLen); i++) {
			carsArray[i].second_PerformLogic(_LightsState, dt);
			//carsArray[i].captureMovement(); //MEMORY LEAK
		}



		//Perform logic - HUD
		_kpHud.updateHud("Q/W - Debug lines\nA/S - Hud\nZ/X - FPS Limit\nFPS: "+std::to_string(mFps));
		_kpHud.updateMouseHud("", mousePosition);


		//Update every car movement
		for (i = 0; i < static_cast<int>(carsArrayLen); i++) {
			//carsArray[i].update();
			carsArray[i].second_moveCar(dt);
		}

		//Update every light
		_kpLightsSystem.applyActions();


		//Clear screen
		window.clear(sf::Color(128, 128, 128, 255));


		//Draw main things
		window.draw(_kpMap.getRoad());
		for (i = 0; i < static_cast<int>(carsArrayLen); i++) {
			window.draw(carsArray[i].getShape());
			window.draw(carsArray[i].getDrawInformation());
		}
		for (i = 0; i < 4; i++) {
			window.draw(_kpLightsSystem.getSprite(i));
		}


		sf::RectangleShape night;
		night.setSize(sf::Vector2f(windowWidth, windowHeight));
		night.setPosition(sf::Vector2f(0.f, 0.f));
		night.setFillColor(sf::Color(0, 0, 0, daycycle));
		window.draw(night);

		//Draw optional things
		if (_settings_debugLinesEnabled) {
			window.draw(_kpMap.getDebugLines(50));
		}
		if (_settings_hudEnabled) {
			window.draw(_kpHud.getHud());
		}
		if (_settings_mouseHudEnabled) {
			window.draw(_kpHud.getMouseHud());
		}
		if (_settings_fpsLimitEnabled) {
			window.setFramerateLimit(60);
		}
		else {
			window.setFramerateLimit(-1);
		}
		//Display everything
		window.display();


		//FPS Counter Logic
		if (mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}
		++mFrame;

	}
}
