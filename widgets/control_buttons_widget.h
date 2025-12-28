#ifndef CONTROLBUTTONSWIDGET_H
#define CONTROLBUTTONSWIDGET_H

#include <functional>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class ControlButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlButtonsWidget(QWidget *parent = nullptr);
    void addButton(QString text, QObject *receiver, std::function<void()> onClick);
    void setBetInfo(int bet, int bankroll);

signals:

private:
    QHBoxLayout* layout;
    QLabel* infoLabel;

};

#endif // CONTROLBUTTONSWIDGET_H
