#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpCarSystem {
private:
	int windowWidth, windowHeight;
	sf::Texture carTextures[4];

	sf::Color carColors[8] = {
		sf::Color(255,255,255,255),
		sf::Color(0,0,0,256),
		sf::Color(192,192,192,255),
		sf::Color(128,128,128,255),
		sf::Color(255,165,0,255),
		sf::Color(220,20,60,255),
		sf::Color(65,105,225,255),
		sf::Color(60,179,113,255)
	};
	sf::Vector2f carSpawnLocations[4] = {
		sf::Vector2f(540.f,0.f),
		sf::Vector2f(1200.f, 255.f),
		sf::Vector2f(605.f, 1200.f / 2.f),
		sf::Vector2f(0.f, 320.f)
	};
	size_t carSpawnLocations_len = sizeof(carSpawnLocations) / sizeof(carSpawnLocations[0]);

	sf::Vector2f carSizes[4] = {
		sf::Vector2f(55.f, 55.f),
		sf::Vector2f(55.f, 55.f),
		sf::Vector2f(55.f, 55.f),
		sf::Vector2f(55.f, 55.f)
	};
	size_t carSizes_len = sizeof(carSizes) / sizeof(carSizes[0]);

	std::string carSpawnNames[4] = { "up", "right","down","left" };
	size_t carSpawnNames_len = sizeof(carSpawnNames) / sizeof(carSpawnNames[0]);


	const float maxSpeed = 800.f;
	const float acceleration = 60.f;
	const float deceleration = 300.f;
	const float rotateAmount[2] = { 110.f, 60.f };
	const sf::Vector2f forwardVectors[4] = {
		sf::Vector2f(0.f,1.f),
		sf::Vector2f(-1.f,0.f),
		sf::Vector2f(0.f,-1.f),
		sf::Vector2f(1.f,0.f)
	};

	int lightsState[4];
	bool wachtRijBezet[4][3];
	float wacht_0[3] = { 140.f, 80.f, 20.f };

	//Car defined vars (16)
	static const int n_car = 1024*2;
	int placeToStopInWachtrij[n_car];
	sf::Vector2f carPosition[n_car];
	sf::RectangleShape carShape[n_car];
	sf::Vector2f carForwardVector[n_car];
	sf::Vector2f carMovementVector[n_car];

	bool carInited[n_car];
	///Events
	bool carEvent_StoppedBeforeIntersection[n_car];
	bool carEvent_IsAllowedByLights[n_car];
	bool carEvent_DoesCareAboutLights[n_car];
	bool carEvent_CheckedWhereToStop[n_car];
	///End
	int carStart[n_car], carEnd[n_car];
	float carCurrentSpeed[n_car];
	float carCurrentRotation[n_car];


	sf::Font infoFont;
	kpDebug _kpDebug;

	void _doSmoothRotation(int n, int direction, int rotateType, float dt);
	void _hacks_setEndRotation(int n, float endRotation);
	void _doGoForward(int n, float dt);
	void _doBrake(int n, float dt);
	void _doMoveCar(int n, float dt);
	void _doPerformLogic(int n, float dt);
	sf::Vector2f _doGetCoords(int n);
	void _doGenerateCar(int n);
public:
	kpCarSystem(int _wW, int _wH, std::string _fontFile, sf::Texture t_car_0, sf::Texture t_car_1, sf::Texture t_car_2, sf::Texture t_car_3);
	void doInitCar(int n, int _carStart, int _carEnd, int _carColor);
	void doPerformLogic(int _lightsState[4], float dt);
	sf::RectangleShape doGetShapeToDraw(int n);
	sf::Text doGetCarInformation(int n);
	void doRegenerateCars();
	int getNCar();


};