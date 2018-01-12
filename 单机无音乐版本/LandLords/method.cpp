#include "method.h"

Method::Method(GamePlayer* player,QList<Card> cards)
{
    m_player=player;
    m_cards=cards;
}

Method::~Method()
{}


int Method::CountOfPoint(QList<Card> cards,CardPoint point)
{
    int count=0;
    for(int i=0;i<cards.size();i++)
        if(cards[i].point==point)
            count++;
    return count;
}

QList<QList<Card> > Method::FindHand(Hand hand, bool beat)
{
    HandType handType = hand.getHandType();
    CardPoint basePoint = CardPoint(hand.getBasePoint());
    int extra = hand.getExtra();

    if (handType == Hand_Pass)
    {}
    else if (handType == Hand_Single)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card> findCards = FindSamePointCards(point, 1);
            if (!findCards.isEmpty())
            {
                findCardsArray.append(findCards);
            }
        }
        return findCardsArray;
    }
    else if (handType == Hand_Pair)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card> findCards = FindSamePointCards(point, 2);
            if (!findCards.isEmpty())
            {
                findCardsArray.append(findCards);
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card> findCards = FindSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray.append(findCards);
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple_Single)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card> findCards = FindSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray.append(findCards);
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QList<Card> remainCards = m_cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }
            //remainCards.Remove(findCardsArray);

            Method st(m_player, remainCards);
            QList<QList<Card> > oneCardsArray = st.FindHand(Hand(Hand_Single, Card_Begin, 0), false);
            if (!oneCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i] .append(oneCardsArray[0]);
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple_Pair)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card>  findCards = FindSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QList<Card>  remainCards = m_cards;
            for(int i=0;i<findCardsArray.size();i++)
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne(findCardsArray[i][j]);

            //            remainCards.Remove(findCardsArray);

            Method st(m_player, remainCards);
            QList<QList<Card> > pairCardsArray = st.FindHand(Hand(Hand_Pair, Card_Begin, 0), false);
            if (!pairCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i].append(pairCardsArray[0]);
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Plane)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QList<Card>  prevCards = FindSamePointCards(point, 3);
            QList<Card>  nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                findCardsArray.append(prevCards);
                findCardsArray.append(nextCards);
            }
        }
    }
    else if (handType == Hand_Plane_Two_Single)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QList<Card>  prevCards = FindSamePointCards(point, 3);
            QList<Card>  nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                QList<Card>  findCards;

                findCards.append(prevCards);
                findCards.append(nextCards);
                findCardsArray.append(findCards);
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QList<Card>  remainCards = m_cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }

            Method st(m_player, remainCards);
            QList<QList<Card> > oneCardsArray = st.FindHand(Hand(Hand_Single, Card_Begin, 0), false);
            if (oneCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    QList<Card>  oneCards;
                    oneCards.append(oneCardsArray[0]);
                    oneCards.append(oneCardsArray[1]);
                    findCardsArray[i] << oneCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Plane_Two_Pair)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QList<Card>  prevCards = FindSamePointCards(point, 3);
            QList<Card>  nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                QList<Card>  findCards;
                findCards << prevCards << nextCards;
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QList<Card>  remainCards = m_cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }

            Method st(m_player, remainCards);
            QList<QList<Card> > pairCardsArray = st.FindHand(Hand(Hand_Pair, Card_Begin, 0), false);
            if (pairCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    QList<Card>  pairCards;
                    pairCards << pairCardsArray[0] << pairCardsArray[1];
                    findCardsArray[i] << pairCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Seq_Pair)
    {
        if (beat)
        {
            QList<QList<Card> > findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_Q; point = CardPoint(point + 1))
            {
                bool seqPairFound = true;
                QList<Card>  seqPair;

                for (int i = 0; i < extra; i++)
                {
                    QList<Card>  cards = FindSamePointCards(CardPoint(point + i), 2);
                    if (cards.isEmpty() || (point + i >= Card_2))	// 连对中断，或顶到2了
                    {
                        seqPairFound = false;
                        seqPair.clear();
                        break;
                    }
                    else
                    {
                        seqPair << cards;
                    }
                }

                if (seqPairFound)
                {
                    findCardsArray << seqPair;
                    return findCardsArray;
                }
            }

            return findCardsArray;
        }
        else
        {
            QList<QList<Card> > findCardsArray;

            for (CardPoint point = Card_3; point <= Card_Q; point = CardPoint(point + 1))
            {
                QList<Card>  cards0 = FindSamePointCards(point, 2);
                QList<Card>  cards1 = FindSamePointCards(CardPoint(point + 1), 2);
                QList<Card>  cards2 = FindSamePointCards(CardPoint(point + 2), 2);

                if (cards0.isEmpty() || cards1.isEmpty() || cards2.isEmpty()) continue;

                QList<Card>  baseSeq;
                baseSeq << cards0 << cards1 << cards2;
                findCardsArray << baseSeq;

                int followed = 3;
                QList<Card>  alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    QList<Card>  followedCards = FindSamePointCards(followedPoint, 2);
                    if (followedCards.isEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        QList<Card>  newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Hand_Seq_Single)
    {
        if (beat)
        {
            QList<QList<Card> > findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_10; point = CardPoint(point + 1))
            {
                bool seqSingleFound = true;
                QList<Card>  seqSingle;

                for (int i = 0; i < extra; i++)
                {
                    QList<Card>  cards = FindSamePointCards(CardPoint(point + i), 1);
                    if (cards.isEmpty() || (point + extra >= Card_2))
                    {
                        seqSingleFound = false;
                        seqSingle.clear();
                        break;
                    }
                    else
                    {
                        seqSingle << cards;
                    }
                }

                if (seqSingleFound)
                {
                    findCardsArray << seqSingle;
                    return findCardsArray;
                }
            }
        }
        else
        {
            QList<QList<Card> > findCardsArray;

            for (CardPoint point = Card_3; point <= Card_10; point = CardPoint(point + 1))
            {
                QList<Card>  cards0 = FindSamePointCards(point, 1);
                QList<Card>  cards1 = FindSamePointCards(CardPoint(point + 1), 1);
                QList<Card>  cards2 = FindSamePointCards(CardPoint(point + 2), 1);
                QList<Card>  cards3 = FindSamePointCards(CardPoint(point + 3), 1);
                QList<Card>  cards4 = FindSamePointCards(CardPoint(point + 4), 1);

                if (cards0.isEmpty() || cards1.isEmpty() || cards2.isEmpty()
                        || cards3.isEmpty() || cards4.isEmpty())
                {
                    continue;
                }

                QList<Card>  baseSeq;
                baseSeq << cards0 << cards1 << cards2 << cards3 << cards4;
                findCardsArray << baseSeq;

                int followed = 5;
                QList<Card>  alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    QList<Card>  followedCards = FindSamePointCards(followedPoint, 1);
                    if (followedCards.isEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        QList<Card>  newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Hand_Bomb)
    {
        QList<QList<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QList<Card>  findCards = FindSamePointCards(point, 4);
            if (!findCards.isEmpty())
            {
                findCardsArray << findCards;
            }
        }

        return findCardsArray;
    }

    QList<QList<Card> > c;
    c.clear();
    return c;
}

QList<Card> Method::FindSamePointCards(CardPoint point, int count)
{
    if (point == Card_SJ || point == Card_BJ)
    {
        if (count > 1) return QList<Card>();

        Card oneCard;
        oneCard.point = point;
        oneCard.suit = Suit_Begin;
        if (m_cards.contains(oneCard))
        {
            QList<Card> cards;
            cards.append(oneCard);
            return cards;
        }

        return QList<Card>();
    }

    QList<Card> findCards;
    int findCount = 0;
    for (int suit = Suit_Begin + 1; suit < Suit_End; suit++)
    {
        Card oneCard;
        oneCard.point = point;
        oneCard.suit = (CardSuit)suit;

        if (m_cards.contains(oneCard))
        {
            findCount++;
            findCards << oneCard;

            if (findCount == count)
            {
                return findCards;
            }
        }
    }

    return QList<Card>();

}

QList<QList<Card> > Method::FindCardsByCount(int count)
{
    QList<QList<Card> > cardsList;
    if (count < 1 || count > 4)     return cardsList;   //count不合理

    for(int point=Card_3;point<Card_End;point++)
    {
        if(CountOfPoint(m_cards,(CardPoint)point)==count)
        {
            QList<Card> cards=FindSamePointCards((CardPoint)point,count);
            cardsList.append(cards);

        }
    }
    return cardsList;
}

QList<Card> Method::GetRangeCards(CardPoint beginPoint, CardPoint endPoint)
{

    QList<Card> rangeCards;

    for (CardPoint point = beginPoint; point <= endPoint; point=(CardPoint)(point+1))
    {
        int count = CountOfPoint(m_cards,point);

        QList<Card> cards ;
        if(count!=0)
        {
            FindSamePointCards(point, count);
            rangeCards<<cards;
        }
    }

    return rangeCards;
}

QList<Card> Method::GetFirstSeqSingleRange()
{
    int seqCount = 0;
    CardPoint beginPoint=Card_Begin, endPoint=Card_Begin;

    for(CardPoint point=Card_3;point<=Card_10;point=(CardPoint)(point+1))
    {
        while(true)
        {
            CardPoint findPoint = CardPoint(point+seqCount);
            QList<Card> oneCard = FindSamePointCards(findPoint,1);
            if(oneCard.isEmpty() || findPoint>Card_A)
            {
                if(seqCount>=5)
                {
                    endPoint+ CardPoint(point+seqCount-1);
                    return GetRangeCards(point,endPoint);
                }
                point=findPoint;
                beginPoint = endPoint = Card_Begin;
                seqCount=0;
                break;
            }
            else
            {
                if (seqCount == 0)
                {
                    beginPoint = point;
                }

                seqCount++;
            }
        }
    }

    QList<Card> cards;
    cards.clear();
    return cards;
}

void Method::PickSeqSingles(QList<QList<QList<Card>  > >& allSeqRecord, const QList<QList<Card> >& seqInherited, QList<Card> cards)
{
    QList<QList<Card> > allSeqScheme = Method(m_player, cards).FindHand(Hand(Hand_Seq_Single, Card_Begin, 0), false);
    if (allSeqScheme.isEmpty())
    {
        allSeqRecord << seqInherited;
    }
    else
    {
        QList<Card> savedCards = cards;
        for (int i = 0; i < allSeqScheme.size(); i++)
        {
            QList<Card> aScheme = allSeqScheme[i];
            QList<Card> leftCards = savedCards;

            for(int j=0;j<aScheme.size();j++)
                leftCards.removeOne(aScheme[j]);

            QList<QList<Card> > seqArray = seqInherited;
            seqArray.append(aScheme);
            PickSeqSingles(allSeqRecord, seqArray, leftCards);
        }
    }
}

QList<QList<Card> > Method::PickOptimalSeqSingles()
{
    QList<QList<QList<Card> > > seqRecord;
    QList<QList<Card> > seqInherited;
    Method(m_player, m_cards).PickSeqSingles(seqRecord, seqInherited, m_cards);
    if (seqRecord.isEmpty())
    {
        return QList<QList<Card> >();
    }

    QMap<int, int> seqMarks;
    for (int i = 0; i < seqRecord.size(); i++)
    {
        QList<Card> backupCards = m_cards;
        QList<QList<Card> > seqArray = seqRecord[i];
        for(int l=0;l<seqArray.size();l++)
        {
            for(int j=0;j<seqArray[l].size();j++)
            {
                backupCards.removeOne(seqArray[l][j]);
            }
        }

        QList<QList<Card> > singleArray = Method(m_player, backupCards).FindCardsByCount(1);

        QList<Card> cardList;
        for (int j = 0; j < singleArray.size(); j++)
        {
            for(int i=0;i<singleArray[j].size();i++)
                cardList<<singleArray[j][i];

        }

        int mark = 0;
        for (int j = 0; j < cardList.size(); j++)
        {
            mark += cardList[j].point + 15;
        }
        seqMarks.insert(i, mark);
    }

    int index = 0;
    int compMark = 1000000;
    QMap<int, int>::ConstIterator it = seqMarks.constBegin();
    for (; it != seqMarks.constEnd(); it++)
    {
        if (it.value() < compMark)
        {
            compMark = it.value();
            index = it.key();
        }
    }

    return seqRecord[index];
}

QList<Card> Method::PlayFirst()
{
    Hand hand(m_cards);
    if (hand.getHandType() != Hand_Unknown)		// 只剩一手牌，直接出完
    {
        return m_cards;
    }


    QList<Card>  seqSingleRange = GetFirstSeqSingleRange();
    if (!seqSingleRange.isEmpty())
    {
        QList<Card>  left = seqSingleRange;

        //清除炸弹和三个
        QList<QList<Card> > cards4=Method(m_player,left).FindCardsByCount(4);

        for(int i=0;i<cards4.size();i++)
            for(int j=0;j<cards4[i].size();j++)
                left.removeOne(cards4[i][j]);

        QList<QList<Card> > cards3=Method(m_player,left).FindCardsByCount(3);

        for(int i=0;i<cards3.size();i++)
            for(int j=0;j<cards3[i].size();j++)
                left.removeOne(cards3[i][j]);

        //     left.Remove(Method(m_player, left).FindCardsByCount(4));
        //     left.Remove(Strategy(m_player, left).FindCardsByCount(3));



        QList<QList<Card> > optimalSeq = Method(m_player, left).PickOptimalSeqSingles();
        if (!optimalSeq.isEmpty())
        {
            int oriSingleCount = Method(m_player, left).FindCardsByCount(1).size();
            //left.Remove(optimalSeq);

            for(int i=0;i<optimalSeq.size();i++)
                for(int j=0;j<optimalSeq[i].size();j++)
                    left.removeOne(optimalSeq[i][j]);

            int leftSingleCount = Method(m_player, left).FindCardsByCount(1).size();

            if (leftSingleCount < oriSingleCount)
            {
                return optimalSeq[0];
            }
        }
    }

    bool hasPlane, hasTriple, hasSeqPair;
    hasPlane = hasTriple = hasSeqPair = false;
    QList<Card>  leftCards = m_cards;

    QList<QList<Card> > bombArray = Method(m_player, leftCards).FindHand(Hand(Hand_Bomb, Card_Begin, 0), false);
    //leftCards.Remove(bombArray);

    for(int i=0;i<bombArray.size();i++)
        for(int j=0;j<bombArray[i].size();j++)
            leftCards.removeOne(bombArray[i][j]);

    QList<QList<Card> > planeArray = Method(m_player, leftCards).FindHand(Hand(Hand_Plane, Card_Begin, 0), false);
    if (!planeArray.isEmpty())
    {
        hasPlane = true;
        for(int i=0;i<planeArray.size();i++)
            for(int j=0;j<planeArray[i].size();j++)
                leftCards.removeOne(planeArray[i][j]);

        //leftCards.Remove(planeArray);
    }

    QList<QList<Card> > tripleArray = Method(m_player, leftCards).FindHand(Hand(Hand_Triple, Card_Begin, 0), false);
    if (!tripleArray.isEmpty())
    {
        hasTriple = true;
        for(int i=0;i<tripleArray.size();i++)
            for(int j=0;j<tripleArray[i].size();j++)
                leftCards.removeOne(tripleArray[i][j]);

        //        leftCards.Remove(tripleArray);
    }

    QList<QList<Card> > seqPairArray = Method(m_player, leftCards).FindHand(Hand(Hand_Seq_Pair, Card_Begin, 0), false);
    if (!seqPairArray.isEmpty())
    {
        hasSeqPair = true;
        for(int i=0;i<seqPairArray.size();i++)
            for(int j=0;j<seqPairArray[i].size();j++)
                leftCards.removeOne(seqPairArray[i][j]);
        //leftCards.Remove(seqPairArray);
    }

    if (hasPlane)
    {
        bool twoPairFound = false;
        QList<QList<Card> > pairArray;
        for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
        {
            QList<Card>  pair = Method(m_player, leftCards).FindSamePointCards(point, 2);
            if (!pair.isEmpty())
            {
                pairArray << pair;
                if (pairArray.size() == 2)
                {
                    twoPairFound = true;
                    break;
                }
            }
        }

        if (twoPairFound)
        {
            QList<Card>  playCards = planeArray[0];
            for(int i=0;i<pairArray.size();i++)
                for(int j=0;j<pairArray[i].size();j++)
                    playCards.append(pairArray[i][j]);
            //            playCards.Add(pairArray);

            return playCards;
        }
        else
        {
            bool twoSingleFound = false;
            QList<QList<Card> > singleArray;
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                if (CountOfPoint(leftCards,point)==1) //(leftCards.PointCount(point) == 1)
                {
                    QList<Card>  single = Method(m_player, leftCards).FindSamePointCards(point, 1);
                    if (!single.isEmpty())
                    {
                        singleArray << single;
                        if (singleArray.size() == 2)
                        {
                            twoSingleFound = true;
                            break;
                        }
                    }
                }
            }

            if (twoSingleFound)
            {
                QList<Card>  playCards = planeArray[0];
                for(int i=0;i<singleArray.size();i++)
                    for(int j=0;j<singleArray[i].size();j++)
                        playCards.append(singleArray[i][j]);
                // playCards.Add(singleArray);

                return playCards;
            }
            else
            {
                return planeArray[0];
            }
        }
    }

    if (hasTriple)
    {
        if (Hand(tripleArray[0]).getBasePoint() < Card_A)
        {
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                int pointCount = CountOfPoint(leftCards,point);//leftCards.PointCount(point);
                if (pointCount == 1)
                {
                    QList<Card>  single = Method(m_player, leftCards).FindSamePointCards(point, 1);
                    if (!single.isEmpty())
                    {
                        QList<Card>  playCards = tripleArray[0];
                        //playCards.Add(single);

                        for(int i=0;i<single.size();i++)
                            playCards.append(single[i]);

                        return playCards;
                    }
                }
                else if (pointCount == 2)
                {
                    QList<Card>  pair = Method(m_player, leftCards).FindSamePointCards(point, 2);
                    if (!pair.isEmpty())
                    {
                        QList<Card>  playCards = tripleArray[0];
                        //                        playCards.Add(pair);

                        for(int i=0;i<pair.size();i++)
                            playCards.append(pair[i]);
                        return playCards;
                    }
                }

            }

            return tripleArray[0];		// 找不到合适的带牌，直接出3个
        }
    }

    if (hasSeqPair)		// 打出最长的连对
    {
        QList<Card>  maxSeqPair;
        for (int i = 0; i < seqPairArray.size(); i++)
        {
            if (seqPairArray[i].size() > maxSeqPair.size())
            {
                maxSeqPair = seqPairArray[i];
            }
        }

        return maxSeqPair;
    }

    GamePlayer* nextPlayer = m_player->getNextPlayer();

    if (m_player->getRole() != nextPlayer->getRole() &&
            nextPlayer->getCards().size() == 1)
    {
        for (CardPoint point = CardPoint(Card_End - 1); point >= Card_3; point = CardPoint(point - 1))
        {
            int pointCount = CountOfPoint(leftCards,point);//leftCards.PointCount(point);
            if (pointCount == 1)
            {
                QList<Card>  single = Method(m_player, leftCards).FindSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                QList<Card>  pair = Method(m_player, leftCards).FindSamePointCards(point, 2);
                return pair;
            }
        }
    }
    else
    {
        for (CardPoint point = Card_3; point < Card_End; point = CardPoint(point + 1))
        {
            int pointCount = CountOfPoint(leftCards,point);//leftCards.PointCount(point);
            if (pointCount == 1)
            {
                QList<Card>  single = Method(m_player, leftCards).FindSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                QList<Card>  pair = Method(m_player, leftCards).FindSamePointCards(point, 2);
                return pair;
            }
        }
    }

    return QList<Card> ();
}

