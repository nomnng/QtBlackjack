#include "blackjack.h"

#include <algorithm>
#include <random>

Blackjack::Blackjack(QObject *parent)
    : QObject{parent}
{
    resetDeck();
}

void Blackjack::startGame()
{
    shuffleDeck();
    dealerCards.clear();
    playerCards.clear();

    for (int i = 0; i < 2; i++) {
        dealerCards.append(takeCard());
        playerCards.append(takeCard());
    }
}

const QList<Card> &Blackjack::getDealerCards()
{
    return dealerCards;
}

const QList<Card> &Blackjack::getPlayerCards()
{
    return playerCards;
}

Card Blackjack::getNextCard()
{
    return deck[cardsTaken];
}

int Blackjack::countPlayerCards()
{
    return countCards(playerCards);
}

int Blackjack::countDealerCards()
{
    return countCards(dealerCards);
}

Blackjack::GameStatus Blackjack::playerHit()
{
    playerCards.append(takeCard());
    if (countPlayerCards() > 21) {
        return GameStatus::DealerWon;
    }
    return GameStatus::InProgress;
}

Blackjack::GameStatus Blackjack::dealerHit()
{
    dealerCards.append(takeCard());
    if (!dealerIsDone()) {
        return GameStatus::InProgress;
    }

    return getGameResult();
}

bool Blackjack::dealerIsDone()
{
    return countDealerCards() > 16;
}

Blackjack::GameStatus Blackjack::getGameResult()
{
    int dealerCardValue = countDealerCards();
    int playerCardValue = countPlayerCards();

    if (dealerCardValue == playerCardValue) {
        return GameStatus::Draw;
    } else if (playerCardValue > 21) {
        return GameStatus::DealerWon;
    } else if (dealerCardValue > 21) {
        return GameStatus::PlayerWon;
    } else if (playerCardValue > dealerCardValue) {
        return GameStatus::PlayerWon;
    }

    return GameStatus::DealerWon;
}

void Blackjack::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(deck.begin(), deck.end(), rng);
}

void Blackjack::resetDeck()
{
    cardsTaken = 0;
    deck.clear();
    for (Card::Rank r = Card::Rank::Start; r <= Card::Rank::End; r++) {
        for (Card::Suit s = Card::Suit::Start; s <= Card::Suit::End; s++) {
            deck.append(Card{r, s});
        }
    }
}

Card Blackjack::takeCard()
{
    return deck[cardsTaken++];
}

int Blackjack::getCardValue(Card card)
{
    switch (card.rank) {
        case Card::Rank::Two: return 2;
        case Card::Rank::Three: return 3;
        case Card::Rank::Four: return 4;
        case Card::Rank::Five: return 5;
        case Card::Rank::Six: return 6;
        case Card::Rank::Seven: return 7;
        case Card::Rank::Eight: return 8;
        case Card::Rank::Nine: return 9;
        case Card::Rank::Ten: return 10;
        case Card::Rank::Jack: return 10;
        case Card::Rank::Queen: return 10;
        case Card::Rank::King: return 10;
        case Card::Rank::Ace: return 11;
    }
}

int Blackjack::countCards(const QList<Card> &cards)
{
    int result = 0;
    int aceCount = 0;
    for (Card card: cards) {
        if (card.rank == Card::Rank::Ace) {
            aceCount++;
            continue;
        }
        result += getCardValue(card);
    }

    if (aceCount > 0) {
        result += aceCount;
        if ((result + 10) <= 21) {
            result += 10;
        }
    }

    return result;
}
