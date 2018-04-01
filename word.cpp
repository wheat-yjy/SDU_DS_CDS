#include "word.h"

Word::Word(QString wor, QString fileName)
{
    consistIn.append(fileName);
    word = wor;
}

Word::Word(QString wor, QStringList fileNames, Word* left, Word* right)
{
    word = wor;
    consistIn = fileNames;
    left_child = left;
    right_child = right;
}

Word::Word() {}

void Word::addConsistIn(QString wor)
{
    consistIn.append(wor);
}

void Word::delConsistIn(QString wor)
{
    consistIn.removeOne(wor);
}

QStringList Word::getConsistIn() const
{
    return consistIn;
}

void Word::PrintSelf() const
{
    qDebug() << this->word << this->consistIn;
}