QList<Card> Method::PlayBeatHand(Hand hand)
{
    // 先固定住最优顺子，从余下牌中打出
    QList<Card>  left = m_cards;
    QList<QList<Card> > cardlll=Method(m_player,left).PickOptimalSeqSingles();
    for(int i=0;i<cardlll.size();i++)
        for(int j=0;j<cardlll[i].size();j++ )
            left.removeOne(cardlll[i][j]);

    //left.Remove(Method(m_player, left).PickOptimalSeqSingles());

    if (hand.getHandType() == Hand_Single)	// 如果压单牌，尽量从单张牌中挑
    {
        QList<QList<Card> > singleArray = Method(m_player, left).FindCardsByCount(1);
        for (int i = 0; i < singleArray.size(); i++)
        {
            if (Hand(singleArray[i]).Defeat(hand))
            {
                return singleArray[i];
            }
        }
    }
    else if (hand.getHandType() == Hand_Pair)	// 如果压双牌，尽量从双牌中挑
    {
        QList<QList<Card> > pairArray = Method(m_player, left).FindCardsByCount(2);
        for (int i = 0; i < pairArray.size(); i++)
        {
            if (Hand(pairArray[i]).Defeat(hand))
            {
                return pairArray[i];
            }
        }
    }

    GamePlayer* nextPlayer = m_player->getNextPlayer();
    QList<QList<Card> > beatCardsArray = Method(m_player, left).FindHand(hand, true);
    if (!beatCardsArray.isEmpty())
    {
        if (m_player->getRole() != nextPlayer->getRole() &&
                nextPlayer->getCards().size() <= 2)
        {
            return beatCardsArray.back();
        }
        else
        {
            return beatCardsArray.front();
        }
    }
    else	// 余下牌没法打时，只好从顺子中挑牌
    {
        beatCardsArray = Method(m_player, m_cards).FindHand(hand, true);
        if (!beatCardsArray.isEmpty())
        {
            if (m_player->getRole() != nextPlayer->getRole() &&
                    nextPlayer->getCards().size() <= 2)
            {
                return beatCardsArray.back();
            }
            else
            {
                return beatCardsArray.front();
            }
        }
    }

    // 对家剩牌小于3张，有炸则炸
    GamePlayer* hitPlayer = m_player->getHitPlayer();
    if (m_player->getRole() != hitPlayer->getRole())
    {
        if (hitPlayer->getCards().size() <= 3)
        {
            QList<QList<Card> > bombs = FindCardsByCount(4);
            if (!bombs.isEmpty())
            {
                return bombs[0];
            }
        }
    }

    QList<Card>  empty;
    empty.clear();
    return empty;
}

