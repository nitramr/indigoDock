#include "indigomenubar.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QDebug>

IndigoMenuBar::IndigoMenuBar()
{
    QMenu *menuWindow = this->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    QAction *quit = new QAction(menuWindow);
    quit->setText(tr("&Quit"));
    menuWindow->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    // connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));

    loadSettings();

}

bool IndigoMenuBar::loadSettings()
{
    QFile loadFile(QStringLiteral("data/navigation.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open menubarfile.");
        return false;
    }

    QByteArray data = loadFile.readAll();

    qDebug() << "data" << data << endl;

    QJsonParseError jerror;
    QJsonDocument loadDoc(QJsonDocument::fromJson(data, &jerror));
    if(jerror.error != QJsonParseError::NoError) {
        qWarning("Error while parsing json.");
        qDebug() << jerror.errorString() << endl;
        qDebug() << "error at" << QTextCodec::codecForMib(106)->toUnicode(data).mid(jerror.offset - 1, 20) << endl;
        return false;
    }
    /*
    QJsonDocument jdoc= QJsonDocument::fromJson(file.readAll(),&jerror);

    if(jerror.error() != QJsonParserError::NoError)
        return false;
    QJsonObject obj = jdoc.object();
    */

    read(loadDoc.object());
    return true;
}

void IndigoMenuBar::read(const QJsonObject &json)
{
    qDebug() << "json" << json << endl;
    qDebug() << "name" << json["name"].toString();
    // QList<Level> mLevels;
    // QJsonObject player = json["player"].toObject();
    // mPlayer.read(player);

    /* read()
    mName = json["name"].toString();
    mLevel = json["level"].toDouble();
    */

/*
    QJsonArray levelArray = json["levels"].toArray();
    for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
        QJsonObject levelObject = levelArray[levelIndex].toObject();
        Level level;
        level.read(levelObject);
        mLevels.append(level);
    }
*/
}
