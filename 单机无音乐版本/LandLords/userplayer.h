#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QWidget>
#include "gameplayer.h"

class UserPlayer:public GamePlayer
{
public:
    UserPlayer(QWidget *parent);
    void beginPlayingHand();
    void beginCallingLord();
};

#endif // USERPLAYER_H
