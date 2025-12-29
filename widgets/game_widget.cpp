#include "game_widget.h"
#include "control_buttons_widget.h"
#include "bet_selection_popup.h"
#include "info_popup.h"
#include "settings_popup.h"

#include <QTimer>

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}, layout(new QGridLayout()), tableWidget(new TableWidget(this)),
      controlButtonsWidget(new ControlButtonsWidget(this)), blackjack(new Blackjack(this))
{
    setLayout(layout);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #444;");

    layout->addWidget(controlButtonsWidget, 5, 0, 1, 1);

    layout->addWidget(tableWidget, 0, 0, 5, 1);

    controlButtonsWidget->addButton("Stand", this, [this](){
        standClicked();
    });
    controlButtonsWidget->addButton("Hit", this, [this](){
        hitClicked();
    });
    controlButtonsWidget->addButton("Settings", this, [this](){
        openSettingsPopup();
    });

    startNewGame();
}

void GameWidget::setBet(int bet)
{
    bankroll -= bet;
    currentBet = bet;
    controlButtonsWidget->setBetInfo(bet, bankroll);
    blackjack->startGame();
    playerTurnEnded = false;

    dealStartCards();
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

void GameWidget::dealStartCards()
{
    const QList<Card> &dealerCards = blackjack->getDealerCards();
    const QList<Card> &playerCards = blackjack->getPlayerCards();

    int timeOffset = 500;
    bool firstCard = true;
    for (Card card: dealerCards) {
        CardWidget* cardWidget = tableWidget->createCardWidget(card);

        QTimer::singleShot(timeOffset, tableWidget, [this, cardWidget, firstCard](){
            tableWidget->tossCardToDealer(cardWidget, !firstCard);
        });

        if (firstCard) {
            firstCard = false;
        }

        timeOffset += 500;
    }

    for (Card card: playerCards) {
        CardWidget* cardWidget = tableWidget->createCardWidget(card);

        QTimer::singleShot(timeOffset, tableWidget, [this, cardWidget](){
            tableWidget->tossCardToPlayer(cardWidget, true);
        });

        timeOffset += 500;
    }

    Card card = blackjack->getNextCard();
    tableWidget->createCardWidget(card);

    QTimer::singleShot(timeOffset, tableWidget, [this](){
        updatePlayerCardValue();
    });
}

void GameWidget::updatePlayerCardValue()
{
    int value = blackjack->countPlayerCards();
    tableWidget->updatePlayerCardValue(value);
}

void GameWidget::updateDealerCardValue()
{
    int value = blackjack->countDealerCards();
    tableWidget->updateDealerCardValue(value);
}

void GameWidget::hitClicked()
{
    if (playerTurnEnded) {
        return;
    }

    if (blackjack->playerHit() == Blackjack::GameStatus::DealerWon) {
        playerTurnEnded = true;
        endRound();
    }

    tableWidget->tossLastCardToPlayer();
    Card card = blackjack->getNextCard();
    tableWidget->createCardWidget(card);

    updatePlayerCardValue();
}

void GameWidget::standClicked()
{
    if (playerTurnEnded) {
        return;
    } else {
        playerTurnEnded = true;
    }

    tableWidget->flipDealerHiddenCard();
    updateDealerCardValue();

    dealerHit();
}

void GameWidget::endRound()
{
    updateDealerCardValue();

    Blackjack::GameStatus result = blackjack->getGameResult();
    QString text;
    if (result == Blackjack::GameStatus::Draw) {
        text = "Draw! Press OK to stand next round.";
        bankroll += currentBet;
    } else if (result == Blackjack::GameStatus::DealerWon) {
        if (bankroll < BET_STEP) {
            bankroll = START_BANKROLL;
            text = QString("GAME OVER! You lost all your money. Press OK to start a new game.");
        } else {
            text = QString("You lost! Money: -%1").arg(currentBet);
        }
    } else if (result == Blackjack::GameStatus::PlayerWon) {
        text = QString("You won! Money: +%1. Press OK to stand next round.").arg(currentBet);
        bankroll += currentBet * 2;
    }

    InfoPopup* popupWidget = new InfoPopup(text, this);
    layout->addWidget(popupWidget, 2, 0, 1, 1);

    connect(popupWidget, &InfoPopup::acknowledged, this, [this](){
        tableWidget->deleteLater();
        tableWidget = new TableWidget(this);
        showBetSelectionPopup();
        layout->addWidget(tableWidget, 0, 0, 5, 1);
    });
}

void GameWidget::dealerHit()
{
    if (blackjack->dealerIsDone()) {
        endRound();
        return;
    }

    QTimer::singleShot(500, tableWidget, [this](){
        tableWidget->tossLastCardToDealer();
        Card card = blackjack->getNextCard();
        tableWidget->createCardWidget(card);

        if (blackjack->dealerHit() == Blackjack::GameStatus::InProgress) {
            dealerHit();
        } else {
            endRound();
        }
    });
}

void GameWidget::openSettingsPopup()
{
    SettingsPopup* settingsPopup = new SettingsPopup(this);
    layout->addWidget(settingsPopup, 0, 0, 5, 1);
}
