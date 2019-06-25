//
// Created by jonathanmedina on 20/06/19.
//

#ifndef PORTAL_SOUNDFACTORY_H
#define PORTAL_SOUNDFACTORY_H
#include <SDL2/SDL_mixer.h>
#include <map>

// This class holds all the soundeffect and music from the game
class SoundFactory {
private:
    std::map<std::string, Mix_Chunk *> effects;
    Mix_Music *music;
    Mix_Music *loser_music;


    // Get the chunk from a file
    Mix_Chunk *getChunkFromFile(const std::string &file_name);
public:
    // Loads all the sound assets
    SoundFactory();

    ~SoundFactory();

    // Get a chunk from the effects list
    Mix_Chunk *getChunk(std::string& chunk_name);

    Mix_Music *getLoserMusic();
    Mix_Music *getMusic();
};


#endif //PORTAL_SOUNDFACTORY_H
