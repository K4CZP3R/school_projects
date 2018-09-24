#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpTextures{
private:
	std::string t_lights_files[4] = { "lights_default.png","lights_red.png","lights_yellow.png","lights_green.png" };
	sf::Texture t_lights[4];

	kpDebug _kpDebug;
public:
	kpTextures();
	void loadTextures();
	sf::Texture getTexture(int category, int id);
};