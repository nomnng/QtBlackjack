#include "mainwindow.h"
#include "card_widget.h"
#include "control_buttons_widget.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

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

    CardWidget* cardWidget = new CardWidget(Card::Rank::Ace, Card::Suit::Diamonds, gameWidget);
    cardWidget->move(0, 0);

    ControlButtonsWidget* buttonsWidget = new ControlButtonsWidget(this);
    buttonsWidget->setStyleSheet("background-color: #777;");
    layout->addWidget(buttonsWidget, 5, 0, 1, 1);

    buttonsWidget->createButton("Move", cardWidget, [cardWidget](){
        cardWidget->animatedMove(cardWidget->x() + 100, cardWidget->y() + 100);
    });

    buttonsWidget->createButton("Flip", cardWidget, [cardWidget](){
        cardWidget->flip();
    });
}

MainWindow::~MainWindow()
{
}

