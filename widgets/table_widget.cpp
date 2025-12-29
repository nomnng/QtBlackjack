#include "table_widget.h"

TableWidget::TableWidget(QWidget *parent)
    : QWidget{parent}, dealerCardValueLabel(new QLabel(this)), playerCardValueLabel(new QLabel(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #274; font-size: 24px; color: white;");

    dealerCardValueLabel->setGeometry(200, 80, 100, 30);
    playerCardValueLabel->setGeometry(200, 350, 100, 30);
}

CardWidget *TableWidget::createCardWidget(Card card)
{
    int deckX = width() * 0.85;
    int deckY = height() * 0.35;

    CardWidget* cardWidget = new CardWidget(card, this);
    cardWidget->show();
    cardWidget->move(deckX, deckY);

    topDeckCard = cardWidget;

    return cardWidget;
}

void TableWidget::tossCardToDealer(CardWidget *cardWidget, bool flip)
{
    int x = width() * 0.35 + 30 * dealerCardWidgets.size();
    int y = height() * 0.05 + 5 * dealerCardWidgets.size();
    if (flip) {
        cardWidget->animatedMoveAndFlip(x, y);
    } else {
        cardWidget->animatedMove(x, y);
    }
    dealerCardWidgets.append(cardWidget);
}

void TableWidget::tossCardToPlayer(CardWidget *cardWidget, bool flip)
{
    int x = width() * 0.35 + 30 * playerCardWidgets.size();
    int y = height() * 0.6 + 5 * playerCardWidgets.size();
    if (flip) {
        cardWidget->animatedMoveAndFlip(x, y);
    } else {
        cardWidget->animatedMove(x, y);
    }
    playerCardWidgets.append(cardWidget);
}

void TableWidget::tossLastCardToPlayer() {
    tossCardToPlayer(topDeckCard, true);
    topDeckCard = nullptr;
}

void TableWidget::tossLastCardToDealer() {
    tossCardToDealer(topDeckCard, true);
    topDeckCard = nullptr;
}

void TableWidget::updatePlayerCardValue(int value)
{
    playerCardValueLabel->setText(QString::number(value));
}

void TableWidget::updateDealerCardValue(int value)
{
    dealerCardValueLabel->setText(QString::number(value));
}

void TableWidget::flipDealerHiddenCard()
{
    for (CardWidget* cardWidget: dealerCardWidgets) {
        if (!cardWidget->isFaceUp()) {
            cardWidget->flip();
        }
    }
}

