#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QObject>

#include "card.h"

class Blackjack : public QObject
{
    Q_OBJECT
public:
    explicit Blackjack(QObject *parent = nullptr);

signals:

private:
    void shuffleDeck();
    void resetDeck();
    Card getDealerCard();
    Card requestNewCard();
    Card stand();

    QList<Card> deck;

};

#endif // BLACKJACK_H
