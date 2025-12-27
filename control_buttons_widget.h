#ifndef CONTROLBUTTONSWIDGET_H
#define CONTROLBUTTONSWIDGET_H

#include <functional>
#include <QWidget>
#include <QHBoxLayout>

class ControlButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlButtonsWidget(QWidget *parent = nullptr);
    void createButton(QString text, QObject *receiver, std::function<void()> onClick);

signals:

private:
    QHBoxLayout* layout;

};

#endif // CONTROLBUTTONSWIDGET_H
