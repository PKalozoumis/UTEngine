#pragma once
#include <iostream>
#include <filesystem>
#include "SDL_mixer.h"

class Music
{
	private:
		std::string filename;
		std::string extension;
		std::string stem;

		Mix_Music* music;

	public:
		Music(std::filesystem::path path); //Used when iterating through the directories

		std::string getFilename(void) const;
		std::string getStem(void) const;
		std::string getExtension(void) const;
		Mix_Music* getMusic(void) const;

	friend std::ostream& operator<<(std::ostream& out, const Music& music);
};

