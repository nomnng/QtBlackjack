#ifndef CARD_H
#define CARD_H

namespace Card {
    enum class Suit {
        Clubs = 1,
        Diamonds,
        Hearts,
        Spades
    };

    enum class Rank {
        Two = 1,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    };
};

#endif // CARD_H
