//
// Created by jonathanmedina on 14/06/19.
//

#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(SoundFactory &soundFactory) : soundFactory(soundFactory) {
}

void MusicPlayer::playBackgroundMusic() {
    Mix_PlayMusic(soundFactory.getMusic(), -1);
}

void MusicPlayer::playLoserSong() {
    Mix_HaltMusic();
    Mix_PlayMusic(soundFactory.getLoserMusic(), -1);
}

void MusicPlayer::playGateOpening() {
    std::string file_name("gate_open");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}

void MusicPlayer::playGateClosing() {
    std::string file_name("gate_close");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}

void MusicPlayer::playPlayerFiring() {
    std::string file_name("player_firing");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}

void MusicPlayer::playPlayerJumping() {
    std::string file_name("player_jumping");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}
