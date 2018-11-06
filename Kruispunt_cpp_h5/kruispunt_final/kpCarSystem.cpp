#include "pch.h"
#include "kpCarSystem.h"

kpCarSystem::kpCarSystem(int _wW, int _wH) {
	_kpDebug.setLocation("kpCarSystem");
	
	if (!infoFont.loadFromFile(_kpConfig.fontFile)) {
		_kpDebug.sendMessage("Error while reading font file (" + _kpConfig.fontFile + ")", _kpConfig.ERROR);
	}

	_kpDebug.sendMessage("[..] Loading textures", _kpConfig.VERBOSE);

	_kpTextures.loadTextures();
	for (int i = 0; i < _kpTextures.t_car_files_len; i++) {
		carTextures[0][i] = _kpTextures.getCarTexture(0,i); //@change
		carTextures[1][i] = _kpTextures.getCarTexture(1,i);

	}
	_kpDebug.sendMessage("[ok] Loading textures", _kpConfig.INFO);



	_kpDebug.sendMessage("[..] Setting default values", _kpConfig.VERBOSE);
	for (int i = 0; i < n_car; i++) {
		carInited[i] = false;
	}
	for (int i = 0; i < 4; i++) {
		carGlobal_NCarsWaiting[i] = 0;
	}
	windowWidth = _wW;
	windowHeight = _wH;
	_kpDebug.sendMessage("[ok] Setting default values", _kpConfig.INFO);


}

void kpCarSystem::doInitCar(int n, int _carModel,  int _carStart, int _carEnd, int _carColor) {
	_kpDebug.sendMessage("[..] Initing car! id=,carmodel,carstart,carend,carcolor", _kpConfig.INFO);
	carShape[n] = sf::RectangleShape();
	
	//Reset every value to default

	carCurrentSpeed[n] = 0.f;
	carCurrentRotation[n] = 0.f;
	carShape[n].setRotation(carCurrentRotation[n]);
	carMovementVector[n] = sf::Vector2f(0.f, 0.f);
	carForwardVector[n] = sf::Vector2f(0.f, 0.f);
	
	//Events reset
	carEvent_DoesCareAboutLights[n] = true;
	carEvent_IsAllowedByLights[n] = false;
	carEvent_StoppedBeforeIntersection[n] = false;
	carEvent_DoesCareAboutCollision[n] = true;
	carEvent_HadCollision[n] = false;
	customSpeedIsSet[n] = false;
	carCollisionMaker[n] = false;

	carCurrentModel[n] = _carModel;
	carInited[n] = true;
	carStart[n] = _carStart;
	carEnd[n] = _carEnd;

	carPosition[n] = carSpawnLocations[_carModel][carStart[n]];
	carShape[n].setTexture(&carTextures[_carModel][carStart[n]]);
	carShape[n].setFillColor(carColors[_carColor]);
	carShape[n].setPosition(carPosition[n]);
	carShape[n].setSize(carSizes[_carModel][carStart[n]]);

	
	

	//Back shape
	carBackCollisionShape[n].setPosition(carPosition[n]);
	carBackCollisionShape[n].setSize(carBackCollisionSizes[_carModel][_carStart]);
	carBackCollisionShape[n].setFillColor(sf::Color(255, 0, 0, 64));
	carBackCollisionShape[n].setRotation(0.f);
	//Head shape
	carHeadCollisionShape[n].setPosition(carPosition[n]);
	carHeadCollisionShape[n].setSize(carHeadCollisionSizes[_carModel][_carStart]);
	carHeadCollisionShape[n].setFillColor(sf::Color(0, 255, 0, 64));
	carHeadCollisionShape[n].setRotation(0.f);

	

}

