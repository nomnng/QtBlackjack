#include "settings_popup.h"
#include "utils/card_image_provider.h"

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>

SettingsPopup::SettingsPopup(QWidget *parent)
    : PopupWidget{parent}
{
    setupContent(contentWidget);
}

void SettingsPopup::setupContent(QWidget *parent)
{
    QGridLayout* layout = new QGridLayout(parent);

    QString comboStyle = R"(
        border: 1px solid gray;
        border-radius: 3px;
        padding: 1px 18px 1px 3px;
        min-width: 6em;
        background-color: white;
    )";

    QLabel* labelFront = new QLabel("Card front:", parent);
    comboFront = new QComboBox(parent);
    comboFront->addItems(CardImageProvider::getFrontOptions());
    comboFront->setStyleSheet(comboStyle);

    QLabel* labelBack = new QLabel("Card back:", parent);
    comboBack = new QComboBox(parent);
    comboBack->addItems(CardImageProvider::getBackOptions());
    comboBack->setStyleSheet(comboStyle);

    layout->addWidget(labelFront, 0, 0);
    layout->addWidget(comboFront, 0, 1);

    layout->addWidget(labelBack, 1, 0);
    layout->addWidget(comboBack, 1, 1);

    layout->setAlignment(Qt::AlignTop);
}

void SettingsPopup::okPressed()
{
    PopupWidget::okPressed();

    CardImageProvider& cardImageProvider = CardImageProvider::instance();
    cardImageProvider.setFrontAtlasImage(comboFront->currentText());
    cardImageProvider.setBackImage(comboBack->currentText());
}

