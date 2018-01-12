#include "gameprocess.h"
#include <QDebug>
#include <QCoreApplication>

GameProcess::GameProcess(QWidget *parent) : QWidget(parent)
{
    betDownOrder=0;
    betLeftOrder=0;
    betRightOrder=0;

    m_LeftPlayer =new Robot(this);
    m_RightPlayer=new Robot(this);
    m_DownPlayer =new UserPlayer(this);

    m_currentPlayer = m_DownPlayer;
    m_hitPlayer=NULL;
    m_hitCards=QList<Card>();

    m_LeftPlayer->setNextPlayer(m_DownPlayer);
    m_RightPlayer->setNextPlayer(m_LeftPlayer);
    m_DownPlayer->setNextPlayer(m_RightPlayer);

    /*测试用角色设定*/
    m_RightPlayer->setRole(GamePlayer::Farmer);
    m_LeftPlayer->setRole(GamePlayer::Farmer);
    m_DownPlayer->setRole(GamePlayer::Lord);


    InitCards();

    //连接通知Player的信号
    connect(this,SIGNAL(TellHitPlayer(GamePlayer*,QList<Card>)),m_DownPlayer,SLOT(setHitPlayer(GamePlayer*,QList<Card>)));
    connect(this,SIGNAL(TellHitPlayer(GamePlayer*,QList<Card>)),m_LeftPlayer,SLOT(setHitPlayer(GamePlayer*,QList<Card>)));
    connect(this,SIGNAL(TellHitPlayer(GamePlayer*,QList<Card>)),m_RightPlayer,SLOT(setHitPlayer(GamePlayer*,QList<Card>)));


    /*处理Player的信号*/
    //叫地主信号
    connect(m_DownPlayer,SIGNAL(TellCallingLord(GamePlayer*,int)),this,SLOT(PlayerCallLord(GamePlayer*,int)));
    connect(m_LeftPlayer,SIGNAL(TellCallingLord(GamePlayer*,int)),this,SLOT(PlayerCallLord(GamePlayer*,int)));
    connect(m_RightPlayer,SIGNAL(TellCallingLord(GamePlayer*,int)),this,SLOT(PlayerCallLord(GamePlayer*,int)));


    //出牌信号
    connect(m_DownPlayer,SIGNAL(TellPlayingHand(GamePlayer*,QList<Card>)),this,SLOT(PlayerPlayHand(GamePlayer*,QList<Card>)));
    connect(m_LeftPlayer,SIGNAL(TellPlayingHand(GamePlayer*,QList<Card>)),this,SLOT(PlayerPlayHand(GamePlayer*,QList<Card>)));
    connect(m_RightPlayer,SIGNAL(TellPlayingHand(GamePlayer*,QList<Card>)),this,SLOT(PlayerPlayHand(GamePlayer*,QList<Card>)));
}


GamePlayer* GameProcess::getLeftPlayer()
{
    return m_LeftPlayer;
}

GamePlayer* GameProcess::getRightPlayer()
{
    return m_RightPlayer;
}

GamePlayer* GameProcess::getDownPlayer()
{
    return m_DownPlayer;
}


void GameProcess::setCurrentPlayer(GamePlayer *player)
{
    m_currentPlayer=player;
}


GamePlayer* GameProcess::getCurrentPlayer()
{
    return m_currentPlayer;
}

GamePlayer* GameProcess::getHitPlayer()
{
    return m_hitPlayer;
}

void GameProcess::setHitPlayer(GamePlayer* player)
{
    m_hitPlayer=player;
}
GamePlayer* GameProcess::getNextPlayer()
{
    if( m_currentPlayer == m_LeftPlayer)
        return m_DownPlayer;
    else if( m_currentPlayer == m_DownPlayer)
        return m_RightPlayer;
    else if (m_currentPlayer ==m_RightPlayer)
        return m_LeftPlayer;
}

GamePlayer* GameProcess::getPrevPlayer()
{
    if( m_currentPlayer == m_LeftPlayer)
        return m_RightPlayer;
    else if( m_currentPlayer == m_DownPlayer)
        return m_LeftPlayer;
    else if (m_currentPlayer ==m_RightPlayer)
        return m_DownPlayer;
}

void GameProcess::getOneCard(GamePlayer* player)
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    int i = qrand()% (m_allCards.size());

    player->getCards().append(m_allCards[i]);
    m_allCards.removeAt(i);
}

