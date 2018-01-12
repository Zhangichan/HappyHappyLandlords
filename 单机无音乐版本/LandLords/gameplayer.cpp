#include "gameplayer.h"

GamePlayer::GamePlayer(QWidget *parent) : QWidget(parent)
{
    m_hitPlyer = NULL;
    m_hitCards.clear();
}

GamePlayer::GamePlayer(int id, QString name, int score, int level)
{
    m_id = id;
    m_name = name;
    m_score = score;
    m_level = level;
    m_hitPlyer = NULL;
    m_hitCards.clear();
}

void GamePlayer::setName(QString name)
{
    m_name = name;
}

QString GamePlayer::getName()
{
    return m_name;
}

void GamePlayer::setLevel(int level)
{
    m_level = level;
}

int GamePlayer::getLevel()
{
    return m_level;
}

void GamePlayer::setScore(int s)
{
    m_score = s;
}

int GamePlayer::getScore()
{
    return m_score;
}

void GamePlayer::setId(int id)
{
    m_id = id;
}

int GamePlayer::getId()
{
    return m_id;
}

void GamePlayer::setRole(Role role)
{
    m_role = role;
    return;
}

GamePlayer::Role GamePlayer::getRole()
{
    return m_role;
}

void GamePlayer::addCard(Card c)
{
    m_cards.append(c);
    return;
}

void GamePlayer::removeCard(QList<Card> &c)
{
    for(int i = 0; i < c.size(); i++)
        m_cards.removeOne(c[i]);
    return;
}

QList<Card> &GamePlayer::getCards()
{
    return m_cards;
}

QList<int>& GamePlayer::getCardsIntList()
{
    return m_cardsIntList;
}

QList<Card> &GamePlayer::getCardsToPlay()
{
    return m_cardsToPlay;
}

void GamePlayer::sortCard()
{
    qSort(m_cards.begin(),m_cards.end(),qGreater<Card>());
    return;
}
void GamePlayer::callingLord(int bet)
{
    emit TellCallingLord(this,bet);
}

void GamePlayer::playHand(QList<Card> cards)
{
    if(!cards.isEmpty())
        removeCard(cards);  //从牌组中清除
    emit TellPlayingHand(this,cards); //发送信号
}

void  GamePlayer::addCardToPlay(QList<Card> cards)
{
    for(int i = 0; i<cards.size();i++)
        m_cardsToPlay.append(cards[i]);
}

GamePlayer *GamePlayer::getHitPlayer()
{
    return m_hitPlyer;
}

void GamePlayer::setHitPlayer(GamePlayer *player, QList<Card> cards)
{
    m_hitPlyer = player;
    m_hitCards = cards;
}

GamePlayer *GamePlayer::getNextPlayer()
{
    return m_nextPlayer;
}

void GamePlayer::setNextPlayer(GamePlayer *player)
{
    m_nextPlayer=player;
}

QList<Card> GamePlayer::getHitCards()
{
    return m_hitCards;
}

void GamePlayer::beginCallingLord()
{}

void GamePlayer::beginPlayingHand()
{}
