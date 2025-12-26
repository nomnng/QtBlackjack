#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include "card.h"

#include <QLabel>

class CardWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CardWidget(Card::Rank r, Card::Suit s, QWidget *parent = nullptr);

signals:

private:
    Card::Rank rank;
    Card::Suit suit;
};

#endif // CARDWIDGET_H
