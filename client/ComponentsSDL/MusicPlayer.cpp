//
// Created by jonathanmedina on 14/06/19.
//

#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(SoundFactory &soundFactory) : soundFactory(soundFactory) {
}

void MusicPlayer::playBackgroundMusic() {
    Mix_PlayMusic(soundFactory.getMusic(), -1);
    Mix_VolumeMusic(20);
}

void MusicPlayer::playLoserSong() {
    Mix_HaltMusic();
    Mix_PlayMusic(soundFactory.getLoserMusic(), -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);
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

void MusicPlayer::playButtonPress() {
    std::string file_name("button_press");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}

void MusicPlayer::playButtonUnpress() {
    std::string file_name("button_unpress");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}

void MusicPlayer::playDisappearingPlayer() {
    std::string file_name("disappearing");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}


void MusicPlayer::playWinningNoise() {
    std::string file_name("winning_noise");
    Mix_PlayChannel(-1, soundFactory.getChunk(file_name), 0);
}
