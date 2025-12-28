#include "card.h"

Card::Rank& operator++(Card::Rank& r) {
    r = static_cast<Card::Rank>(static_cast<int>(r) + 1);
    return r;
}

Card::Rank operator++(Card::Rank& r, int) {
    Card::Rank currentValue = r;
    ++r;
    return currentValue;
}

Card::Suit& operator++(Card::Suit& s) {
    s = static_cast<Card::Suit>(static_cast<int>(s) + 1);
    return s;
}

Card::Suit operator++(Card::Suit& s, int) {
    Card::Suit currentValue = s;
    ++s;
    return currentValue;
}
