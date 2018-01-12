#ifndef ROBOT_H
#define ROBOT_H

#include <QWidget>
#include <QThread>
#include "gameplayer.h"
#include "method.h"

class Robot:public GamePlayer
{
public:
    Robot(QWidget *parent);
    void beginPlayingHand();
    void beginCallingLord();
};

#endif // ROBOT_H