void kpCarSystem::_doSmoothRotation(int n, int direction, int rotateType, float dt) {

	if (direction == 0) {
		carShape[n].rotate(rotateAmount[rotateType] * dt);
		carBackCollisionShape[n].rotate(rotateAmount[rotateType] * dt);
		carHeadCollisionShape[n].rotate(rotateAmount[rotateType] * dt);

	}
	if (direction == 1) {
		carShape[n].rotate(-rotateAmount[rotateType] * dt);
		carBackCollisionShape[n].rotate(-rotateAmount[rotateType] * dt);
		carHeadCollisionShape[n].rotate(-rotateAmount[rotateType] * dt);


	}
}
void kpCarSystem::_hacks_setEndRotation(int n, float endRotation) {
	carShape[n].setRotation(endRotation);
	carBackCollisionShape[n].setRotation(endRotation);
	carHeadCollisionShape[n].setRotation(endRotation);
}

void kpCarSystem::_doGoForward(int n, float dt) {
	if (carCurrentSpeed[n] < maxSpeed) {
		carCurrentSpeed[n] += acceleration * dt;
	}

	sf::Transform t;
	t.rotate(carShape[n].getRotation());
	carForwardVector[n] = forwardVectors[carStart[n]];
	carMovementVector[n] = t.transformPoint(carForwardVector[n]);
}
void kpCarSystem::_doHardBrake(int n, float dt) {
	carCurrentSpeed[n] -= hardDeceleration * dt;
	if (carCurrentSpeed[n] < 0.f) {
		carCurrentSpeed[n] = 0.f;
	}

}
void kpCarSystem::_doBrake(int n, float dt) {
	carCurrentSpeed[n] -= deceleration * dt;
	if (carCurrentSpeed[n] < 0.f) {
		carCurrentSpeed[n] = 0.f;
	}
}
void kpCarSystem::_doMoveCar(int n, float dt) {
	if (carCollisionMaker[n] == false) {
		carShape[n].move(carMovementVector[n] * carCurrentSpeed[n] * dt);
	}
	carPosition[n] = carShape[n].getPosition();

}

