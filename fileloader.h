#ifndef FILELOADER_H
#define FILELOADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "word.h"

class FileLoader
{
public:
    FileLoader();
    QList<Word> loadAllFile();
    QString delete_punctutaion(QString original);
};

#endif // FILELOADER_H
