#ifndef METHOD_H
#define METHOD_H


#include <QWidget>
#include "gameplayer.h"
#include "hand.h"
#include <QMap>

class Method
{
public:
    Method(GamePlayer* player, QList<Card> cards);
    ~Method();

    int CountOfPoint(QList<Card> cards, CardPoint point);
    QList<Card> MakeDecision();

    QList<Card> FindSamePointCards(CardPoint point, int count);// 找出count张点数为point的牌
    QList<QList<Card> > FindCardsByCount(int count);// 找出所有点数相同张数为count的牌组
    QList<Card> GetRangeCards(CardPoint beginPoint, CardPoint endPoint);// 找出所有在范围内的牌
    QList<Card> GetFirstSeqSingleRange();               // 找到能构成顺子的最小起点牌的牌组

    // 在cards中挑出一个顺子，seqInherited记录逐步拨除顺子，allSeqRecord记录所能分离出的顺子
    void PickSeqSingles(QList<QList<QList<Card> > >& allSeqRecord, const QList<QList<Card> >& seqInherited, QList<Card> cards);
    QList<QList<Card> > PickOptimalSeqSingles();

    // 按牌型找到若干手牌，beat为true表示要大过hand, beat为false表示不要求大过hand
    QList<QList<Card> >  FindHand(Hand hand, bool beat);

    QList<Card> PlayFirst();// 主动出牌
    QList<Card> PlayBeatHand(Hand hand);// 大过指定牌型
    bool WhetherToBeat(QList<Card> &myCards);// 能大过时，判断是打还是放行

protected:
    GamePlayer* m_player;
    QList<Card> m_cards;
};

#endif // METHOD_H
