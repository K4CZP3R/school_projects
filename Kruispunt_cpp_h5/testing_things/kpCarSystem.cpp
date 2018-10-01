#include "pch.h"
#include "kpCarSystem.h"

kpCarSystem::kpCarSystem(int _wW, int _wH, std::string _fontFile, sf::Texture t_car_0, sf::Texture t_car_1, sf::Texture t_car_2, sf::Texture t_car_3) {
	_kpDebug.setLocation("kpCarSystem");
	if (!infoFont.loadFromFile(_fontFile)) {
		_kpDebug.sendMessage("Error while reading font file (" + _fontFile + ")");
	}
	_kpDebug.sendMessage("Loading t_car_s");
	carTextures[0] = t_car_0;
	carTextures[1] = t_car_1;
	carTextures[2] = t_car_2;
	carTextures[3] = t_car_3;



	int i, o;

	//deinint cars
	for (i = 0; i < n_car; i++) {
		carInited[i] = false;
	}

	for (i = 0; i < 4; i++) {
		for (o = 0; o < 3; o++) {
			wachtRijBezet[i][o] = false;
		}
	}
	windowWidth = _wW;
	windowHeight = _wH;


}

void kpCarSystem::doInitCar(int n, int _carStart, int _carEnd, int _carColor) {
	carCurrentSpeed[n] = 0.f;
	carCurrentRotation[n] = 0.f;
	carShape[n].setRotation(carCurrentRotation[n]);
	carMovementVector[n] = sf::Vector2f(0.f, 0.f);
	carForwardVector[n] = sf::Vector2f(0.f, 0.f);
	carEvent_DoesCareAboutLights[n] = true;
	carEvent_IsAllowedByLights[n] = false;
	carEvent_StoppedBeforeIntersection[n] = false;

	carInited[n] = true;
	carStart[n] = _carStart;
	carEnd[n] = _carEnd;
	carPosition[n] = carSpawnLocations[carStart[n]];
	carShape[n].setPosition(carPosition[n]);
	carShape[n].setSize(carSizes[carStart[n]]);

	carShape[n].setTexture(&carTextures[carStart[n]]);
	carShape[n].setFillColor(carColors[_carColor]);
	
	carEvent_CheckedWhereToStop[n] = false;
	placeToStopInWachtrij[n] = 0;
}

