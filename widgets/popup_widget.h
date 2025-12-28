#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>

class PopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PopupWidget(QWidget *parent = nullptr);

protected:
    virtual void okPressed();

    QWidget* contentWidget = nullptr;
};

#endif // POPUPWIDGET_H
