#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "kpConfig.h"
#include "kpDebug.h"
#include "kpTextures.h"
#include "kpMap.h"
#include "kpCarSystem.h"
#include "kpLightsSystem.h"
#include "kpHud.h"
#include "kpEnvObjects.h"



int main()
{
	std::cout << "> > > > > > > > > > > > > > > > > >" << std::endl;
	std::cout << "K A C P E R ' S   K R U I S P U N T" << std::endl;
	std::cout << "> > > > > > > > > > > > > > > > > >" << std::endl;
	kpConfig _kpConfig;

	srand(static_cast<long int>(time(NULL)));
	kpDebug _kpDebug;

	_kpDebug.setLocation("main");
	_kpDebug.sendMessage("Debug module: OK!", _kpConfig.VERBOSE);
	
	_kpDebug.sendMessage("[..] Setting render window", _kpConfig.VERBOSE);
	sf::RenderWindow window(_kpConfig.windowVideoMode, _kpConfig.windowTitle);
	_kpDebug.sendMessage("[ok] Render window set!", _kpConfig.INFO);


	window.clear(sf::Color::Black);
	window.display();

	kpTextures _kpTextures;
	_kpTextures.loadLoadingTextures();


	window.clear();
	sf::Sprite bgLoadingSprite;
	sf::Texture loadingTexture = _kpTextures.getLoadingTexture(0);
	bgLoadingSprite.setTexture(loadingTexture);
	bgLoadingSprite.setScale(_kpTextures.scaleTexture(window.getSize(), loadingTexture.getSize()));
	window.draw(bgLoadingSprite);
	window.display();
	


	_kpDebug.sendMessage("[..] Definining values", _kpConfig.VERBOSE);
	sf::Vector2i mousePosition;
	sf::Clock deltaClock;
	sf::Clock lightsClock;
	_kpDebug.sendMessage("[ok] Values defined", _kpConfig.INFO);


	_kpDebug.sendMessage("[..] Loading textures", _kpConfig.VERBOSE);
	_kpTextures.loadTextures();
	
	_kpDebug.sendMessage("[..] Defining background texture", _kpConfig.VERBOSE);
	sf::Sprite bgSprite;
	sf::Texture bgTexture = _kpTextures.getBackgroundTexture(0);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(_kpTextures.scaleTexture(window.getSize(), bgTexture.getSize()));
	_kpDebug.sendMessage("[ok] Defining background texture", _kpConfig.INFO);
	_kpDebug.sendMessage("[ok] Loaded textures", _kpConfig.INFO);


	window.clear();
	loadingTexture = _kpTextures.getLoadingTexture(1);
	bgLoadingSprite.setTexture(loadingTexture);
	window.draw(bgLoadingSprite);
	window.display();

	_kpDebug.sendMessage("[..] Initializing map", _kpConfig.VERBOSE);
	kpMap _kpMap(_kpConfig.windowWidth, _kpConfig.windowHeight, _kpConfig.kpMap_debugLines);
	_kpDebug.sendMessage("[ok] Initializing map", _kpConfig.INFO);


	window.clear();
	loadingTexture = _kpTextures.getLoadingTexture(2);
	bgLoadingSprite.setTexture(loadingTexture);
	window.draw(bgLoadingSprite);
	window.display();

	_kpDebug.sendMessage("[..] Initializing cars", _kpConfig.VERBOSE);
	kpCarSystem _kpCarSystem(_kpConfig.windowWidth, _kpConfig.windowHeight);
	/*_kpCarSystem.debug_doInitCar(0, sf::Vector2f(200.f, 100.f), 1, 0, 0);
	_kpCarSystem.debug_doInitCar(1, sf::Vector2f(400.f, 200.f), 1, 0, 1);
	_kpCarSystem.debug_doInitCar(2, sf::Vector2f(600.f, 300.f), 1, 0, 2);
	_kpCarSystem.debug_setRotation(2, 45.f);
	_kpCarSystem.debug_doInitCar(3, sf::Vector2f(600.f, 300.f), 1, 0, 2);
	_kpCarSystem.debug_setRotation(3, 90.f);
	_kpCarSystem.debug_doInitCar(4, sf::Vector2f(600.f, 300.f), 1, 0, 2);
	_kpCarSystem.debug_doInitCar(5, sf::Vector2f(700.f, 300.f), 0, 0, 2);
	_kpCarSystem.debug_doInitCar(6, sf::Vector2f(800.f, 400.f), 1, 0, 3);*/
	

	_kpDebug.sendMessage("[ok] Initializing cars", _kpConfig.INFO);

	window.clear();
	loadingTexture = _kpTextures.getLoadingTexture(3);
	bgLoadingSprite.setTexture(loadingTexture);
	window.draw(bgLoadingSprite);
	window.display();

	_kpDebug.sendMessage("[..] Initializing lights", _kpConfig.VERBOSE);
	kpLightsSystem _kpLightsSystem(
		_kpTextures.getLightsTexture(0),
		_kpTextures.getLightsTexture(1),
		_kpTextures.getLightsTexture(2),
		_kpTextures.getLightsTexture(3));

	int _LightsState[4];
	for (int i = 0; i < 4; i++) {
		_LightsState[i] = _kpLightsSystem.getLightState(i);
	}
	_kpDebug.sendMessage("[ok] Initializing lights", _kpConfig.INFO);

	_kpDebug.sendMessage("[..] Initializing env objects", _kpConfig.VERBOSE);
	kpEnvObjects _kpEnvObjects;
	_kpDebug.sendMessage("[ok] Initializing env objects", _kpConfig.INFO);

	window.clear();
	loadingTexture = _kpTextures.getLoadingTexture(4);
	bgLoadingSprite.setTexture(loadingTexture);
	window.draw(bgLoadingSprite);
	window.display();

	_kpDebug.sendMessage("Initializing HUD...", 3);
	kpHud _kpHud("res/font_consolas.ttf", 12, sf::Color::Red, sf::Vector2f(0, 0), 12, sf::Color::Green);
	_kpHud.updateHud("Hello World\nAnother line!\nVersion: -1");

	_kpDebug.sendMessage("Setting FPS Counter...", 3);
	sf::Clock mClock;
	unsigned int mFrame;
	unsigned int mFps;
	unsigned int maxFps;
	mFrame = 0; mFps = 0; maxFps = 0;

	//lightsClock
	lightsClock.restart().asSeconds();
	
	int daycycle = 0;
	bool spawned1 = false;
	bool spawned2 = false;
	sf::Clock debugClock;
	sf::Clock debugCycleClock;
	bool godown = false;

	sf::Clock spawnClock;
	int nToSpawn = 0;

	bool spawned = false;
	int carsonscreen = 0;
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
			_kpConfig.debugInfoEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_kpConfig.debugInfoEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_kpConfig.hudEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_kpConfig.hudEnabled = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			_kpConfig.fpsLimitEnabled = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			_kpConfig.fpsLimitEnabled = true;
		}

		
		/*if (spawnClock.getElapsedTime().asSeconds() >= 1.f) {
			if (!spawned) {
				_kpCarSystem.doInitCar(0, //id
					1, //model
					3, //start
					0, //end
					0); //color
				spawned = true;
			}

		}*/

		if (spawnClock.getElapsedTime().asSeconds() >= 2.f) {
			if (!(nToSpawn == _kpCarSystem.getNCar())) {
				_kpCarSystem.doGenerateCar(nToSpawn);
				nToSpawn = nToSpawn + 1;
				spawnClock.restart();

				_kpDebug.sendMessage("Spawning " + std::to_string(nToSpawn), 3);
			}
		}


		
		//Perform logic

		///Lights
		if (lightsClock.getElapsedTime().asSeconds() > 1.f) {
			lightsClock.restart().asSeconds();
			_kpLightsSystem.performLogic();
			for (int i = 0; i < 4; i++) {
				_LightsState[i] = _kpLightsSystem.getLightState(i);
			}
		}

		///Cars
		_kpCarSystem.doRegenerateCars();
		_kpCarSystem.doPerformLogic(_LightsState, dt);
		for (int i = 0; i < _kpCarSystem.getNCar(); i++) {
			if (_kpCarSystem.isCarInited(i)) {
				carsonscreen += 1;
			}
		}



		//Perform logic - HUD
		_kpHud.updateHud("Q/W - Debug Info\nA/S - This Hud\nZ/X - FPS Limit\nFPS: " + std::to_string(mFps) + "\nmax fps: " + std::to_string(maxFps)+"\nCars on screen:"+std::to_string(carsonscreen));
		_kpHud.updateMouseHud("", mousePosition);

		//Update every light
		_kpLightsSystem.applyActions();



		//--- DRAW ---//

		//Clear screen
		window.clear();
		//Draw background
		window.draw(bgSprite);



		//Draw main things
		//window.draw(_kpMap.getRoad());
		for (int i = 0; i < _kpCarSystem.getNCar(); i++) {
			window.draw(_kpCarSystem.doGetShapeToDraw(i));
		}
		for (int i = 0; i < 4; i++) {
			window.draw(_kpLightsSystem.getSprite(i));
		}
		for (int i = 0; i < _kpEnvObjects.getNTreeShapes(); i++) {
			window.draw(_kpEnvObjects.doGetTreeShapeToDraw(i));
		}
		//Draw debug cars
		for (int i = 0; i < _kpCarSystem.debug_getNDebugCar(); i++) {
			window.draw(_kpCarSystem.debug_doGetShapeToDraw(i));
		}


		window.draw(_kpEnvObjects.doGetLightningSpriteToDraw(0));

		
		

		//Draw optional things
		if (_kpConfig.debugInfoEnabled) {
			for (int i = 0; i < _kpCarSystem.getNCar(); i++) {
				
				window.draw(_kpCarSystem.doGetBackCollisionShapeToDraw(i));
				window.draw(_kpCarSystem.doGetHeadCollisionShapeToDraw(i));
				window.draw(_kpCarSystem.doGetCarInformation(i));
			}
			window.draw(_kpHud.getMouseHud());
		}
		if (_kpConfig.hudEnabled) {
			window.draw(_kpHud.getHud());
		}
		if (_kpConfig.fpsLimitEnabled) {
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
		carsonscreen = 0;
	}
	

}