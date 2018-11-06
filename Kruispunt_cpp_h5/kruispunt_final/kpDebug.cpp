#include "pch.h"
#include "kpDebug.h"

void kpDebug::setLocation(std::string _location) {
	if (location.length() != 0) {
		std::cout << "[void] " << "Location: " << location << " --> " << _location << std::endl;
	}
	else {
		std::cout << "[void] " << "New location: " << _location << std::endl;
	}
	location = _location;
}

void kpDebug::sendMessage(std::string content, int messageLevel) {
	if (messageLevel >= _kpConfig.debugMinimumLevel) {
		std::string toSend = "[" + location + "] " + content;
		std::cout << toSend << std::endl;
	}
}