void kpCarSystem::_modifyCurrentSpeedIfNeeded(int n, float _desiredSpeed) {
	if (customSpeedIsSet[n] == false) {
		carCurrentSpeed[n] = _desiredSpeed;
		customSpeedIsSet[n] = true;
	}
}
void kpCarSystem::_doPerformLogic(int n, float dt) {
	carPosition[n] = carShape[n].getPosition();
	carCurrentRotation[n] = carShape[n].getRotation();

	if (carEvent_DoesCareAboutCollision[n] == true && carGlobal_EnableCollision == true) {
		for (int i = 0; i < n_car; i++) {
			if (!(i == n)) {
				if (carHeadCollisionShape[n].getGlobalBounds().intersects(carBackCollisionShape[i].getGlobalBounds())) {
					thisCarRanInto[n] = i;
					carCollisionMaker[n] = true;
					carEvent_HadCollision[n] = true;
				}
			}
		}

		if (carCollisionMaker[n] == true) {
			if (!carHeadCollisionShape[n].getGlobalBounds().intersects(carBackCollisionShape[thisCarRanInto[n]].getGlobalBounds())) {
				carCollisionMaker[n] = false;
			}
			else {
				_doHardBrake(n, dt);
				return;
			}
		}
	}


	//FASE0
	float pos_stopAccelerate = actionCoordinates_fase0[carStart[n]][carCurrentModel[n]][0];
	float pos_startBrake = actionCoordinates_fase0[carStart[n]][carCurrentModel[n]][0];
	float pos_startHardBrake = actionCoordinates_fase0[carStart[n]][carCurrentModel[n]][1];

	if (carStart[n] == 3) {
		//Fase0
		
		if (carPosition[n].x < pos_stopAccelerate) { //posx
			_doGoForward(n, dt);
		}
		if (carEvent_HadCollision[n] && carPosition[n].x > pos_startHardBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doHardBrake(n, dt);
		}
		if (!carEvent_HadCollision[n] && carPosition[n].x > pos_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doBrake(n, dt);
		}
		if (carCurrentSpeed[n] == 0.f) {
			carEvent_StoppedBeforeIntersection[n] = true;
		}

		//Fase1
		if (carEvent_StoppedBeforeIntersection[n]) {
			if (carEvent_DoesCareAboutLights[n]) {
				carEvent_IsAllowedByLights[n] = (lightsState[carStart[n]] == 3);
				if (carEvent_IsAllowedByLights[n]) {
					carEvent_DoesCareAboutLights[n] = false;
					carEvent_DoesCareAboutCollision[n] = carGlobal_EnableCollisionAfterLights;
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {

				//Fase2.0
				if (carEnd[n] == 0) {
					if (carPosition[n].x < 510.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x > 510.f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 74.f);
							_doSmoothRotation(n, 1, 1, dt);
						}
						else {
							_hacks_setEndRotation(n, 270.f);
						}
						_doGoForward(n, dt);
					}
				}

				//Fase2.1
				if (carEnd[n] == 1) {
					_doGoForward(n, dt);
				}

				//Fase2.2
				if (carEnd[n] == 2) {
					if (carPosition[n].x < 515.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x > 515.f) {


						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {

							_modifyCurrentSpeedIfNeeded(n, 97.f);
							_doSmoothRotation(n, 0, 0, dt);
						}
						else {
							_hacks_setEndRotation(n, 90.f);
						}
						_doGoForward(n, dt);
					}
				}
			}
		}

	}
	if (carStart[n] == 2) {
		//Fase0
		
		if (carPosition[n].y > pos_stopAccelerate) { //posy
			_doGoForward(n, dt);
		}
		if (carEvent_HadCollision[n] && carPosition[n].y < pos_startHardBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doHardBrake(n, dt);
		}
		if (!carEvent_HadCollision[n] && carPosition[n].y < pos_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doBrake(n, dt);
		}

		if (carCurrentSpeed[n] == 0.f) {
			carEvent_StoppedBeforeIntersection[n] = true;
		}

		//Fase1
		if (carEvent_StoppedBeforeIntersection[n]) {
			if (carEvent_DoesCareAboutLights[n]) {
				carEvent_IsAllowedByLights[n] = (lightsState[carStart[n]] == 3);
				if (carEvent_IsAllowedByLights[n]) {
					carEvent_DoesCareAboutLights[n] = false;
					carEvent_DoesCareAboutCollision[n] = carGlobal_EnableCollisionAfterLights;
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {

				//Fase2.0
				if (carEnd[n] == 0) {
					_doGoForward(n, dt);
				}

				//Fase2.1
				if (carEnd[n] == 1) {
					if (carPosition[n].y > 390.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].y < 390.f) {
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 96.6f);
							_doSmoothRotation(n, 0, 0, dt);
						}
						else {
							_hacks_setEndRotation(n, 90.f);
						}
						_doGoForward(n, dt);
					}
				}

				//Fase2.3
				if (carEnd[n] == 3) {
					if (carPosition[n].y > 380.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].y < 380.f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 77.f);
							_doSmoothRotation(n, 1, 1, dt);
						}
						else {
							_hacks_setEndRotation(n, 270.f);
						}
						_doGoForward(n, dt);
					}
				}

			}
		}
	}
	if (carStart[n] == 1) {
		//Fase0
		
		if (carPosition[n].x > pos_stopAccelerate) { //posx
			_doGoForward(n, dt);
		}
		if (carEvent_HadCollision[n] && carPosition[n].x < pos_startHardBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doHardBrake(n, dt);
		}
		if (!carEvent_HadCollision[n] && carPosition[n].x < pos_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doBrake(n, dt);
		}

		if (carCurrentSpeed[n] == 0.f) {
			carEvent_StoppedBeforeIntersection[n] = true;
		}

		//Fase1
		if (carEvent_StoppedBeforeIntersection[n]) {
			if (carEvent_DoesCareAboutLights[n]) {
				carEvent_IsAllowedByLights[n] = (lightsState[carStart[n]] == 3);
				if (carEvent_IsAllowedByLights[n]) {
					carEvent_DoesCareAboutLights[n] = false;
					carEvent_DoesCareAboutCollision[n] = carGlobal_EnableCollisionAfterLights;
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {

				//Fase2.0
				if (carEnd[n] == 0) {
					if (carPosition[n].x > 720.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x < 720.f) {
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 62.f);
							_doSmoothRotation(n, 0, 0, dt);
						}
						else {
							_hacks_setEndRotation(n, 90.f);
						}
						_doGoForward(n, dt);
					}
				}

				//Fase2.2
				if (carEnd[n] == 2) {
					if (carPosition[n].x > 659.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x < 659.f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 94.f);
							_doSmoothRotation(n, 1, 1, dt);
						}
						else {
							_hacks_setEndRotation(n, 270.f);
						}
						_doGoForward(n, dt);
					}
				}

				//Fase2.3
				if (carEnd[n] == 3) {
					_doGoForward(n, dt);
				}
			}
		}
	}
	if (carStart[n] == 0) {
		//Fase0
		if (carPosition[n].y < pos_stopAccelerate) { //posy
			_doGoForward(n, dt);
		}
		if (carEvent_HadCollision[n] && carPosition[n].y > pos_startHardBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doHardBrake(n, dt);
		}
		if (!carEvent_HadCollision[n] && carPosition[n].y > pos_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
			_doBrake(n, dt);
		}
		if (carCurrentSpeed[n] == 0.f) {
			carEvent_StoppedBeforeIntersection[n] = true;
		}


		//Fase1
		if (carEvent_StoppedBeforeIntersection[n]) {
			if (carEvent_DoesCareAboutLights[n]) {
				carEvent_IsAllowedByLights[n] = (lightsState[carStart[n]] == 3);
				if (carEvent_IsAllowedByLights[n]) {

					carEvent_DoesCareAboutLights[n] = false;
					carEvent_DoesCareAboutCollision[n] = carGlobal_EnableCollisionAfterLights;
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {

				//Fase2.1
				if (carEnd[n] == 1) {

					//Pas aan de volgende weg
					if (carPosition[n].y < 247.5f) { //247.5
						_doGoForward(n, dt);
					}

					//Begin te draaien en ga naar de doelweg
					if (carPosition[n].y > 247.5f) {
						if (carCurrentRotation[n] > 270.0f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 97.f);
							_doSmoothRotation(n, 1, 1, dt); //Softbocht
						}
						else {
							_hacks_setEndRotation(n, 270.f);
						}
						_doGoForward(n, dt);


					}
				}
				//Fase2.2
				if (carEnd[n] == 2) {
					_doGoForward(n, dt);
				}
				//Fase2.3
				if (carEnd[n] == 3) {
					//Pas aan de volgende weg
					if (carPosition[n].y < 180.f) {
						_doGoForward(n, dt);
					}

					//Begin te draaien en ga neer de doelweg
					if (carPosition[n].y > 180.f) {

						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
							_modifyCurrentSpeedIfNeeded(n, 71.f);

							_doSmoothRotation(n, 0, 0, dt); //Scherpbocht
						}
						else {
							_hacks_setEndRotation(n, 90.f);
						}
						_doGoForward(n, dt);

					}
				}
			}
		}
	}

}


