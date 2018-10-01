#include "pch.h"
#include "kpCarObject.h"
#include "kpCarSystem.h"
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
	bool _settings_debugHudEnabled = true;
	bool _settings_hudEnabled = true;
	bool _settings_fpsLimitEnabled = false;
	bool _debug_switchlight = false;
	int i,o;

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
	unsigned int maxFps;
	mFrame = 0; mFps = 0; maxFps = 0;

	_kpDebug.sendMessage("Loading textures...");
	kpTextures _kpTextures;
	_kpTextures.loadTextures();

	_kpDebug.sendMessage("Background texture..."); //make module for it
	sf::Sprite bg;
	sf::Texture t_bg = _kpTextures.getBackgroundTexture(0);
	float scaleX = (float)window.getSize().x / t_bg.getSize().x;
	float scaleY = (float)window.getSize().y / t_bg.getSize().y;
	bg.setTexture(t_bg);
	bg.setScale(scaleX, scaleY);


	_kpDebug.sendMessage("Initializing map...");
	kpMap _kpMap(windowWidth, windowHeight, false);


	_kpDebug.sendMessage("Initializing cars...");
	kpCarSystem _kpCarSystem(windowWidth, windowHeight, "Consolas.ttf",
		_kpTextures.getCarTexture(0),
		_kpTextures.getCarTexture(1),
		_kpTextures.getCarTexture(2),
		_kpTextures.getCarTexture(3));

	for (i = 0; i < _kpCarSystem.getNCar(); i++) {
		_kpDebug.sendMessage("Car (" + std::to_string(i) + ") init!");
		_kpCarSystem.doInitCar(i, 0, 1, 1);

	}
	

	_kpDebug.sendMessage("Generating lights...");
	kpLightsSystem _kpLightsSystem(
		_kpTextures.getLightsTexture(0),
		_kpTextures.getLightsTexture(1),
		_kpTextures.getLightsTexture(2),
		_kpTextures.getLightsTexture(3));

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
			_settings_debugHudEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_settings_debugHudEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_settings_hudEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_settings_hudEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			_settings_fpsLimitEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			_settings_fpsLimitEnabled = true;
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
		_kpCarSystem.doRegenerateCars();
		_kpCarSystem.doPerformLogic(_LightsState, dt);
		


		//Perform logic - HUD
		_kpHud.updateHud("Q/W - Debug HUD\nA/S - Hud\nZ/X - FPS Limit\nFPS: "+std::to_string(mFps)+"\nmax fps: "+std::to_string(maxFps));
		_kpHud.updateMouseHud("", mousePosition);

		//Update every light
		_kpLightsSystem.applyActions();


		
		//--- DRAW ---//

		//Clear screen
		window.clear();
		//Draw background
		window.draw(bg);



		//Draw main things
		window.draw(_kpMap.getRoad());
		for (i = 0; i < _kpCarSystem.getNCar(); i++) {
			window.draw(_kpCarSystem.doGetShapeToDraw(i));
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
		if (_settings_debugHudEnabled) {
			for (i = 0; i < _kpCarSystem.getNCar(); i++) {
				window.draw(_kpCarSystem.doGetCarInformation(i));
			}
			window.draw(_kpHud.getMouseHud());
		}
		if (_settings_hudEnabled) {
			window.draw(_kpHud.getHud());
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
			if (mFps > maxFps) {
				maxFps = mFps;
			}
		}
		++mFrame;

	}
}
