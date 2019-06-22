//
// Created by jonathanmedina on 20/06/19.
//

#include "SoundFactory.h"
#include "SDLException.h"


SoundFactory::SoundFactory() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("assets/backgroundSong/song_portal_you_will_be_perfect.mp3");
    loser_music = Mix_LoadMUS("assets/backgroundSong/loser_music.mp3");
    effects["gate_open"] = getChunkFromFile("assets/soundeffects/scenario/gate_open.wav");
    effects["gate_close"] = getChunkFromFile("assets/soundeffects/scenario/gate_close.wav");
    effects["player_firing"] = getChunkFromFile("assets/soundeffects/player/firing.wav");
    effects["player_jumping"] = getChunkFromFile("assets/soundeffects/player/jump.wav");
    effects["button_press"] = getChunkFromFile("assets/soundeffects/scenario/button_press.wav");
    effects["button_unpress"] = getChunkFromFile("assets/soundeffects/scenario/button_press.wav");
}

SoundFactory::~SoundFactory() {
    Mix_FreeMusic(music);
    Mix_FreeMusic(loser_music);
    for (auto& chunk : effects) {
        Mix_FreeChunk(chunk.second);
    }
    Mix_CloseAudio();
}


Mix_Chunk *SoundFactory::getChunk(std::string& chunk_name) {
    return effects[chunk_name];
}

Mix_Music *SoundFactory::getMusic() {
    return music;
}

Mix_Chunk *SoundFactory::getChunkFromFile(const std::string &file_name) {
    Mix_Chunk* soundeffect = Mix_LoadWAV(file_name.c_str());
    if (soundeffect == NULL) {
        throw SDLException("Error while loading sound effect", SDL_GetError());
    }
    return soundeffect;
}

Mix_Music *SoundFactory::getLoserMusic() {
    return loser_music;
}
