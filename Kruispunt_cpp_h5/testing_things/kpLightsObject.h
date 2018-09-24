#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpLightsObject {
private:
	sf::Vector2f lightLocations[4] = { sf::Vector2f(450,100),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0) };
	sf::Vector2f lightSizes[4] = { sf::Vector2f(40,80),sf::Vector2f(80,40),sf::Vector2f(80,40),sf::Vector2f(40,80) };
	std::string lightNames[4] = { "up", "right", "down", "left" };
	int lightId;
	sf::Vector2f position;
	sf::Texture lightTextures[4];
	sf::Sprite lightSprite;

	std::string location;
	kpDebug _kpDebug;
public:
	void initLight(std::string location, sf::Texture text_default, sf::Texture text_red, sf::Texture text_yellow, sf::Texture text_green);
	sf::FloatRect getPosition();
	sf::Sprite getSprite();
	void switchLight();
	void switchLight(int toState);
	void update();
};