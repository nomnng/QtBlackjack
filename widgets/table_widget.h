#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include "card_widget.h"

#include <QWidget>
#include <QLabel>

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);
    CardWidget* createCardWidget(Card card);
    void tossCardToDealer(CardWidget* cardWidget, bool flip = false);
    void tossCardToPlayer(CardWidget* cardWidget, bool flip = false);
    void tossLastCardToPlayer();
    void tossLastCardToDealer();
    void updatePlayerCardValue(int value);
    void updateDealerCardValue(int value);
    void flipDealerHiddenCard();
    void setInfoLabelText(const QString& text);

signals:

private:
    QLabel* playerCardValueLabel;
    QLabel* dealerCardValueLabel;
    CardWidget* topDeckCard;

    QList<CardWidget*> dealerCardWidgets;
    QList<CardWidget*> playerCardWidgets;
    CardWidget* nextCard;

};

#endif // TABLEWIDGET_H
