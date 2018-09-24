#include "pch.h"
#include "kpLightsObject.h"
#include <iostream>

void kpLightsObject::initLight(std::string location, sf::Texture text_default, sf::Texture text_red, sf::Texture text_yellow, sf::Texture text_green) {
	int i;
	_kpDebug.setLocation("kpLightsObject");


	_kpDebug.sendMessage("Mapping textures");
	sf::Texture _lightTextures[4] = { text_default, text_red, text_yellow, text_green };
	for (i = 0; i < 4; i++) {
		lightTextures[i] = _lightTextures[i];
	}



	std::string *string = std::find(std::begin(lightNames), std::end(lightNames), location);
	if (string != std::end(lightNames)) {
		_kpDebug.sendMessage("lightName found at position " + std::distance(lightNames, string));
		lightId = std::distance(lightNames, string);
	}
	else {
		_kpDebug.sendMessage("lightName not found!");
		lightId = -1;
	}

	if (lightId != -1) {
		_kpDebug.setLocation("kpLightsObject_" + std::to_string(lightId));

		lightSprite.setTexture(lightTextures[0]);
		lightSprite.setPosition(lightLocations[lightId]);
		lightSprite.setScale(0.5, 0.5);
	}

}
sf::FloatRect kpLightsObject::getPosition() {
	return lightSprite.getGlobalBounds();
}

sf::Sprite kpLightsObject::getSprite() {
	return lightSprite;
}
void kpLightsObject::switchLight(int toState) {
	lightSprite.setTexture(lightTextures[toState]);
}
void kpLightsObject::switchLight() {
	lightSprite.setTexture(lightTextures[1]);
	lightSprite.setTexture(lightTextures[2]);
	lightSprite.setTexture(lightTextures[3]);
	lightSprite.setTexture(lightTextures[0]);

}

void kpLightsObject::update() {

}