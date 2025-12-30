#include "bet_selection_popup.h"
#include "utils/audio_manager.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

BetSelectionPopup::BetSelectionPopup(int maxBet, int betStep, QWidget *parent)
    : PopupWidget{parent}, currentBet(betStep), maxBet(maxBet), betStep(betStep)
{
    setupContent(contentWidget);
}

void BetSelectionPopup::setupContent(QWidget *parent)
{
    QHBoxLayout* layout = new QHBoxLayout(parent);
    parent->setLayout(layout);
    layout->addStretch(4);

    QString btnStyle = R"(
        background-color: #329;
        border-radius: 12px;
        color: white;
    )";

    layout->addWidget(new QLabel("Bet: ", this), 1);

    QPushButton* minusBtn = new QPushButton("-", parent);
    minusBtn->setStyleSheet(btnStyle);
    connect(minusBtn, &QPushButton::clicked, this, &BetSelectionPopup::decreaseBet);
    layout->addWidget(minusBtn, 1);

    betLabel = new QLabel(QString::number(currentBet), parent);
    betLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(betLabel, 1);

    QPushButton* plusBtn = new QPushButton("+", parent);
    plusBtn->setStyleSheet(btnStyle);
    connect(plusBtn, &QPushButton::clicked, this, &BetSelectionPopup::increaseBet);
    layout->addWidget(plusBtn, 1);

    QString remainingText = QString("  |  Bankroll: %1").arg(maxBet);
    layout->addWidget(new QLabel(remainingText, this), 1);

    layout->addStretch(4);
}

void BetSelectionPopup::increaseBet()
{
    AudioManager::playButtonSound();

    if ((currentBet + betStep) > maxBet) {
        return;
    }
    currentBet += betStep;
    betLabel->setNum(currentBet);
}

void BetSelectionPopup::decreaseBet()
{
    AudioManager::playButtonSound();

    if (currentBet <= betStep) {
        return;
    }
    currentBet -= betStep;
    betLabel->setNum(currentBet);
}

void BetSelectionPopup::okPressed()
{
    PopupWidget::okPressed();
    emit betSelected(currentBet);
}

