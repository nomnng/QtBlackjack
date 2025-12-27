#include "control_buttons_widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>

ControlButtonsWidget::ControlButtonsWidget(QWidget *parent)
    : QWidget{parent}, layout(new QHBoxLayout(this))
{
    setLayout(layout);
    this->setAttribute(Qt::WA_StyledBackground, true); // needed to properly change background color
}

void ControlButtonsWidget::createButton(QString text, QObject *receiver, std::function<void()> onClick)
{
    QPushButton* btn = new QPushButton(text, this);
    layout->addWidget(btn);
    btn->setStyleSheet("background-color: #555; border-radius: 8px; font-size: 20px");
    connect(btn, &QPushButton::clicked, receiver, onClick);
}
