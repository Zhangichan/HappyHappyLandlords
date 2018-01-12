#include "card.h"

//根据 点数 和 花色 构造
Card::Card(CardPoint p, CardSuit s)
{
    point=p;
    suit=s;
}

//根据 [1,54]的整数构造
Card::Card(int number)
{
    if(number>=1 && number<=54){
        point=CardPoint((number-1)/4+1);
        if(number==53||number==54)
            suit=Suit_Begin;
        else
            suit=CardSuit((number-1)%4+1);
    }
}

//设置点数
void Card::setPoint(CardPoint p)
{
    point=p;
    return;
}

//获取点数
CardPoint Card::getPoint()
{
    return point;
}

//设置花色
void Card::setSuit(CardSuit s)
{
    suit=s;
    return;
}

//获取花色
CardSuit Card::getSuit()
{
    return suit;
}
