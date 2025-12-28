#include "control_buttons_widget.h"

#include <QPushButton>

ControlButtonsWidget::ControlButtonsWidget(QWidget *parent)
    : QWidget{parent}, layout(new QHBoxLayout(this))
{
    setLayout(layout);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #777; font-size: 20px;");

    infoLabel = new QLabel(this);
    layout->addWidget(infoLabel);
}

void ControlButtonsWidget::addButton(QString text, QObject *receiver, std::function<void()> onClick)
{
    QPushButton* btn = new QPushButton(text, this);
    layout->addWidget(btn);
    btn->setStyleSheet("background-color: #444; color: #DDD; border-radius: 8px;");
    connect(btn, &QPushButton::clicked, receiver, onClick);
}

void ControlButtonsWidget::setBetInfo(int bet, int bankroll)
{
    QString text = QString("Bet: %1\nBankroll: %2").arg(bet).arg(bankroll);
    infoLabel->setText(text);
}
