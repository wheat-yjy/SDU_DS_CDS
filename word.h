#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

class Word
{
public:
    Word(QString word, QString fileName);
    Word(QString word, QStringList fileName, Word* left, Word* right);
    Word();

    QString word;

    void addConsistIn(QString wor);
    void delConsistIn(QString wor);
    QStringList getConsistIn() const;

    Word* left_child;
    Word* right_child;
    Word* parent;

    void PrintSelf() const;

    int height;
    int hash;

private:
    QStringList consistIn;
};

#endif // WORD_H
