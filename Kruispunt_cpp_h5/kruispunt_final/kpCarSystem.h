#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"
#include "kpTextures.h"
#include "kpConfig.h"

class kpCarSystem {
private:
	int windowWidth, windowHeight;

	int carWeight[2] = { 1,2 };
	sf::Texture carTextures[2][4];
	sf::Color carColors[9] = {
		sf::Color(255,20,147,255),
		sf::Color(255,255,255,255),
		sf::Color(64,128,64,255),
		sf::Color(192,192,192,255),
		sf::Color(128,128,128,255),
		sf::Color(255,165,0,255),
		sf::Color(220,20,60,255),
		sf::Color(65,105,225,255),
		sf::Color(60,179,113,255)
	};
	sf::Vector2f carSpawnLocations[2][4] = {
		{
			sf::Vector2f(530.f,-100.f),
			sf::Vector2f(1300.f, 230.f),
			sf::Vector2f(610.f,700.f),
			sf::Vector2f(-100.f, 320.f)
		},
		{
			sf::Vector2f(530.f,-100.f),
			sf::Vector2f(1300.f, 230.f),
			sf::Vector2f(610.f,700.f),
			sf::Vector2f(-100.f, 320.f)
		},

	};
	size_t carSpawnLocations_len = sizeof(carSpawnLocations[0]) / sizeof(carSpawnLocations[0][0]);

	sf::Vector2f carSizes[2][4] = {

		{
			sf::Vector2f(55.f, 55.f),
			sf::Vector2f(-55.f, 55.f),
			sf::Vector2f(55.f, -55.f),
			sf::Vector2f(55.f, 55.f)
		},
		{
			sf::Vector2f(55.f, 90.f),
			sf::Vector2f(-90.f, 55.f),
			sf::Vector2f(55.f, -90.f),
			sf::Vector2f(90.f, 55.f)
		}
	};
	size_t carSizes_len = sizeof(carSizes[0]) / sizeof(carSizes[0][0]);

	sf::Vector2f carHeadCollisionSizes[2][4] = {
		{
			sf::Vector2f(55.f / 1.15f, 65.f / 1.15f),
			sf::Vector2f(-65.f / 1.15f, 55.f / 1.15f),
			sf::Vector2f(55.f / 1.15f, -65.f / 1.15f),
			sf::Vector2f(65.f / 1.15f, 55.f / 1.15f)
		},
		{
			sf::Vector2f(55.f, 90.f),
			sf::Vector2f(-90.f, 55.f),
			sf::Vector2f(55.f, -90.f),
			sf::Vector2f(90.f, 55.f)
		}
			
	};
	size_t carHeadCollisionSizes_len = sizeof(carHeadCollisionSizes[0]) / sizeof(carHeadCollisionSizes[0][0]);

	sf::Vector2f carBackCollisionSizes[2][4] = {
		{
			sf::Vector2f(55.f / 2, -15.f),
			sf::Vector2f(15.f, 55.f / 2),
			sf::Vector2f(55.f / 2, 15.f),
			sf::Vector2f(-15.f / 2, 55.f / 2)
		},
		{
			sf::Vector2f(55.f / 2, -15.f),
			sf::Vector2f(15.f, 55.f / 2),
			sf::Vector2f(55.f / 2, 15.f),
			sf::Vector2f(-15.f, 55.f / 2)
		}
		
	};
	size_t carBackCollisionSizes_len = sizeof(carBackCollisionSizes[0]) / sizeof(carBackCollisionSizes[0][0]);

	std::string carSpawnNames[4] = { "up", "right","down","left" };
	size_t carSpawnNames_len = sizeof(carSpawnNames) / sizeof(carSpawnNames[0]);

	const float maxSpeed = 600.f;
	const float acceleration = 60.f;
	const float deceleration = 300.f;
	const float hardDeceleration = deceleration * 3;
	const float rotateAmount[2] = { 110.f, 60.f };
	const sf::Vector2f forwardVectors[4] = {
		sf::Vector2f(0.f,1.f),
		sf::Vector2f(-1.f,0.f),
		sf::Vector2f(0.f,-1.f),
		sf::Vector2f(1.f,0.f)
	};

	const float actionCoordinates_fase0[4][2][2] = {
		{
			{{100.f},{145.f}},
			{{80.f},{115.f}}
		},
		{
			{{850.f},{755.f}},
			{{870.f},{785.f}}
		},
		{
			{{500.f},{455.f}},
			{{520.f},{485.f}}
		},
		{
			{{370.f},{450.f}},
			{{340.f},{420.f}}
		}
	};



	int lightsState[4];

	int maxCarPerLane[4] = { 3,8,3,8 };
	int actualNplaces[4];

	//Debug cars (to test textures etc.)
	static const int debug_n_car = 8;
	sf::Vector2f debug_CarPosition[debug_n_car];
	sf::RectangleShape debug_CarShape[debug_n_car];

	//Car defined vars (exclusive for every car)
	static const int n_car = 16;
	int carStart[n_car], carEnd[n_car], carCurrentModel[n_car];
	float carCurrentSpeed[n_car];
	float carCurrentRotation[n_car];
	sf::Vector2f carPosition[n_car];
	sf::RectangleShape carShape[n_car];
	sf::Vector2f carForwardVector[n_car];
	sf::Vector2f carMovementVector[n_car];
	sf::RectangleShape carBackCollisionShape[n_car];
	sf::RectangleShape carHeadCollisionShape[n_car];
	int thisCarRanInto[n_car];
	bool carCollisionMaker[n_car];
	bool customSpeedIsSet[n_car];
	bool carInited[n_car];

	///Events (for every car)
	bool carEvent_StoppedBeforeIntersection[n_car];
	bool carEvent_IsAllowedByLights[n_car];
	bool carEvent_DoesCareAboutLights[n_car];
	bool carEvent_DoesCareAboutCollision[n_car];
	bool carEvent_HadCollision[n_car];

	int carGlobal_NCarsWaiting[4];
	bool carGlobal_EnableCollision = true;
	bool carGlobal_EnableCollisionAfterLights = false;

	sf::Font infoFont;
	kpDebug _kpDebug;
	kpTextures _kpTextures;
	kpConfig _kpConfig;

	void _doSmoothRotation(int n, int direction, int rotateType, float dt);
	void _hacks_setEndRotation(int n, float endRotation);
	void _doGoForward(int n, float dt);
	void _doBrake(int n, float dt);
	void _doHardBrake(int n, float dt);
	void _doMoveCar(int n, float dt);
	void _doPerformLogic(int n, float dt);
	void _doUpdateCollisions(int n);
	void _modifyCurrentSpeedIfNeeded(int _n, float _desiredSpeed);
	sf::Vector2f _doGetCoords(int n);
	void _doUpdateCarLights(int n);
public:
	kpCarSystem(int _wW, int _wH);
	void doInitCar(int n,int _carModel , int _carStart, int _carEnd, int _carColor);
	void doPerformLogic(int _lightsState[4], float dt);
	sf::RectangleShape doGetShapeToDraw(int n);
	sf::RectangleShape doGetBackCollisionShapeToDraw(int n);
	sf::RectangleShape doGetHeadCollisionShapeToDraw(int n);

	sf::Text doGetCarInformation(int n);
	void doRegenerateCars();
	void doGenerateCar(int n);

	int getNCar();
	bool isCarInited(int n);
	int debug_getNDebugCar();
	sf::RectangleShape debug_doGetShapeToDraw(int n);
	void debug_doInitCar(int n, sf::Vector2f _position, int _carModel, int _carColor, int _carStart);
	void debug_setRotation(int n, float endRotation);
	

};