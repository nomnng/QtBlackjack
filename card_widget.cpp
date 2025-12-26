#include "card_widget.h"

CardWidget::CardWidget(Card::Rank r, Card::Suit s, QWidget *parent)
    : QLabel{parent}, rank(r), suit(s)
{

}
