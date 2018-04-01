#ifndef SEARCH_H
#define SEARCH_H

#include <QString>
#include <QStringList>
#include <QList>
#include <stack>

#include "word.h"
#include "avltree.h"

class Search
{
public:
    Search();

    QStringList sequential_search(QString key, QList<Word> words) const;
    QStringList binary_search(QString key, QList<Word> words);
    QStringList interpolation_search(QString key, QList<Word> words);
    QStringList fibonacci_search(QString key, QList<Word> words);
    QStringList avl_search(QString key, QList<Word> words);
    QStringList hash_search(QString key, QList<Word> words);
    QStringList rbt_search(QString key, QList<Word> words);

private:
    int hash(QString key);
    void quick_sort(QList<Word>& list, int left, int right);
    int partition(QList<Word>& vec, int low, int high);
};

#endif // SEARCH_H
