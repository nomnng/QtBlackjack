#include "game_widget.h"
#include "control_buttons_widget.h"
#include "bet_selection_popup.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{
    layout = new QGridLayout();
    setLayout(layout);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #444;");

    QWidget* tableWidget = new QWidget(this);
    tableWidget->setStyleSheet("background-color: #274;");
    layout->addWidget(tableWidget, 0, 0, 5, 1);

    ControlButtonsWidget* controlButtonsWidget = new ControlButtonsWidget(this);
    layout->addWidget(controlButtonsWidget, 5, 0, 1, 1);

    controlButtonsWidget->createButton("Stand", this, [](){
    });
    controlButtonsWidget->createButton("Hit", this, [](){
    });
    controlButtonsWidget->createButton("Settings", this, [this](){
    });

    showBetSelectionPopup();
}

void GameWidget::startGame(int bet)
{
    qDebug() << "Starting game, bet: " << bet;
}

void GameWidget::showBetSelectionPopup()
{
    BetSelectionPopup* popupWidget = new BetSelectionPopup(10000, BET_STEP, this);
    layout->addWidget(popupWidget, 0, 0, 6, 1);
    connect(popupWidget, &BetSelectionPopup::betSelected, this, &GameWidget::startGame);
}
