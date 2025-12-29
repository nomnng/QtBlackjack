#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include "game/card.h"

#include <QLabel>
#include <functional>

class CardWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CardWidget(Card c, QWidget *parent = nullptr);
    void flip();
    bool isFaceUp();
    void animatedMove(int dstX, int dstY, std::function<void()> onEnd = nullptr);
    void animatedMoveAndFlip(int dstX, int dstY);

signals:

private:
    void updateCardImage();

    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 150;
    static constexpr int ANIMATION_DURATION = 200;

    Card card;

    bool frontVisible;
};

#endif // CARDWIDGET_H
