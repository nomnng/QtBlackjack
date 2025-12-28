#include "main_window.h"
#include "game_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    GameWidget* centralWidget = new GameWidget(this);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

