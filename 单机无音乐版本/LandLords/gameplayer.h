#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include <QWidget>
#include <QSet>
#include <QLabel>
#include "card.h"

inline bool operator == (const Card c1,const Card c2)
{
    return (c1.point==c2.point)&&(c1.suit==c2.suit);
}

inline uint qHash(const Card& c)
{
    return c.point * 100 + c.suit;
}

inline bool operator <(const Card c1,const Card c2)
{
    if(c1.point==c2.point)
        return c1.suit<c2.suit;
    else
        return c1.point<c2.point;
}


class GamePlayer : public QWidget
{
    Q_OBJECT
public:
    enum Role
    {
        Farmer,  //平民
        Lord   //地主
    };

    enum PlayerStatus
    {
        waitingCallingLord,
        waitingPlayingHand,
        winning
    };



    GamePlayer(QWidget *parent = 0);
    GamePlayer(int id = 0, QString name="Unknow", int score = 0, int level = 0);

    void setName(QString name);
    QString getName();
    void setScore(int s);
    int getScore();
    void setLevel(int l);
    int getLevel();
    void setId(int id);
    int getId();

    void setBet(int bet);
    int getBet();

    void setRole(Role role);
    Role getRole();

    void sortCard();          //牌排序
    void addCard(Card c);     //添加牌
    void removeCard(Card c);  //清除牌
    void removeCard(QList<Card> &c);

    void callingLord(int bet);
    void playHand(QList<Card> cards);
    QList<Card> &getCards();
    QList<int> &getCardsIntList();
    QList<Card> &getCardsToPlay();

    void addCardToPlay(QList<Card> cards);
    GamePlayer *getHitPlayer();
    QList<Card> getHitCards();
    GamePlayer *getNextPlayer();
    void setNextPlayer(GamePlayer *player);

    virtual void beginPlayingHand();
    virtual void beginCallingLord();

    QLabel *passLabel;
    QLabel *betLabel;
    QLabel *roleLabel;

    int m_betOrder;

signals:
    void TellCallingLord(GamePlayer *player, int bet);
    void TellPlayingHand(GamePlayer *player,QList<Card> cards);

public slots:
    void setHitPlayer(GamePlayer *player, QList<Card> cards);

protected:
    int m_id;
    QString m_name;
    int m_score;
    int m_level;
    Role m_role;

    GamePlayer *m_nextPlayer;
    GamePlayer *m_hitPlyer;
    QList<Card> m_hitCards;

    QList<Card> m_cards;    //牌组
    QList<int> m_cardsIntList;  //整数数组

    QList<Card> m_cardsToPlay; //要打出去的派
    QList<Card> m_lastPlayedCards; //上次出牌
    PlayerStatus m_playerStatus;  //玩家状态


};

#endif // GAMEPLAYER_H
