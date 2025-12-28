#include "card_image_provider.h"

#include <QDir>

CardImageProvider &CardImageProvider::instance()
{
    static CardImageProvider _instance;
    return _instance;
}

const QStringList &CardImageProvider::getFrontOptions()
{
    return instance().frontImageList;
}

const QStringList &CardImageProvider::getBackOptions()
{
    return instance().backImageList;
}

const void CardImageProvider::setBackImage(QString name)
{
    QString filepath = QDir::cleanPath(QString(BACKS_PATH) + "/" + name + "." + IMAGE_EXTENSION);
    instance().backPixmap.load(filepath);
}

const void CardImageProvider::setFrontAtlasImage(QString name)
{
    QString filepath = QDir::cleanPath(QString(FRONTS_PATH) + "/" + name + "." + IMAGE_EXTENSION);
    instance().frontAtlasPixmap.load(filepath);
}

const QPixmap CardImageProvider::getCardImage(Card card)
{
    CardImageProvider &inst = instance();
    if (inst.frontAtlasPixmap.isNull()) {
        setFrontAtlasImage(inst.frontImageList[0]);
    }

    int rankIndex = static_cast<int>(card.rank) - static_cast<int>(Card::Rank::Two);
    int suitIndex = static_cast<int>(card.suit) - static_cast<int>(Card::Suit::Clubs);
    int x = rankIndex * CARD_WIDTH;
    int y = suitIndex * CARD_HEIGHT;
    return inst.frontAtlasPixmap.copy(x, y, CARD_WIDTH, CARD_HEIGHT);
}

const QPixmap &CardImageProvider::getBackImage()
{
    CardImageProvider &inst = instance();
    if (inst.backPixmap.isNull()) {
        setBackImage(inst.backImageList[0]);
    }

    return inst.backPixmap;
}

CardImageProvider::CardImageProvider(QObject* parent) : QObject(parent)
{
    updateImageList(FRONTS_PATH, frontImageList);
    updateImageList(BACKS_PATH, backImageList);
}

void CardImageProvider::updateImageList(QString path, QStringList &list) {
    QDir dir(path);
    QStringList fileList = dir.entryList(
        QStringList(QString("*.") + IMAGE_EXTENSION), QDir::Files | QDir::NoDotAndDotDot
    );

    for (const QString &filename: fileList) {
        QString frontName = filename.section('.', 0, -2);
        list.append(frontName);
    }
}
