#include "popup_widget.h"

#include <QPushButton>
#include <QStyle>
#include <QGridLayout>

PopupWidget::PopupWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #679; font-size: 24px;");

    QGridLayout* layout = new QGridLayout(this);
    setLayout(layout);

    QPushButton* closeBtn = new QPushButton("OK", this);
    closeBtn->setStyleSheet(R"(
        color: white;
        background-color: #333;
        border-radius: 5px;
        padding: 10px;
    )");
    connect(closeBtn, &QPushButton::clicked, this, &PopupWidget::okPressed);
    layout->addWidget(closeBtn, 5, 0, 1, 4, Qt::AlignCenter);

    contentWidget = new QWidget(this);
    contentWidget->setStyleSheet("background-color: transparent;");
    layout->addWidget(contentWidget, 0, 0, 5, 4);
}

void PopupWidget::okPressed()
{
    deleteLater();
}
