#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"
#include "kpConfig.h"

class kpLightsSystem {
private:
	sf::Vector2f lightLocations[4] = { 
		sf::Vector2f(450,120),
		sf::Vector2f(780,150),
		sf::Vector2f(750,480),
		sf::Vector2f(420,450) };

	sf::Vector2f lightSizes[4] = { sf::Vector2f(80,80),sf::Vector2f(80,80),sf::Vector2f(80,80),sf::Vector2f(80,80) };
	std::string lightNames[4] = { "up", "right", "down", "left" };
	sf::Texture lightTextures[4];
	float lightRotation[4] = { 0.f, 90.f, 180.f, 270.f };

	sf::Sprite lightSprites[4] = {};

	kpDebug _kpDebug;

	bool lightsGlobal_setAllToGreen = false;
	bool lightsGlobal_setAllToRed = false;
	int l1, l2, l3, l4;
public:
	kpLightsSystem(sf::Texture text_default, sf::Texture text_red, sf::Texture text_yellow, sf::Texture text_green);
	sf::FloatRect getPosition(int n);
	sf::Sprite getSprite(int n);
	void performLogic();
	void applyActions();
	int getLightState(int n);
};