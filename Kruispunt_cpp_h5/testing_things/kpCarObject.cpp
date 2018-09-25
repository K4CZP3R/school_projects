#include "pch.h"
#include "kpCarObject.h"

kpCarObject::kpCarObject() {
	
	_kpDebug.setLocation("kpCarObject");

}
void kpCarObject::initCar(int _windowWidth, int _windowHeight, int startDirection, int endDirection, std::string _fontFile) {
	//int i;
	//Todo: map textures

	captureN = 0;
	captureI = 0;

	if (!infoFont.loadFromFile(_fontFile)) {
		_kpDebug.sendMessage("Error while reading font file (" + _fontFile + ")");
	}


	windowWidth = _windowWidth;
	windowHeight = _windowHeight;

	if(startDirection < 0 || startDirection > carNamesLen){
		throw "startDirection too big/small";
	}
	if (endDirection < 0 || endDirection > carNamesLen) {
		throw "endDirection too big/small";
	}
	carStartDirection = startDirection;
	carEndDirection = endDirection;

	position = carLocations[startDirection];
	carShape.setPosition(position);
	carShape.setSize(carSize[startDirection]);

	//Beta, reint
	currentSpeed = 0.f;
	rotation = 0.f;
	carShape.setRotation(0.f);
	movementVector = sf::Vector2f(0.f, 0.f);
	forwardVec = sf::Vector2f(0.f, 0.f);
	carEvent_StoppedBeforeIntersection = false;
	carEvent_IsAllowedByLights = false;
	carEvent_DoesCareAboutLights = true;


}
sf::Vector2f kpCarObject::getCoords() {
	return carShape.getPosition();
}
sf::FloatRect kpCarObject::getPosition() {
	return carShape.getGlobalBounds();
}

sf::RectangleShape kpCarObject::getShape() {
	return carShape;
}

