#include "card_widget.h"
#include "card_image_provider.h"

#include <QPropertyAnimation>

CardWidget::CardWidget(Card::Rank r, Card::Suit s, QWidget *parent)
    : QLabel{parent}, rank(r), suit(s), frontVisible(false)
{
    setScaledContents(true);
    setAttribute(Qt::WA_TranslucentBackground); // needed to properly draw transparent parts
    resize(WIDTH, HEIGHT);
    updateCardImage();
}

void CardWidget::flip()
{
    QRect startValue(x(), y(), WIDTH, HEIGHT);
    QRect endValue = startValue;
    endValue.setWidth(0);
    endValue.setX(endValue.x() + WIDTH); // adding full width instead of half to compensate for shrinking width

    QPropertyAnimation *firstAnimation = new QPropertyAnimation(this, "geometry");
    firstAnimation->setDuration(ANIMATION_DURATION);
    firstAnimation->setStartValue(startValue);
    firstAnimation->setEndValue(endValue);
    firstAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(firstAnimation, &QPropertyAnimation::finished, this, [this, startValue, endValue]() {
        QPropertyAnimation *secondAnimation = new QPropertyAnimation(this, "geometry");
        secondAnimation->setDuration(ANIMATION_DURATION);
        secondAnimation->setStartValue(endValue);
        secondAnimation->setEndValue(startValue);
        secondAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        frontVisible = !frontVisible;
        updateCardImage();
    });
}

void CardWidget::animatedMove(int dstX, int dstY)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(ANIMATION_DURATION);
    animation->setStartValue(pos());
    animation->setEndValue(QPoint(dstX, dstY));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CardWidget::updateCardImage()
{
    QPixmap pixmap = frontVisible ? CardImageProvider::getCardImage(rank, suit) : CardImageProvider::getBackImage();
    setPixmap(pixmap);
}
