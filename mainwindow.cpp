#include "mainwindow.h"
#include "card_image_provider.h"

#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: #444;");
    setCentralWidget(centralWidget);

    QGridLayout* layout = new QGridLayout();
    centralWidget->setLayout(layout);

    QWidget* gameWidget = new QWidget(this);
    gameWidget->setStyleSheet("background-color: #274;");
    layout->addWidget(gameWidget, 0, 0, 5, 1);

    QLabel *cardBack = new QLabel(gameWidget);
    cardBack->setPixmap(CardImageProvider::getBackImage());

    QLabel *cardFront = new QLabel(gameWidget);
    cardFront->setGeometry(220, 0, 200, 300);
    cardFront->setScaledContents(true);
    cardFront->setPixmap(CardImageProvider::getCardImage(Card::Rank::Ace, Card::Suit::Diamonds));

    QWidget* buttonsWidget = new QWidget(this);
    buttonsWidget->setStyleSheet("background-color: #777;");
    layout->addWidget(buttonsWidget, 5, 0, 1, 1);
}

MainWindow::~MainWindow()
{
}

