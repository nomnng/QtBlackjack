#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include "card.h"

#include <QLabel>

class CardWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CardWidget(Card::Rank r, Card::Suit s, QWidget *parent = nullptr);
    void flip();

signals:

private:
    void updateCardImage();

    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 300;
    static constexpr int ANIMATION_DURATION = 300;

    Card::Rank rank;
    Card::Suit suit;

    bool frontVisible;
};

#endif // CARDWIDGET_H