void kpCarSystem::_doUpdateCollisions(int n) {
	carBackCollisionShape[n].setPosition(carShape[n].getPosition());
	carHeadCollisionShape[n].setPosition(carShape[n].getPosition());
}
sf::Vector2f kpCarSystem::_doGetCoords(int n) {
	return carShape[n].getPosition();
}

void kpCarSystem::doPerformLogic(int _lightsState[4], float dt) {

	//Update lightsstate
	int i;
	for (i = 0; i < 4; i++) {
		lightsState[i] = _lightsState[i];
	}
	//Update collisions
	for (i = 0; i < n_car; i++) {
		_doUpdateCollisions(i);
	}
	//Perform main logic
	for (i = 0; i < n_car; i++) {
		if (carInited[i]) {
			_doPerformLogic(i, dt);
		}
	}

	//Perform finalizing logic
	for (i = 0; i < n_car; i++) {
		if (carInited[i]) {
			_doMoveCar(i, dt);
		}
	}

	//Update car lights
	for (int i = 0; i < n_car; i++) {

	}


}
void kpCarSystem::_doUpdateCarLights(int n) {
	//carLightsDirectionLeft[n].setPosition()
}
sf::RectangleShape kpCarSystem::doGetBackCollisionShapeToDraw(int n) {
	return carBackCollisionShape[n];
}
sf::RectangleShape kpCarSystem::doGetHeadCollisionShapeToDraw(int n) {
	return carHeadCollisionShape[n];
}

