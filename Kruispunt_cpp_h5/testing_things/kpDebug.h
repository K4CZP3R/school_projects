#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class kpDebug {
private:
	std::string location;
public:
	void setLocation(std::string _location);
	void sendMessage(std::string content);
};