#include "pch.h"
#include "kpTextures.h"

kpTextures::kpTextures() {
	_kpDebug.setLocation("kpTextures");
}
void kpTextures::loadLoadingTextures() {
	_kpDebug.sendMessage("[..] Loading loading textures", _kpConfig.VERBOSE);

	for (int i = 0; i < t_loading_files_len; i++) {
		_kpDebug.sendMessage("ID:" + std::to_string(i) + " will be loaded from " + t_loading_files[i], _kpConfig.DEBUG);
		if (!t_loading[i].loadFromFile(t_loading_files[i])) {
			_kpDebug.sendMessage("ID:" + std::to_string(i) + " FAILED", _kpConfig.ERROR);
		}
	}
	_kpDebug.sendMessage("[ok] Loading loading textures", _kpConfig.INFO);

}
sf::Texture kpTextures::getLoadingTexture(int id) {
	return t_loading[id];
}

void kpTextures::loadTextures() {
	_kpDebug.sendMessage("[..] Loading lights texutes", _kpConfig.VERBOSE);
	for (int i = 0; i<t_lights_files_len; i++) {
		_kpDebug.sendMessage("ID:" + std::to_string(i) + " will be loaded from " + t_lights_files[i], _kpConfig.DEBUG);

		if (!t_lights[i].loadFromFile(t_lights_files[i])) {
			_kpDebug.sendMessage("ID:" + std::to_string(i) + " FAILED", _kpConfig.ERROR);
		}
	}
	_kpDebug.sendMessage("[ok] Loading lights texutes", _kpConfig.INFO);

	_kpDebug.sendMessage("[..] Loading background texture(s)...", _kpConfig.VERBOSE);
	for (int i = 0; i < t_background_files_len; i++) {
		_kpDebug.sendMessage("ID: "+std::to_string(i) + " will be loaded from" + t_background_files[i], _kpConfig.DEBUG);

		if (!t_background[i].loadFromFile(t_background_files[i])) {
			_kpDebug.sendMessage("ID: "+std::to_string(i) + " FAILED!", _kpConfig.ERROR);
		}
	}
	_kpDebug.sendMessage("[ok] Loading background texture(s)...", _kpConfig.INFO);


	_kpDebug.sendMessage("[..] Loading car texture(s)...", _kpConfig.VERBOSE);
	for (int i = 0; i < t_car_files_len; i++) {
		_kpDebug.sendMessage("CAR0_ID: "+std::to_string(i) + " will be loaded from " + t_car_files[0][i], _kpConfig.DEBUG);
		_kpDebug.sendMessage("CAR1_ID: " + std::to_string(i) + " will be loaded from " + t_car_files[1][i], _kpConfig.DEBUG);
		if (!t_car[0][i].loadFromFile(t_car_files[0][i])) {
			_kpDebug.sendMessage("CAR0_ID: "+std::to_string(i) + " FAILED!", _kpConfig.ERROR);
		}
		t_car[0][i].setSmooth(true);

		if (!t_car[1][i].loadFromFile(t_car_files[1][i])) {
			_kpDebug.sendMessage("CAR1_ID: " + std::to_string(i) + " FAILED!", _kpConfig.ERROR);

		}
		t_car[1][i].setSmooth(true);


	}

	_kpDebug.sendMessage("[ok] Loading car texture(s)...", _kpConfig.INFO);

	_kpDebug.sendMessage("[..] Loading misc texture(s)...", _kpConfig.VERBOSE);
	for (int i = 0; i < t_misc_files_len; i++) {
		_kpDebug.sendMessage("ID: " + std::to_string(i) + " will be loaded from" + t_misc_files[i], _kpConfig.DEBUG);
		if (!t_misc[i].loadFromFile(t_misc_files[i])) {
			_kpDebug.sendMessage("ID: " + std::to_string(i) + " FAILED!", _kpConfig.ERROR);
		}
	}
	for (int i = 0; i < t_lightning_files_len; i++) {
		_kpDebug.sendMessage("ID: " + std::to_string(i) + " will be loaded from" + t_lightning_files[i], _kpConfig.DEBUG);
		if (!t_lightning[i].loadFromFile(t_lightning_files[i])) {
			_kpDebug.sendMessage("ID: " + std::to_string(i) + " FAILED!", _kpConfig.ERROR);
		}

	}
	_kpDebug.sendMessage("[ok] Loading misc texture(s)...", _kpConfig.INFO);

	/* NOT IMPLEMENTED
	_kpDebug.sendMessage("[..] Loading car lights texture(s)...", _kpConfig.VERBOSE);
	for (int i = 0; i < t_carLights_files_len; i++) {
		_kpDebug.sendMessage("ID: "+std::to_string(i) + " will be loaded from " + t_carLights_files[i], _kpConfig.DEBUG);
		if (!(t_carLights[0][i].loadFromFile(t_carLights_files[i]))) { //Changeme
			_kpDebug.sendMessage("ID: "+std::to_string(i) + " FAILED!", _kpConfig.ERROR);
		}

	}
	_kpDebug.sendMessage("[ok] Loading car lights texture(s)...", _kpConfig.INFO);
	*/
	
}

sf::Texture kpTextures::getBackgroundTexture(int id) {
	_kpDebug.sendMessage("[!] Returning background texture [" + std::to_string(id) + "]", _kpConfig.VERBOSE);
	return t_background[id];
}
sf::Texture kpTextures::getLightsTexture(int id) {
	_kpDebug.sendMessage("[!] Returning lights texture [" + std::to_string(id) + "]", _kpConfig.VERBOSE);
	return t_lights[id];
}
sf::Texture kpTextures::getCarTexture(int id, int id2) {
	_kpDebug.sendMessage("[!] Returning car texture [" + std::to_string(id2) + "] for model ["+std::to_string(id)+ "]", _kpConfig.VERBOSE);
	return t_car[id][id2];
}
sf::Texture kpTextures::getCarLightsTexture(int id, int id2) {
	//NOT IMPLEMENTED
	_kpDebug.sendMessage("[!] Returning car lights texture [" + std::to_string(id) + "],["+std::to_string(id2)+ "] ", _kpConfig.VERBOSE);
	return t_carLights[id][id2];
}
sf::Texture kpTextures::getMiscTexture(int id) {
	_kpDebug.sendMessage("[!] Returning misc texture [" + std::to_string(id) + "]", _kpConfig.VERBOSE);
	return t_misc[id];
}
sf::Texture kpTextures::getLightningTexture(int id) {
	_kpDebug.sendMessage("[!] Returning lightning texture [" + std::to_string(id) + "]", _kpConfig.VERBOSE);
	return t_lightning[id];

}
sf::Vector2f kpTextures::scaleTexture(sf::Vector2u windowSize, sf::Vector2u textureSize) {

	float scaleX = (float)windowSize.x / textureSize.x;
	float scaleY = (float)windowSize.y / textureSize.y;
	return sf::Vector2f(scaleX, scaleY);
}