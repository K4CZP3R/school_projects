#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpCarObject {
private:
	int windowWidth, windowHeight;

	//RES HARDCODED
	sf::Vector2f carLocations[4] = {sf::Vector2f(525,0), sf::Vector2f(1200, 225), sf::Vector2f(625, 1200/2), sf::Vector2f(0,325 )};
	size_t carLocationsLen = sizeof(carLocations) / sizeof(carLocations[0]);
	
	sf::Vector2f carSize[4] = { sf::Vector2f(50,50), sf::Vector2f(50,50), sf::Vector2f(50,50),sf::Vector2f(50,50) };
	size_t carSizeLen = sizeof(carSize) / sizeof(carSize[0]);
	
	std::string carNames[4] = { "up", "right", "down", "left" };
	size_t carNamesLen = sizeof(carNames) / sizeof(carNames[0]);

	sf::Vector2f position;
	sf::RectangleShape carShape;
	float carSpeed = .3f;
	int carStartDirection;
	int carEndDirection;
	float carRotation = 0.f;

	sf::Font infoFont;
	kpDebug _kpDebug;

	int captureN;
	int captureI;
	sf::Vector2f captureD[64];


	//Beta
	float currentSpeed = 0.f;
	const float maxSpeed = 800.f;
	const float acceleration = 60.f;
	const float deceleration = 300.f;
	const float rotateAmount[2] = { 110.f, 60.f };
	sf::Vector2f movementVector; //Direction vector
	const sf::Vector2f forwardVecs[4] = { sf::Vector2f(0.f,1.f), sf::Vector2f(-1.f,0.f), sf::Vector2f(0.f,-1.f), sf::Vector2f(1.f,0.f) };

	bool carEvent_StoppedBeforeIntersection = false;
	float rotation = 0.f;
	bool carEvent_IsAllowedByLights = false;
	bool carEvent_DoesCareAboutLights = true;

public:
	kpCarObject();
	void initCar(int _windowWidth, int _windowHeight, int startDirection, int endDirection, std::string _fontFile);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	void moveCar();
	void update();
	sf::Text getDrawInformation();
	void captureMovement();
	sf::RectangleShape drawMovement(int n);

	//Beta
	void second_setSmoothRotation(int direction,int rotateType, float dt);
	void second_goForward(float dt);
	void second_brake(float dt);
	void second_moveCar(float dt);
	void second_PerformLogic(int lightsState[4],float dt);
};