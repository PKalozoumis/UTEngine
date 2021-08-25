#pragma once

#include <iostream>
#include "Text.h"
#include <map>

class Debug
{

	public:
		void init(void);
		void update(void);
		void draw(void);

	private:
		std::map<std::string, Text*> textMap;
};

