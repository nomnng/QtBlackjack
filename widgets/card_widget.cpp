#include "card_widget.h"
#include "utils/card_image_provider.h"

#include <QPropertyAnimation>

CardWidget::CardWidget(Card c, QWidget *parent)
    : QLabel{parent}, card(c), frontVisible(false)
{
    setScaledContents(true);
    setAttribute(Qt::WA_TranslucentBackground); // needed to properly draw transparent parts
    resize(WIDTH, HEIGHT);
    updateCardImage();

    connect(&CardImageProvider::instance(), &CardImageProvider::cardFrontChanged, this, [this](){
        updateCardImage();
    });

    connect(&CardImageProvider::instance(), &CardImageProvider::cardBackChanged, this, [this](){
        updateCardImage();
    });
}

void CardWidget::flip()
{
    QRect startValue(x(), y(), WIDTH, HEIGHT);
    QRect endValue = startValue;
    endValue.setWidth(0);
    endValue.setX(endValue.x() + WIDTH); // adding full width instead of half to compensate for shrinking width

    QPropertyAnimation *firstAnimation = new QPropertyAnimation(this, "geometry");
    firstAnimation->setDuration(ANIMATION_DURATION / 2);
    firstAnimation->setStartValue(startValue);
    firstAnimation->setEndValue(endValue);
    firstAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(firstAnimation, &QPropertyAnimation::finished, this, [this, startValue, endValue]() {
        QPropertyAnimation *secondAnimation = new QPropertyAnimation(this, "geometry");
        secondAnimation->setDuration(ANIMATION_DURATION / 2);
        secondAnimation->setStartValue(endValue);
        secondAnimation->setEndValue(startValue);
        secondAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        frontVisible = !frontVisible;
        updateCardImage();
    });
}

bool CardWidget::isFaceUp()
{
    return frontVisible;
}

void CardWidget::animatedMove(int dstX, int dstY, std::function<void()> onEnd)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(ANIMATION_DURATION);
    animation->setStartValue(pos());
    animation->setEndValue(QPoint(dstX, dstY));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    if (onEnd) {
        connect(animation, &QPropertyAnimation::finished, this, onEnd);
    }
}

void CardWidget::animatedMoveAndFlip(int dstX, int dstY)
{
    animatedMove(dstX, dstY, [this](){
        flip();
    });
}


void CardWidget::updateCardImage()
{
    QPixmap pixmap = frontVisible ? CardImageProvider::getCardImage(card) : CardImageProvider::getBackImage();
    setPixmap(pixmap);
}
