#include "fileloader.h"

FileLoader::FileLoader()
{

}

QList<Word> FileLoader::loadAllFile()
{
    // 1. Load All Contents in files
    // 2. Remove Repeation
    // 3. build a <Word> List

    QString baseStr = "/home/veteran/Search/files/File_";
    QString baseEnd = ".txt";
    QList<Word> wordList;
    QStringList words;

    for(int i = 1;i < 46;i++) {
        QString fileName = baseStr + QString::number(i) + baseEnd;
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return wordList;

        QString article = "";

        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull() && line.length() > 2) {
            article += line;
            line = in.readLine();
        }

        QStringList tempWords = article.split(" ");
        for(int k = 0;k < tempWords.length();k++) {
            tempWords[k] = delete_punctutaion(tempWords[k]);
        }

qDebug() << i << tempWords.length() << wordList.length();

        if(i == 1)
        {
            for(int k = 0;k < tempWords.length();k++)
            {
                wordList.append(Word(tempWords[k], fileName));
                words.append(tempWords[k]);
            }
            continue;
        }


        for(int k = 0;k < tempWords.length();k++) {
            int index = words.indexOf(tempWords[k]);
qDebug() << index;
            if(index > 0)
            {
qDebug() << "enter" << index << tempWords[k] << wordList[index].word;
                if(!wordList[index].getConsistIn().contains(fileName))
                    wordList[index].addConsistIn(fileName);
            } else {
                wordList.append(Word(tempWords[k], fileName));
                words.append(tempWords[k]);
            }
        }
    }


    return wordList;
}


QString FileLoader::delete_punctutaion(QString original)
{
    for(int i = 0;i < original.length();i++)
    {
        if(! original[i].isLetter())
            original.remove(i);
    }

    return original;
}