void kpCarSystem::_doSmoothRotation(int n, int direction, int rotateType, float dt) {
	if (direction == 0) {
		carShape[n].rotate(rotateAmount[rotateType] * dt);
	}
	if (direction == 1) {
		carShape[n].rotate(-rotateAmount[rotateType] * dt);
	}
}
void kpCarSystem::_hacks_setEndRotation(int n, float endRotation) {
	carShape[n].setRotation(endRotation);
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

void kpCarSystem::_doBrake(int n, float dt) {
	carCurrentSpeed[n] -= deceleration * dt;
	if (carCurrentSpeed[n] < 0.f) {
		carCurrentSpeed[n] = 0.f;
	}
}

void kpCarSystem::_doMoveCar(int n, float dt) {
	carShape[n].move(carMovementVector[n] * carCurrentSpeed[n] * dt);
	carPosition[n] = carShape[n].getPosition();
}

void kpCarSystem::_doPerformLogic(int n, float dt) {
	carPosition[n] = carShape[n].getPosition();
	carCurrentRotation[n] = carShape[n].getRotation();

	

	if (carStart[n] == 3) {
		//Fase0
		float posx_stopAccelerate, posx_startBrake;
		posx_stopAccelerate = 380.f;
		posx_startBrake = 380.f;

		if (carPosition[n].x < posx_stopAccelerate) {
			_doGoForward(n, dt);
		}
		if (carPosition[n].x > posx_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
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
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {
				//Fase2.0
				if (carEnd[n] == 0) {
					if (carPosition[n].x < 502.5f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x > 502.5f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
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
					if (carPosition[n].x < 535.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x > 535.f) {
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
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
		float posy_stopAccelerate, posy_startBrake;
		posy_stopAccelerate = 430.f;
		posy_startBrake = 430.f;

		if (carPosition[n].y > posy_stopAccelerate) {
			_doGoForward(n, dt);
		}
		if (carPosition[n].y < posy_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
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
					if (carPosition[n].y > 362.5f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].y < 362.5f) {
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
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
					if (carPosition[n].y > 382.5f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].y < 382.5f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
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
		float posx_stopAcccelerate, posx_startBrake;
		posx_stopAcccelerate = 755.f;
		posx_startBrake = 755.f;

		if (carPosition[n].x > posx_stopAcccelerate) {
			_doGoForward(n, dt);
		}
		if (carPosition[n].x < posx_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
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
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {
				//Fase2.0
				if (carEnd[n] == 0) {
					if (carPosition[n].x > 700.f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x < 700.f) {
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
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
					if (carPosition[n].x > 632.5f) {
						_doGoForward(n, dt);
					}
					if (carPosition[n].x < 632.5f) {
						if (carCurrentRotation[n] > 270.f || carCurrentRotation[n] == 0.f) {
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
		float posy_stopAccelerate, posy_startBrake;
		posy_stopAccelerate = 140.f;
		posy_startBrake = 140.f;



			if (carPosition[n].y < posy_stopAccelerate) {
				_doGoForward(n, dt);
			}
			if (carPosition[n].y > posy_startBrake && carCurrentSpeed[n] != 0.f && !carEvent_StoppedBeforeIntersection[n]) {
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
				}
			}

			//Fase2
			if (carEvent_IsAllowedByLights[n]) {
				//Fase2.1
				if (carEnd[n] == 1) {

					//Pas aan de volgende weg
					if (carPosition[n].y < 247.5f) {
						_doGoForward(n, dt);
					}

					//Begin te draaien en ga naar de doelweg
					if (carPosition[n].y > 247.5f) {
						if (carCurrentRotation[n] > 270.0f || carCurrentRotation[n] == 0.f) {
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
					if (carPosition[n].y < 210.f) {
						_doGoForward(n, dt);
					}

					//Begin te draaien en ga neer de doelweg
					if (carPosition[n].y > 210.f) {
						
						if (carCurrentRotation[n] < 90.f || carCurrentRotation[n] == 0.f) {
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

sf::Vector2f kpCarSystem::_doGetCoords(int n) {
	return carShape[n].getPosition();
}

void kpCarSystem::doPerformLogic(int _lightsState[4], float dt) {
	
	//Update lightsstate
	int i;
	for (i = 0; i < 4; i++) {
		lightsState[i] = _lightsState[i];
	}

	//Perform main logic
	for (i = 0; i < n_car; i++) {
		_doPerformLogic(i, dt);
	}

	//Perform finalizing logic
	for (i = 0; i < n_car; i++) {
		_doMoveCar(i, dt);
	}


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
			std::to_string(carCurrentRotation[n])
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
		if (carShape[i].getPosition().x > windowWidth + 80.f
			|| carShape[i].getPosition().x < -80.f
			|| carShape[i].getPosition().y < -80.f
			|| carShape[i].getPosition().y > windowHeight + 80.f) {

			_doGenerateCar(i);
		}
	}
}
void kpCarSystem::_doGenerateCar(int n) {
	bool generatedDifferent = false;
	int _carStart, _carEnd, _carColor;
	while (!generatedDifferent) {
		_carStart = rand() % (3 - 0 + 1) + 0;
		_carEnd = rand() % (3 - 0 + 1) + 0;
		_carColor = rand() % (7 - 0 + 1) + 0;
		if (_carStart != _carEnd) {
			generatedDifferent = true;
		}
	}

	doInitCar(n, _carStart, _carEnd, _carColor);
}

int kpCarSystem::getNCar() {
	return n_car;
}