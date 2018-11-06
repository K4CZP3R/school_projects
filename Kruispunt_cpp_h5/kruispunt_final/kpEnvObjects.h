#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"
#include "kpTextures.h"
#include "kpConfig.h"

class kpEnvObjects {
private:
	kpDebug _kpDebug;
	kpConfig _kpConfig;
	kpTextures _kpTextures;
	
	sf::Texture miscTextures[1];

	sf::RectangleShape treeShapes[4];
	const size_t treeShapes_len = sizeof(treeShapes) / sizeof(treeShapes[0]);
	sf::Vector2f treeLocations[4] = {
		sf::Vector2f(20.f, 310.f),
		sf::Vector2f(120.f, 310.f),
		sf::Vector2f(220.f, 310.f),
		sf::Vector2f(320.f, 310.f),
	};
	sf::Vector2f treeSize = sf::Vector2f(75.f, 100.f);

	sf::Texture lightningTextures[1];
	sf::Sprite lightningSprites[2];
	const size_t lightningShapes_len = sizeof(lightningSprites) / sizeof(lightningSprites[0]);

public:
	kpEnvObjects();
	sf::RectangleShape doGetTreeShapeToDraw(int n);
	int getNTreeShapes();
	sf::Sprite doGetLightningSpriteToDraw(int n);

	
};