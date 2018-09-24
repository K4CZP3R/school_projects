#include "pch.h"
#include "kpHud.h"
#include <iostream>

kpHud::kpHud(std::string _fontFile, int _hudFontSize, sf::Color _hudFontColor, sf::Vector2f _hudPos, int _mouseHudFontSize, sf::Color _mouseHudFontColor) {
	_kpDebug.setLocation("kpHud");

	if (!hudFont.loadFromFile(_fontFile)) {
		_kpDebug.sendMessage("Error while reading font file (" + _fontFile + ")");
	}
	hudFontSize = _hudFontSize;
	hudFontColor = _hudFontColor;
	hudPos = _hudPos;

	mouseHudFontSize = _mouseHudFontSize;
	mouseHudFontColor = _mouseHudFontColor;
}

void kpHud::updateHud(std::string newContent) {
	hudContent = newContent;
}

sf::Text kpHud::getHud() {
	sf::Text text;
	text.setFont(hudFont);
	text.setString(hudContent);
	text.setCharacterSize(hudFontSize);
	text.setFillColor(hudFontColor);
	text.setPosition(hudPosition);
	return text;
}

void kpHud::updateMouseHud(std::string newContent, sf::Vector2i _mousePos) {
	mouseHudPos = _mousePos;
	mouseHudContent = "x:" + std::to_string(_mousePos.x) + ",y:" + std::to_string(_mousePos.y) + "\n" + newContent;
}

sf::Text kpHud::getMouseHud() {
	sf::Text text;
	text.setFont(hudFont);
	text.setString(mouseHudContent);
	text.setCharacterSize(mouseHudFontSize);
	text.setFillColor(mouseHudFontColor);
	text.setPosition(mouseHudPos.x, mouseHudPos.y);
	return text;
}