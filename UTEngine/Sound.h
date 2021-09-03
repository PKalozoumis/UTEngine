#pragma once
#include <iostream>
#include <filesystem>
#include "SDL_mixer.h"

class Sound
{
	private:
		std::string filename;
		std::string extension;
		std::string stem;

		Mix_Chunk* sound;

	public:
		Sound(std::filesystem::path path); //Used when iterating through the directories

		std::string getFilename(void) const;
		std::string getStem(void) const;
		std::string getExtension(void) const;
		Mix_Chunk* getSound(void) const;

	friend std::ostream& operator<<(std::ostream& out, const Sound& music);
};

