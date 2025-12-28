#ifndef CARDIMAGEPROVIDER_H
#define CARDIMAGEPROVIDER_H

#include "game/card.h"

#include <QObject>
#include <QPixmap>

class CardImageProvider : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CardImageProvider)

public:
    static CardImageProvider& instance();
    static const QStringList& getFrontOptions();
    static const QStringList& getBackOptions();

    static const void setBackImage(QString name);
    static const void setFrontAtlasImage(QString name);
    static const QPixmap getCardImage(Card card);
    static const QPixmap& getBackImage();

signals:
    void cardBackChanged();
    void cardFrontChanged();

private:
    CardImageProvider(QObject* parent = nullptr);
    void updateImageList(QString path, QStringList &list);

    static constexpr char FRONTS_PATH[] = ":/assets/fronts";
    static constexpr char BACKS_PATH[] = ":/assets/backs";
    static constexpr char IMAGE_EXTENSION[] = "png";
    static constexpr int CARD_WIDTH = 200;
    static constexpr int CARD_HEIGHT = 300;

    QPixmap frontAtlasPixmap;
    QPixmap backPixmap;
    QStringList frontImageList;
    QStringList backImageList;
};

#endif // CARDIMAGEPROVIDER_H
