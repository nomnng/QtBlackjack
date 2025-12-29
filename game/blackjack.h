#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QObject>

#include "card.h"

class Blackjack : public QObject
{
    Q_OBJECT
public:
    enum class GameStatus {
        InProgress = 1,
        PlayerWon,
        DealerWon,
        Draw
    };

    explicit Blackjack(QObject *parent = nullptr);
    void startGame();
    const QList<Card>& getDealerCards();
    const QList<Card>& getPlayerCards();
    Card getNextCard();
    int countPlayerCards();
    int countDealerCards();
    GameStatus playerHit();
    GameStatus dealerHit();
    bool dealerIsDone();
    GameStatus getGameResult();

signals:

private:
    void shuffleDeck();
    void resetDeck();
    Card getDealerCard();
    Card takeCard();
    Card stand();
    int getCardValue(Card card);
    int countCards(const QList<Card>& cards);

    QList<Card> deck;
    QList<Card> dealerCards;
    QList<Card> playerCards;
    int cardsTaken;

};

#endif // BLACKJACK_H
