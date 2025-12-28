#include "game_widget.h"
#include "control_buttons_widget.h"
#include "bet_selection_popup.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}, layout(new QGridLayout()), tableWidget(new QWidget(this)),
      controlButtonsWidget(new ControlButtonsWidget(this))
{
    setLayout(layout);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #444;");

    tableWidget->setStyleSheet("background-color: #274;");
    layout->addWidget(tableWidget, 0, 0, 5, 1);

    layout->addWidget(controlButtonsWidget, 5, 0, 1, 1);

    controlButtonsWidget->addButton("Stand", this, [](){
    });
    controlButtonsWidget->addButton("Hit", this, [](){
    });
    controlButtonsWidget->addButton("Settings", this, [this](){
    });

    startNewGame();
}

void GameWidget::setBet(int bet)
{
    bankroll -= bet;
    currentBet = bet;
    controlButtonsWidget->setBetInfo(bet, bankroll);
}

void GameWidget::showBetSelectionPopup()
{
    BetSelectionPopup* popupWidget = new BetSelectionPopup(bankroll, BET_STEP, this);
    layout->addWidget(popupWidget, 0, 0, 6, 1);
    connect(popupWidget, &BetSelectionPopup::betSelected, this, &GameWidget::setBet);
}

void GameWidget::startNewGame()
{
    bankroll = START_BANKROLL;
    showBetSelectionPopup();
}
