#include "pch.h"
#include "kpTextures.h"


kpTextures::kpTextures() {
	_kpDebug.setLocation("kpTextures");
}


void kpTextures::loadTextures() {
	int i;


	_kpDebug.sendMessage("Loading lights textures...");
	for (i = 0; i < 4; i++) {
		_kpDebug.sendMessage(std::to_string(i) + " from " + t_lights_files[i]);
	
		if (!t_lights[i].loadFromFile(t_lights_files[i])) {
			_kpDebug.sendMessage(std::to_string(i) + " FAILED!");
		}
	}

	_kpDebug.sendMessage("Loading background texture(s)...");
	for (i = 0; i < 1; i++) {
		_kpDebug.sendMessage(std::to_string(i) + " from " + t_background_files[i]);

		if (!t_background[i].loadFromFile(t_background_files[i])) {
			_kpDebug.sendMessage(std::to_string(i) + " FAILED!");
		}
	}

	_kpDebug.sendMessage("Loading car texture(s)...");
	for (i = 0; i < 4; i++) {
		_kpDebug.sendMessage(std::to_string(i) + " from " + t_car_files[i]);
		if (!t_car[i].loadFromFile(t_car_files[i])) {
			_kpDebug.sendMessage(std::to_string(i) + " FAILED!");
		}
		t_car[i].setSmooth(true);
	}
}
sf::Texture kpTextures::getBackgroundTexture(int id) {
	return t_background[id];
}
sf::Texture kpTextures::getLightsTexture(int id) {
	return t_lights[id];
}
sf::Texture kpTextures::getCarTexture(int id) {
	return t_car[id];
}