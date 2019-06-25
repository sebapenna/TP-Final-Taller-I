//
// Created by jonathanmedina on 20/06/19.
//

#include "SoundFactory.h"
#include "SDLException.h"

#ifdef DEBUG_MODE
#define SONG_PORTAL "assets/backgroundSong/song_portal_you_will_be_perfect.mp3"
#else
#define SONG_PORTAL "/etc/Portal/assets/backgroundSong/song_portal_you_will_be_perfect.mp3"
#endif

#ifdef DEBUG_MODE
#define LOSER "assets/backgroundSong/loser_music.mp3"
#else
#define LOSER "/etc/Portal/assets/backgroundSong/loser_music.mp3"
#endif

#ifdef DEBUG_MODE
#define GATE_OPEN "assets/soundeffects/scenario/gate_open.wav"
#else
#define GATE_OPEN "/etc/Portal/assets/soundeffects/scenario/gate_open.wav"
#endif


#ifdef DEBUG_MODE
#define GATE_CLOSE "assets/soundeffects/scenario/gate_close.wav"
#else
#define GATE_CLOSE "/etc/Portal/assets/soundeffects/scenario/gate_close.wav"
#endif

#ifdef DEBUG_MODE
#define BUTTON_PRESS "assets/soundeffects/scenario/button_press.wav"
#else
#define BUTTON_PRESS "/etc/Portal/assets/soundeffects/scenario/button_press.wav"
#endif

#ifdef DEBUG_MODE
#define BUTTON_UNPRESS "assets/soundeffects/scenario/button_press.wav"
#else
#define BUTTON_UNPRESS "/etc/Portal/assets/soundeffects/scenario/button_unpress.wav"
#endif

#ifdef DEBUG_MODE
#define FIRING "assets/soundeffects/player/firing.wav"
#else
#define FIRING "/etc/Portal/assets/soundeffects/player/firing.wav"
#endif

#ifdef DEBUG_MODE
#define JUMP "assets/soundeffects/player/jump.wav"
#else
#define JUMP "/etc/Portal/assets/soundeffects/player/jump.wav"
#endif

#ifdef DEBUG_MODE
#define DISAPPEARING "assets/soundeffects/player/disappearing.wav"
#else
#define DISAPPEARING "/etc/Portal/assets/soundeffects/player/disappearing.wav"
#endif

#ifdef DEBUG_MODE
#define WINNING "assets/soundeffects/player/winning_noise.wav"
#else
#define WINNING "/etc/Portal/assets/soundeffects/player/winning_noise.wav"
#endif

SoundFactory::SoundFactory() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS(SONG_PORTAL);
    loser_music = Mix_LoadMUS(LOSER);
    effects["gate_open"] = getChunkFromFile(GATE_OPEN);
    effects["gate_close"] = getChunkFromFile(GATE_CLOSE);
    effects["player_firing"] = getChunkFromFile(FIRING);
    effects["player_jumping"] = getChunkFromFile(JUMP);
    effects["button_press"] = getChunkFromFile(BUTTON_PRESS);
    effects["button_unpress"] = getChunkFromFile(BUTTON_UNPRESS);
    effects["disappearing"] = getChunkFromFile(DISAPPEARING);
    effects["winning_noise"] = getChunkFromFile(WINNING);
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
    if (!soundeffect) {
        throw SDLException("Error while loading sound effect", Mix_GetError());
    }
    return soundeffect;
}

Mix_Music *SoundFactory::getLoserMusic() {
    return loser_music;
}
