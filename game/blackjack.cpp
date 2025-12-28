#include "blackjack.h"

#include <algorithm>
#include <random>

Blackjack::Blackjack(QObject *parent)
    : QObject{parent}
{
    resetDeck();
    shuffleDeck();
}

void Blackjack::shuffleDeck()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(deck.begin(), deck.end(), rng);
}

void Blackjack::resetDeck()
{
    deck.clear();
    for (Card::Rank r = Card::Rank::Start; r <= Card::Rank::End; r++) {
        for (Card::Suit s = Card::Suit::Start; s <= Card::Suit::End; s++) {
            deck.append(Card{r, s});
        }
    }
}
