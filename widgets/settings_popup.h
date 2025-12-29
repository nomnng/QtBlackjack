#ifndef SETTINGSPOPUP_H
#define SETTINGSPOPUP_H

#include "popup_widget.h"

#include <QComboBox>

class SettingsPopup : public PopupWidget
{
    Q_OBJECT
public:
    explicit SettingsPopup(QWidget *parent = nullptr);

protected:
    void okPressed() override;

private:
    void setupContent(QWidget* parent);

    QComboBox* comboFront;
    QComboBox* comboBack;
};

#endif // SETTINGSPOPUP_H
