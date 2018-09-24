#include "pch.h"
#include "kpLightsSystem.h"

kpLightsSystem::kpLightsSystem(sf::Texture text_default, sf::Texture text_red, sf::Texture text_yellow, sf::Texture text_green) {
	int i;
	_kpDebug.setLocation("kpLightSystem");

	_kpDebug.sendMessage("Mapping textures");
	sf::Texture _lightTextures[4] = { text_default, text_red, text_yellow, text_green };
	for (i = 0; i < 4; i++) {
		lightTextures[i] = _lightTextures[i];
	}

	_kpDebug.sendMessage("Setting texture, pos and scale");
	for (i = 0; i < 4; i++) {
		lightSprites[i].setTexture(lightTextures[i]);
		lightSprites[i].setPosition(lightLocations[i]);
		
		lightSprites[i].setScale(0.5, 0.5);
	}
	l1 = 3;
	l2 = 1;
	l3 = 1;
	l4 = 1;
}

sf::FloatRect kpLightsSystem::getPosition(int n) {
	return lightSprites[n].getGlobalBounds();
}
sf::Sprite kpLightsSystem::getSprite(int n) {
	return lightSprites[n];
}
void kpLightsSystem::performLogic() {
	if (l1 == 3 && l2 == 1 && l3 == 1 && l4 == 1) {
		l1 = 2;
		l2 = 2;
		return;
	}
	if (l1 == 2 && l2 == 2 && l3 == 1 && l4 == 1) {
		l1 = 1;
		l2 = 3;
		return;
	}
	if (l1 == 1 && l2 == 3 && l3 == 1 && l4 == 1) {
		l2 = 2;
		l3 = 2;
		return;
	}
	if (l1 == 1 && l2 == 2 && l3 == 2 && l4 == 1) {
		l2 = 1;
		l3 = 3;
		return;
	}
	if (l1 == 1 && l2 == 1 && l3 == 3 && l4 == 1) {
		l3 = 2;
		l4 = 2;
		return;
	}
	if (l1 == 1 && l2 == 1 && l3 == 2 && l4 == 2) {
		l3 = 1;
		l4 = 3;
		return;
	}
	if (l1 == 1 && l2 == 1 && l3 == 1 && l4 == 3) {
		l1 = 2;
		l4 = 2;
		return;
	}
	if (l1 == 2 && l2 == 1 && l3 == 1 && l4 == 2) {
		l1 = 3;
		l4 = 1;
		return;
	}
}
int kpLightsSystem::getLightState(int n) {
	
	const int lightsState[4] = { l1,l2,l3,l4 };
	return lightsState[n];

}
void kpLightsSystem::applyActions() {
	lightSprites[0].setTexture(lightTextures[l1]);
	lightSprites[1].setTexture(lightTextures[l2]);
	lightSprites[2].setTexture(lightTextures[l3]);
	lightSprites[3].setTexture(lightTextures[l4]);
}
