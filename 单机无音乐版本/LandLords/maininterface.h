#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QSound>
#include "cardpicture.h"
#include "gameprocess.h"
#include "hand.h"

class QLabel;

namespace Ui {
class MainInterface;
}


class MainInterface : public QWidget
{
    Q_OBJECT

public:
    /*explicit */MainInterface(QWidget *parent = 0);
    ~MainInterface();
        void paintEvent(QPaintEvent *);//设置游戏大厅背景
        void Init();
        void InitCardsMap();//初始化m_Cards

        void CutCardPic(int x,int y,Card c);
        void UpdateCards(GamePlayer* player);
        void PickingCardsAnimation(GamePlayer* player);

        void PlayerStartCallingLord();  //玩家开始叫地主
         void PlayerStartPlayingHand(); //玩家开始打地主

         void ReStart();   //重新开始发牌


public slots:
        void NoOneCallLord();       //没人叫地主
        void StartProcess(GameProcess::GameStatus status);   //发牌
        void PickingCards();
        void CardSelected();
        void CallingLord(GamePlayer* player,int bet);
        void SetPlayerStatus(GamePlayer* player,GamePlayer::PlayerStatus status);
        void PlayingHand(GamePlayer* player, QList<Card> cards);


        /*按钮槽*/
        void start_clicked();//游戏开始的槽

        void bet0_clicked();
        void bet1_clicked();
        void bet2_clicked();
        void bet3_clicked();

        void continue_clicked();//继续打牌的槽


        void playhand_clicked();
        void pass_clicked();
        void tip_clicked();

        void timeDisplay();         //倒数时间显示


private:
    Ui::MainInterface *ui;
    QMap<Card,CardPicture*> m_Cards;
    QSet<CardPicture*> m_Selected;
    QList<CardPicture*> m_restThreeCards;

    QPixmap m_cardBackPic;
    QPixmap m_cardBasePic;
    QPixmap m_AllCardsPic;  //所有牌的集合象图

    QLabel* m_rePickingCards;   //重新发牌标识
    QLabel* m_clock;       //闹钟图标
    QLabel* m_timeLabel;   //显示倒数时间
    QTimer* timer;              //叫地主计时器
    int time;                   //倒数时间

    CardPicture* m_movingcard;
    CardPicture* m_basecard;   //中间固定的牌

    QPoint m_basecardPos;   //???
    int MoveDistance;
    QTimer* m_pickingCardTimer;
    GameProcess* m_gameprocess;

    /*按钮*/
    QPushButton* m_start;
    QPushButton* m_bet0;
    QPushButton* m_bet1;
    QPushButton* m_bet2;
    QPushButton* m_bet3;
    QPushButton* m_playhand;
    QPushButton* m_pass;
    QPushButton* m_continue;
    QPushButton* m_tip;


};

#endif // MAININTERFACE_H
