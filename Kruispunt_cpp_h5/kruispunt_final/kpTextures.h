#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"
#include "kpConfig.h"

class kpTextures {
private:
	const std::string t_lights_files[4] = { "res/light_0.png","res/light_0.png","res/light_1.png","res/light_2.png" };
	sf::Texture t_lights[4];

	const std::string t_background_files[2] = { "res/bg_road.png", "res/bg_mainmenu.png" };
	sf::Texture t_background[2];

	const std::string t_car_files[2][4] = { 
		{	
			"res/car_0.png","res/car_1.png","res/car_2.png","res/car_3.png"
		},
		{
			"res/car_1_0.png", "res/car_1_1.png", "res/car_1_2.png", "res/car_1_3.png"
		}
	};
	sf::Texture t_car[2][4];

	
	const std::string t_carLights_files[4] = { "res/car_0_b.png", "res/car_0_dr.png", "res/car_0_dl.png", "res/car_0_b.png" };
	sf::Texture t_carLights[4][4];

	const std::string t_misc_files[1] = { "res/misc_tree.png" };
	sf::Texture t_misc[1];
		
	sf::Texture t_loading[5];
	const std::string t_loading_files[5] = { "res/loading_0.png", "res/loading_1.png", "res/loading_2.png", "res/loading_3.png", "res/loading_4.png" };

	sf::Texture t_lightning[1];
	const std::string t_lightning_files[1] = { "res/lightning_0.png" };

	kpDebug _kpDebug;
	kpConfig _kpConfig;

public:
	kpTextures();
	void loadTextures();
	sf::Texture getLightsTexture(int id);
	sf::Texture getBackgroundTexture(int id);
	sf::Texture getCarTexture(int id, int id2);
	sf::Texture getCarLightsTexture(int id, int id2);
	sf::Texture getMiscTexture(int id);
	sf::Texture getLightningTexture(int id);

	sf::Vector2f scaleTexture(sf::Vector2u windowSize, sf::Vector2u textureSize);

	const size_t t_lights_files_len = sizeof(t_lights_files) / sizeof(t_lights_files[0]);
	const size_t t_background_files_len = sizeof(t_background_files) / sizeof(t_background_files[0]);
	const size_t t_car_files_len = sizeof(t_car_files[0]) / sizeof(t_car_files[0][0]);
	const size_t t_carLights_files_len = sizeof(t_carLights_files) / sizeof(t_carLights_files[0]);
	const size_t t_misc_files_len = sizeof(t_misc_files) / sizeof(t_misc_files[0]);
	const size_t t_lightning_files_len = sizeof(t_lightning_files) / sizeof(t_lightning_files[0]);

	void loadLoadingTextures();
	const size_t t_loading_files_len = sizeof(t_loading_files) / sizeof(t_loading_files[0]);
	sf::Texture getLoadingTexture(int id);




};