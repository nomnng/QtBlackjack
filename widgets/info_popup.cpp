#include "info_popup.h"

#include <QLabel>
#include <QHBoxLayout>

InfoPopup::InfoPopup(QString text, QWidget *parent)
    : PopupWidget{parent}
{
    setupContent(contentWidget, text);
}

void InfoPopup::setupContent(QWidget *parent, QString text)
{
    QHBoxLayout* layout = new QHBoxLayout(parent);
    parent->setLayout(layout);
    QLabel* infoLabel = new QLabel(text, parent);
    infoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(infoLabel, 0, Qt::AlignCenter);
}

void InfoPopup::okPressed()
{
    PopupWidget::okPressed();
    emit acknowledged();
}
