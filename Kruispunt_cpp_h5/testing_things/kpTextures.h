#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpTextures{
private:
	const std::string t_lights_files[4] = { "light_red.png","light_red.png","light_yellow.png","light_green.png" };
	sf::Texture t_lights[4];

	const std::string t_background_files[1] = { "background.png" };
	sf::Texture t_background[1];

	const std::string t_car_files[4] = { "car_0.png","car_1.png","car_2.png","car_3.png", };
	sf::Texture t_car[4];
	kpDebug _kpDebug;
public:
	kpTextures();
	void loadTextures();
	sf::Texture getLightsTexture(int id);
	sf::Texture getBackgroundTexture(int id);
	sf::Texture getCarTexture(int id);
};