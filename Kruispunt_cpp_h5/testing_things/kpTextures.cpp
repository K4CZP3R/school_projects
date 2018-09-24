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
}

sf::Texture kpTextures::getTexture(int category, int id) {
	return t_lights[id];
}