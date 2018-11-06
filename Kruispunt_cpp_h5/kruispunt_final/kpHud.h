#pragma once
#include <SFML/Graphics.hpp>
#include "kpDebug.h"

class kpHud {
private:
	sf::Font hudFont;

	sf::Vector2f hudPosition;
	std::string hudContent;
	sf::Color hudFontColor;
	int hudFontSize;
	sf::Vector2f hudPos;

	sf::Vector2f mouseHudPosition;
	std::string mouseHudContent;
	sf::Color mouseHudFontColor;
	int mouseHudFontSize;
	sf::Vector2i mouseHudPos;

	kpDebug _kpDebug;
public:
	kpHud(std::string _fontFile, int _hudFontSize, sf::Color _hudFontColor, sf::Vector2f _hudPos, int _mouseHudFontSize, sf::Color _mouseHudFontColor);
	void updateHud(std::string newContent);
	sf::Text getHud();
	void updateMouseHud(std::string newContent, sf::Vector2i _mousePos);
	sf::Text getMouseHud();

};