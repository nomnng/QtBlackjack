#ifndef CARD_H
#define CARD_H

struct Card {
    enum class Suit {
        Clubs = 1,
        Diamonds,
        Hearts,
        Spades,

        Start = Clubs,
        End = Spades
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
        Ace,

        Start = Two,
        End = Ace
    };


    Rank rank;
    Suit suit;
};

Card::Rank& operator++(Card::Rank& r);
Card::Rank operator++(Card::Rank& r, int);
Card::Suit& operator++(Card::Suit& s);
Card::Suit operator++(Card::Suit& s, int);


#endif // CARD_H