bool Method::WhetherToBeat(QList<Card> &myCards)
{
    if (myCards.isEmpty()) return true;

    GamePlayer* hitPlayer = m_player->getHitPlayer();
    QList<Card> hitCards = m_player->getHitCards();

    if (m_player->getRole() == hitPlayer->getRole())		// punch的是同家
    {
        QList<Card> left = m_cards;
        for(int i=0;i<myCards.size();i++)
            left.removeOne(myCards[i]);

        if (Hand(left).getHandType() != Hand_Unknown) return true;

        CardPoint basePoint = CardPoint(Hand(myCards).getBasePoint());
        if (basePoint == Card_2 || basePoint == Card_SJ || basePoint == Card_BJ)
        {
            return false;
        }
    }
    else	// punch的是对家
    {
        Hand myHand(myCards);

        if ( (myHand.getHandType() == Hand_Triple_Single || myHand.getHandType() == Hand_Triple_Pair) &&
             (myHand.getBasePoint() == Card_2) )	// 三个2就不打出去了
        {
            return false;
        }

        if (myHand.getHandType() == Hand_Pair && myHand.getBasePoint() == Card_2 &&
                hitPlayer->getCards().size() >= 10 && m_player->getCards().size() >= 5)
        {
            return false;
        }
    }

    return true;
}

QList<Card> Method::MakeDecision()
{
    GamePlayer* hitPlayer = m_player->getHitPlayer();
    QList<Card> hitCards = m_player->getHitCards();

    if (hitPlayer == m_player || hitPlayer == NULL)
    {
        return PlayFirst();              //主动出牌
    }
    else
    {
        Hand hitHand(hitCards);
        QList<Card> beatCards = PlayBeatHand(hitHand);
        bool shouldBeat = WhetherToBeat(beatCards);
        if (shouldBeat)
        {
            return beatCards;
        }
        else
        {
            return QList<Card> ();
        }
    }
    return QList<Card>();
}