sf::RectangleShape kpCarSystem::doGetShapeToDraw(int n) {
	return carShape[n];
}
sf::Text kpCarSystem::doGetCarInformation(int n) {
	sf::Text text;
	if (carInited[n]) {
		text.setFont(infoFont);
		text.setString(
			"(" + std::to_string(carPosition[n].x) + "," + std::to_string(carPosition[n].y) + "\n" +
			std::to_string(carCurrentRotation[n]) + "," + std::to_string(carCurrentSpeed[n]) + "\n" +
			std::to_string(carCollisionMaker[n]) + "|" + std::to_string(n)
		);
		text.setCharacterSize(12);
		text.setFillColor(sf::Color::Red);
		text.setPosition(carPosition[n]);
	}
	return text;
}

void kpCarSystem::doRegenerateCars() {
	int i;
	for (i = 0; i < n_car; i++) {
		if (carShape[i].getPosition().x > windowWidth + 120.f
			|| carShape[i].getPosition().x < -120.f
			|| carShape[i].getPosition().y < -120.f
			|| carShape[i].getPosition().y > windowHeight + 120.f) {

			carGlobal_NCarsWaiting[carStart[i]] -= carWeight[carCurrentModel[i]];
			doGenerateCar(i);
		}
	}
}
void kpCarSystem::doGenerateCar(int n) {
	bool generatedDifferent = false;
	int _carStart, _carEnd, _carColor, _carModel;
	int actualTries = 0;
	int maxTries = 10;
	while (!generatedDifferent && actualTries < maxTries) {
		_carStart = rand() % (3 - 0 + 1) + 0;
		_carEnd = rand() % (3 - 0 + 1) + 0;
		_carColor = rand() % (7 - 0 + 1) + 0;
		_carModel = rand() % (1 - 0 + 1) + 0;
		if (_carStart != _carEnd) {
			if (carGlobal_NCarsWaiting[_carStart] < maxCarPerLane[_carStart]) {
				generatedDifferent = true;
			}
		}
		actualTries += 1;
	}

	if (generatedDifferent) {
		carGlobal_NCarsWaiting[_carStart] += carWeight[_carModel];
		doInitCar(n, _carModel, _carStart, _carEnd, _carColor);
		_kpDebug.sendMessage("Spawned at " + std::to_string(_carStart), 3);
	}
	else {
		_kpDebug.sendMessage("Spawn at " + std::to_string(_carStart) + " is not possible!", 3);

	}
}

int kpCarSystem::getNCar() {
	return n_car;
}
bool kpCarSystem::isCarInited(int n) {
	return carInited[n];
}

int kpCarSystem::debug_getNDebugCar() {
	return debug_n_car;
}
sf::RectangleShape kpCarSystem::debug_doGetShapeToDraw(int n) {
	return debug_CarShape[n];
}
void kpCarSystem::debug_doInitCar(int n, sf::Vector2f _position, int _carModel, int _carColor, int _carStart) {	
	debug_CarShape[n].setPosition(_position);
	debug_CarShape[n].setSize(carSizes[_carModel][_carStart]);
	debug_CarShape[n].setTexture(&carTextures[_carModel][_carStart]);
	debug_CarShape[n].setFillColor(carColors[_carColor]);
}
void kpCarSystem::debug_setRotation(int n, float endRotation) {
	debug_CarShape[n].setRotation(endRotation);
}