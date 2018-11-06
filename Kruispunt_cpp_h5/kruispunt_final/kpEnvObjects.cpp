#include "pch.h"
#include "kpEnvObjects.h"
kpEnvObjects::kpEnvObjects() {
	_kpDebug.setLocation("kpEnvObjects");

	_kpDebug.sendMessage("[..] Loading textures", _kpConfig.VERBOSE);
	_kpTextures.loadTextures();
	for (int i = 0; i < _kpTextures.t_misc_files_len; i++) {
		miscTextures[i] = _kpTextures.getMiscTexture(i);
	}
	for (int i = 0; i < _kpTextures.t_lightning_files_len; i++) {
		lightningTextures[i] = _kpTextures.getLightningTexture(i);
	}
	_kpDebug.sendMessage("[ok] Loading textures", _kpConfig.INFO);

	for (int i = 0; i < treeShapes_len; i++) {
		treeShapes[i].setPosition(treeLocations[i]);
		treeShapes[i].setSize(treeSize);
		treeShapes[i].setTexture(&miscTextures[0]);
	}
	for (int i = 0; i < lightningShapes_len; i++) {
		lightningSprites[i].setTexture(lightningTextures[0]);
		lightningSprites[i].setPosition(sf::Vector2f(-600.f, 0.f));
		//lightningSprites[i].setScale(_kpTextures.scaleTexture(sf::Vector2u(1200, 600), lightningTextures[0].getSize()));

	}


}

sf::RectangleShape kpEnvObjects::doGetTreeShapeToDraw(int n) {
	return treeShapes[n];
}
int kpEnvObjects::getNTreeShapes() {
	return treeShapes_len;
}
sf::Sprite kpEnvObjects::doGetLightningSpriteToDraw(int n) {
	return lightningSprites[n];
}
