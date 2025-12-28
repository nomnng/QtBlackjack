#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "game/blackjack.h"

#include <QWidget>
#include <QGridLayout>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

public slots:
    void startGame(int bet);

signals:

private:
    void showBetSelectionPopup();

    QGridLayout* layout;

    Blackjack blackjack;

    static constexpr int BET_STEP = 25;
    int currentBet;
    int bankroll = 500;

};

#endif // GAMEWIDGET_H
