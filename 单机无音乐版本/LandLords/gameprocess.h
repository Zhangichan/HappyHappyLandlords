#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QWidget>
#include <QTime>
#include <QMap>
#include "robot.h"
#include "userplayer.h"

class GameProcess : public QWidget
{
    Q_OBJECT
public:
    enum GameStatus
    {
        PickingCard,
        CallingLord,
        PlayingHand,
    };

    GameProcess(QWidget *parent = 0);

    void getOneCard(GamePlayer *player);                 //添加一张牌到当前玩家的牌组中
    void setCurrentPlayer(GamePlayer *player);
    GamePlayer *getLeftPlayer();
    GamePlayer *getRightPlayer();
    GamePlayer *getDownPlayer();

    GamePlayer *getCurrentPlayer();
    GamePlayer *getNextPlayer();
    GamePlayer *getPrevPlayer();

    GamePlayer *getHitPlayer();  //获取当前最大牌的玩家
    void setHitPlayer(GamePlayer *player);
    QList<Card> getHitCards();

    QList<Card> getAllCards();
    void beginPlayHand();
    void InitCards();       //初始化m_allCards
    void Restart();         //重新开始时用的初始化

    GameStatus m_gamestatus;
    QMap<GamePlayer *,int> BetList;      //记录玩家和对应的叫分

    int betLeftOrder;
    int betDownOrder;
    int betRightOrder;

signals:
    /*告知MainInterface的信号*/
    void TellGameProcess(GameProcess::GameStatus);
    void TellPlayerStatus(GamePlayer *player,GamePlayer::PlayerStatus status);
    void TellPlayerPlayHand(GamePlayer *player,QList<Card> cards);
    void TellPlayerCallLord(GamePlayer *player,int bet);

    /*告知Player的信号*/
    void TellHitPlayer(GamePlayer *player,QList<Card> cards);

public slots:
    void PlayerCallLord(GamePlayer *player,int bet);
    void PlayerPlayHand(GamePlayer *player,QList<Card> cards);

private:
    Robot *m_LeftPlayer;
    Robot *m_RightPlayer;
    UserPlayer *m_DownPlayer;

    GamePlayer *m_currentPlayer;        //当前玩家

    QList<Card> m_allCards;         //所有牌的card
    GamePlayer *m_hitPlayer;            //当前最大牌的玩家
    QList<Card> m_hitCards;         //当前最大牌

};

#endif // GAMEPROCESS_H