void kpCarObject::moveCar() {
	if (carStartDirection == 0) {
		if (carEndDirection == 1) {
			//Rotation 
			if (position.y > 200.0 && position.y < 375.0) {
				carShape.setRotation(carRotation);
				carRotation -= 90.f/175.f;
			}

			//Go down before to the right
			if (position.y < 375.0) {
				position.y += 1.0f;
			}

			//Go to the right when rotating
			if (position.y > 250.0) {
				position.x += 0.75f;
			}

			//Go to the right
			if (position.y >= 375.0) {
				carShape.setRotation(270.f);
				carRotation = 0.f;
				_kpDebug.sendMessage(std::to_string(carShape.getRotation()));
				position.x += 1.0f;
			}
		}
		if (carEndDirection == 2) {

			position.y += 1.0f;
		}
		if (carEndDirection == 3) {

			//Rotation
			if (position.y > 200.0 && position.y < 325.0) {
				carShape.setRotation(carRotation);
				carRotation += 90.f / 125.f;
			}

			//Go down before to the left
			if (position.y < 325.0) {
				position.y += 1.0f;
			}

			//Go to the right when rotating
			if (position.y > 250.0) {
				position.x -= 0.75f;
			}
			//Go to the left
			if (position.y >= 325.0) {
				carShape.setRotation(90.f);
				carRotation = 0.f;
				position.x -= 1.0f;
			}

		}
	}
}
void kpCarObject::second_PerformLogic(int carWaiting[4][3], int lightsState[4], float dt) {
	//_kpDebug.sendMessage(std::to_string(carShape.getRotation()));
	
	position = carShape.getPosition();
	rotation = carShape.getRotation();

	
	if (carStartDirection == 2) {
		float posy_stopAccelerate = 0.f;
		float posy_startBrake = 0.f;
		if (position.y > 440.f) {
			second_goForward(dt);
		}
		if (position.y < 440.f && currentSpeed != 0.f && !carEvent_StoppedBeforeIntersection) {
			second_brake(dt);
		}
		if (currentSpeed == 0.f) {
			carEvent_StoppedBeforeIntersection = true;
		}
		//End

		if (carEvent_StoppedBeforeIntersection) {
			if(carEvent_DoesCareAboutLights){ 
				carEvent_IsAllowedByLights = (lightsState[carStartDirection] == 3);
				if (carEvent_IsAllowedByLights) {
					carEvent_DoesCareAboutLights = false;
				}
			}

			if (carEvent_IsAllowedByLights) {
				if (carEndDirection == 0) {
					second_goForward(dt);
				}
				if (carEndDirection == 1) {
					if (position.y > 365.f) {
						second_goForward(dt);
					}
					if (position.y < 365.f) {
						if (rotation < 90.f || rotation == 0.f) {
							second_setSmoothRotation(1, 0, dt);
						}
						second_goForward(dt);
					}
				}
				if(carEndDirection == 3){
					if (position.y > 370.f) {
						second_goForward(dt);
					}
					if (position.y < 370.f) {
						if (rotation > 270.f || rotation == 0.f) {
							second_setSmoothRotation(0, 1, dt); //Soft bocht
						}
						second_goForward(dt);
					}
				}
			}
		}
	}
	if (carStartDirection == 0) {
		float posy_stopAccelerate, posy_startBrake;
		if (carWaiting[carStartDirection][0] == 0) {
			//Go to the rand and stop
			posy_stopAccelerate = 120.f;
			posy_startBrake = 120.f;
			carWaiting[carStartDirection][0] = 1;
			carStoppedAt = 0;
		}
		else if (carWaiting[carStartDirection][1] == 0) {
			posy_stopAccelerate = 100.f;
			posy_startBrake = 100.f;
			carWaiting[carStartDirection][1] = 1;
			carStoppedAt = 1;
		}
		else if (carWaiting[carStartDirection][2] == 0) {
			posy_stopAccelerate = 80.f;
			posy_startBrake = 80.f;
			carWaiting[carStartDirection][2] = 1;
			carStoppedAt = 2;
		}
		
		if (position.y < posy_stopAccelerate) {
			second_goForward(dt);
		}
		if (position.y > posy_startBrake && currentSpeed != 0.f && !carEvent_StoppedBeforeIntersection) {
			second_brake(dt);
		}
		if (currentSpeed == 0.f) {
			carEvent_StoppedBeforeIntersection = true;
		}
		//End

		if (carEvent_StoppedBeforeIntersection) {
			if (carEvent_DoesCareAboutLights) {
				carEvent_IsAllowedByLights = (lightsState[carStartDirection] == 3);
				if (carEvent_IsAllowedByLights) {
					carEvent_DoesCareAboutLights = false;
				}
			}
			if (carEvent_IsAllowedByLights) {
				carWaiting[carStartDirection][carStoppedAt] = 0;
				if (carEndDirection == 1) {
					//Pas aan de volgende weg
					if (position.y < 245.f) {
						second_goForward(dt);
					}
					//Begin te draaien en ga naar de doelweg
					if (position.y > 245.f) {
						if (rotation > 270.f || rotation == 0.f) { //360-90=270
							second_setSmoothRotation(0, 1, dt); //Soft bocht
						}
						second_goForward(dt);
					}
				}
				if (carEndDirection == 2) {
					second_goForward(dt);
				}
				if (carEndDirection == 3) {
					//Pas aan de volgende weg
					if (position.y < 180.f) {
						second_goForward(dt);
					}
					//Begin te draaien en ga naar de doelweg
					if (position.y > 180.f) {
						if (rotation < 90.f || rotation == 0.f) {
							second_setSmoothRotation(1, 0, dt); //Sharp bocht
						}
						second_goForward(dt);
					}
				}
			}
		}
	}
	if (carStartDirection == 3) {
		float posx_stopAccelerate = 120.f;
		float posx_startBrake = 120.f;
		
		if (position.x < 370.f) {
			second_goForward(dt);
		}
		if (position.x > 370.f && currentSpeed != 0.f && !carEvent_StoppedBeforeIntersection) {
			second_brake(dt);
		}
		if (currentSpeed == 0.f) {
			carEvent_StoppedBeforeIntersection = true;
		}
		if (carEvent_StoppedBeforeIntersection) {
			if (carEvent_DoesCareAboutLights) {
				carEvent_IsAllowedByLights = (lightsState[carStartDirection] == 3);
				if (carEvent_IsAllowedByLights) {
					carEvent_DoesCareAboutLights = false;
				}
			}

			if (carEvent_IsAllowedByLights) {
				if (carEndDirection == 0) {
					if (position.x < 510.f) {
						second_goForward(dt);
					}
					if (position.x > 510.f) {
						if (rotation > 270.f || rotation == 0.f) {
							second_setSmoothRotation(0, 1, dt);
						}
						second_goForward(dt);
					}
				}
				if (carEndDirection == 1) {
					second_goForward(dt);
				}
				if (carEndDirection == 2) {
					if (position.x < 520.f) {
						second_goForward(dt);
					}
					if (position.x > 520.f) {
						if (rotation < 90.f || rotation == 0.f) {
							second_setSmoothRotation(1, 0, dt);
						}
						second_goForward(dt);
					}
				}
			}
		}


	}
	if (carStartDirection == 1) {
		float posx_stopAccelerate = 120.f;
		float posx_startBrake = 120.f;

		if (position.x > 795.f) {
			second_goForward(dt);
		}
		if (position.x < 795.f && currentSpeed != 0.f && !carEvent_StoppedBeforeIntersection) {
			second_brake(dt);
		}
		if (currentSpeed == 0.f) {
			carEvent_StoppedBeforeIntersection = true;
		}

		if (carEvent_StoppedBeforeIntersection) {
			if (carEvent_DoesCareAboutLights) {
				carEvent_IsAllowedByLights = (lightsState[carStartDirection] == 3);
				if (carEvent_IsAllowedByLights) {
					carEvent_DoesCareAboutLights = false;
				}
			}

			if (carEvent_IsAllowedByLights) {
				if (carEndDirection == 0) {
					if (position.x > 700.f) {
						second_goForward(dt);
					}
					if (position.x < 700.f) {
						if (rotation < 90.f || rotation == 0.f) {
							second_setSmoothRotation(1, 0, dt);
						}
						second_goForward(dt);
					}
				}
				if (carEndDirection == 2) {
					if (position.x > 640.f) {
						second_goForward(dt);
					}
					if (position.x < 640.f) {
						if (rotation > 270.f || rotation == 0.f) {
							second_setSmoothRotation(0, 1, dt);
						}
						second_goForward(dt);
					}
				}
				if (carEndDirection == 3) {
					second_goForward(dt);
				}
			}
		}
	}



}
void kpCarObject::second_setSmoothRotation(int direction, int rotateType,float dt) {
	if (direction == 1) {
		carShape.rotate(rotateAmount[rotateType]*dt);
	}
	if (direction == 0) {
		carShape.rotate(-rotateAmount[rotateType] * dt);
	}
}
void kpCarObject::second_goForward(float dt) {
	if (currentSpeed < maxSpeed) {
		currentSpeed += acceleration * dt;
	}
	
	sf::Transform t;
	t.rotate(carShape.getRotation());
	forwardVec = forwardVecs[carStartDirection];
	movementVector = t.transformPoint(forwardVec);
}
void kpCarObject::second_brake(float dt) {
	currentSpeed -= deceleration * dt;
	if (currentSpeed < 0.f) {
		currentSpeed = 0.f;
	}
}
void kpCarObject::second_moveCar(float dt) {
	carShape.move(movementVector*currentSpeed*dt);
	position = carShape.getPosition();
}


void kpCarObject::update() {

	carShape.setPosition(position);
}

sf::Text kpCarObject::getDrawInformation() {
	sf::Text text;
	text.setFont(infoFont);
	text.setString(std::to_string(position.x) + "\n" + std::to_string(position.y)+ "\n"+std::to_string(currentSpeed));
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(position);
	return text;
}


void kpCarObject::captureMovement() {
	captureN += 1;
	if (captureI > 64) {
		captureI = 0;
		captureN = 0;
	}
	if (!(captureN % 10)) {
		captureD[captureI] = position;
		captureI += 1;
	}
}

sf::RectangleShape kpCarObject::drawMovement(int n) {
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(5, 5));
	shape.setPosition(captureD[n]);
	return shape;
}