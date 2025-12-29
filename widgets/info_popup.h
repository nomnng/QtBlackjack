#ifndef INFOPOPUP_H
#define INFOPOPUP_H

#include "popup_widget.h"

class InfoPopup : public PopupWidget
{
    Q_OBJECT
public:
    explicit InfoPopup(QString text, QWidget *parent = nullptr);

signals:
    void acknowledged();

protected:
    void okPressed() override;

private:
    void setupContent(QWidget *parent, QString text);
};

#endif // INFOPOPUP_H
