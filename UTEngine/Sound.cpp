#include "Sound.h"
#include "SDL_mixer.h"
#include <filesystem>

Sound::Sound(std::filesystem::path path)
{
	filename = path.filename().string();
	extension = path.extension().string();
	stem = path.stem().string();

	sound = Mix_LoadWAV(("assets/sounds/" + filename).c_str());
}

std::string Sound::getExtension(void) const
{
	return extension;
}

std::string Sound::getFilename(void) const
{
	return extension;
}

std::string Sound::getStem(void) const
{
	return stem;
}

Mix_Chunk* Sound::getSound(void) const
{
	return sound;
}

std::ostream& operator<<(std::ostream& out, const Sound& music)
{
	out << music.filename;
	return out;
}