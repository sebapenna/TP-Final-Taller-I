//
// Created by jonathanmedina on 14/06/19.
//

#ifndef PORTAL_MUSICPLAYER_H
#define PORTAL_MUSICPLAYER_H


#include "SoundFactory.h"

class MusicPlayer {
private:
    SoundFactory& soundFactory;
public:
    MusicPlayer(SoundFactory& soundFactory);
    void playBackgroundMusic();
    void playLoserSong();
    void playGateOpening();
    void playGateClosing();
    void playPlayerFiring();
    void playPlayerJumping();
    void playButtonPress();
    void playButtonUnpress();
    void playDisappearingPlayer();
    void playWinningNoise();
};


#endif //PORTAL_MUSICPLAYER_H
