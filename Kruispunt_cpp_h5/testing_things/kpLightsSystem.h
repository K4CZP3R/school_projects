#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpLightsSystem {
private:
	sf::Vector2f lightLocations[4] = { sf::Vector2f(450,100),
		sf::Vector2f(710,125),
		sf::Vector2f(710,410),
		sf::Vector2f(480,410) };
	sf::Vector2f lightSizes[4] = { sf::Vector2f(40,80),sf::Vector2f(40,40),sf::Vector2f(80,40),sf::Vector2f(40,80) };
	std::string lightNames[4] = { "up", "right", "down", "left" };
	sf::Texture lightTextures[4];

	sf::Sprite lightSprites[4] = {};

	kpDebug _kpDebug;

	int l1, l2, l3, l4;
public:
	kpLightsSystem(sf::Texture text_default, sf::Texture text_red, sf::Texture text_yellow, sf::Texture text_green);
	sf::FloatRect getPosition(int n);
	sf::Sprite getSprite(int n);
	void performLogic();
	void applyActions();
	int getLightState(int n);
};