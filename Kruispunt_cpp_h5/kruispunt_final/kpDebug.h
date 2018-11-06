#pragma once
#include <iostream>
#include <string>
#include "kpConfig.h"


class kpDebug {
private:
	kpConfig _kpConfig;
	std::string location;
public:
	void setLocation(std::string _location);
	void sendMessage(std::string content, int messageLevel);
};