void GameProcess::PlayerCallLord(GamePlayer *player, int bet)
{
    emit TellPlayerCallLord(player,bet);


    //叫3分直接当地主
    if(bet==3)
    {
        //设置角色
        player->setRole(GamePlayer::Lord);
        player->getNextPlayer()->setRole(GamePlayer::Farmer);
        player->getNextPlayer()->getNextPlayer()->setRole(GamePlayer::Farmer);

        /*暂停1秒钟后开始打牌*/
        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        emit TellGameProcess(PlayingHand);
        beginPlayHand();
        return;
    }


    BetList.insert(player,bet);

    if(player==m_DownPlayer) betDownOrder=BetList.size();
    else if(player==m_LeftPlayer) betLeftOrder=BetList.size();
    else if(player==m_RightPlayer) betRightOrder=BetList.size();

    if(BetList.size()==3)
    {

        int betDown=BetList.value(m_DownPlayer);
        int betLeft=BetList.value(m_LeftPlayer);
        int betRight=BetList.value(m_RightPlayer);

        //三个人叫分一样
        if((betDown==betLeft) && (betDown==betRight))
        {
            m_currentPlayer=getNextPlayer();
            QTime dieTime = QTime::currentTime().addMSecs(1000);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            emit TellGameProcess(PickingCard);
            return;
        }

        //叫分不一样,最大的为地主
        if(betDown>betLeft && betDown>betRight)
            m_currentPlayer=m_DownPlayer;
        else if(betLeft>betDown && betLeft>betRight)
            m_currentPlayer=m_LeftPlayer;
        else if(betRight>betDown && betRight>betLeft)
            m_currentPlayer=m_RightPlayer;

        else if(betLeft==betDown&&betLeft>betRight)
        {
            if(betLeftOrder<betDownOrder)
                m_currentPlayer=m_LeftPlayer;
            else
                m_currentPlayer=m_DownPlayer;
        }
        else if(betLeft==betRight && betLeft>betDown)
        {
            if(betRightOrder<betLeftOrder)
                m_currentPlayer=m_RightPlayer;
            else
                m_currentPlayer=m_LeftPlayer;
        }
        else if(betDown==betRight&&betDown>betLeft)
        {
            if(betDownOrder<betRightOrder)
                m_currentPlayer=m_DownPlayer;
            else
                m_currentPlayer=m_RightPlayer;
        }

        m_currentPlayer->setRole(GamePlayer::Lord);
        m_currentPlayer->getNextPlayer()->setRole(GamePlayer::Farmer);
        m_currentPlayer->getNextPlayer()->getNextPlayer()->setRole(GamePlayer::Farmer);

        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        emit TellGameProcess(PlayingHand);
        beginPlayHand();
        return;
    }

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    m_currentPlayer=player->getNextPlayer();
    emit TellPlayerStatus(m_currentPlayer,GamePlayer::waitingCallingLord);

    m_currentPlayer->beginCallingLord();
}

void GameProcess::PlayerPlayHand(GamePlayer *player, QList<Card> cards)
{
    if(!cards.isEmpty())
    {
        m_hitPlayer=player;
        m_hitCards=cards;
        emit TellHitPlayer(player,cards);
    }

    emit TellPlayerPlayHand(player,cards);

    if(player->getCards().isEmpty())                   //若玩家出牌后剩余牌组为空,则该玩家胜利
    {
        emit TellPlayerStatus(player,GamePlayer::winning); //设置胜利状态
        return;
    }

    /*出牌权移到下一玩家*/
    m_currentPlayer=player->getNextPlayer();
    emit TellPlayerStatus(m_currentPlayer,GamePlayer::waitingPlayingHand);//设置等待出牌状态
    m_currentPlayer->beginPlayingHand();    //下一位玩家出牌
}

void GameProcess::beginPlayHand()
{
    emit TellPlayerStatus(m_currentPlayer,GamePlayer::waitingPlayingHand);
    m_currentPlayer->beginPlayingHand();
}

QList<Card> GameProcess::getHitCards()
{
    return m_hitCards;
}

void GameProcess::InitCards()
{
    //m_allCards初始化
    for(int suit=Suit_Begin+1;suit<Suit_End;suit++)
    {
        for(int point=Card_3;point<Card_SJ;point++)
            m_allCards.append(Card((CardPoint)point,(CardSuit)suit));
    }

    m_allCards.append(Card(Card_SJ,Suit_Begin));
    m_allCards.append(Card(Card_BJ,Suit_Begin));

}

QList<Card> GameProcess::getAllCards()
{
    return m_allCards;
}

void GameProcess::Restart()
{

    m_hitPlayer=NULL;
    m_hitCards.clear();
    m_allCards.clear();
    BetList.clear();
    InitCards();
}

