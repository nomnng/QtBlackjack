#ifndef BETSELECTIONPOPUP_H
#define BETSELECTIONPOPUP_H

#include "popup_widget.h"

#include <QLabel>

class BetSelectionPopup : public PopupWidget
{
    Q_OBJECT
public:
    explicit BetSelectionPopup(int maxBet, int betStep, QWidget *parent = nullptr);

signals:
    void betSelected(int bet);

public slots:
    void increaseBet();
    void decreaseBet();

protected:
    void okPressed() override;

private:
    void setupContent(QWidget *parent);

    QLabel* betLabel;
    int currentBet;
    int maxBet;
    int betStep;
};

#endif // BETSELECTIONPOPUP_H
