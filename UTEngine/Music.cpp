#include "Music.h"
#include "SDL_mixer.h"
#include <filesystem>

Music::Music(std::filesystem::path path)
{
	filename = path.filename().string();
	extension = path.extension().string();
	stem = path.stem().string();

	music = Mix_LoadMUS(("assets/music/" + filename).c_str());
}

std::string Music::getExtension(void) const
{
	return extension;
}

std::string Music::getFilename(void) const
{
	return extension;
}

std::string Music::getStem(void) const
{
	return stem;
}

Mix_Music* Music::getMusic(void) const
{
	return music;
}

std::ostream& operator<<(std::ostream& out, const Music& music)
{
	out << music.filename;
	return out;
}
