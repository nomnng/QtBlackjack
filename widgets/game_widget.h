#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "game/blackjack.h"
#include "control_buttons_widget.h"
#include "table_widget.h"

#include <QWidget>
#include <QGridLayout>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

public slots:
    void setBet(int bet);

signals:

private:
    void showBetSelectionPopup();
    void startNewGame();
    void dealStartCards();
    void updatePlayerCardValue();
    void updateDealerCardValue();
    void hitClicked();
    void standClicked();
    void endRound();
    void dealerHit();
    void openSettingsPopup();

    QGridLayout* layout;
    ControlButtonsWidget* controlButtonsWidget;
    TableWidget* tableWidget;

    Blackjack* blackjack;

    static constexpr int BET_STEP = 25;
    static constexpr int START_BANKROLL = 1000;
    int currentBet;
    int bankroll;
    bool playerTurnEnded;
};

#endif // GAMEWIDGET_H
