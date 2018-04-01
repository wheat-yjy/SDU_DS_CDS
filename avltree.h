#include <QString>
#include <QDebug>

#include "word.h"

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void preOrder();
    void InOrder();
    void postOrder();

    void print();
    void destory();

    void insert(QString key, QStringList fileNames);
    void remove(QString key);

    Word* search_recurse(QString key);
    QStringList search_iterator(QString key);
    QString minimum();
    QString maximum();

    int height();

private:
    Word* root;

private:
    void preOrder(Word* pnode) const;
    void inOrder(Word* pnode) const;
    void postOrder(Word* pnode) const;

    void print(Word* pnode,QString key, int direction) const;
    void destory(Word* & pnode);

    int height(Word* pnode) ;

    Word* insert(Word* &pnode, QString key, QStringList fileNames);
    Word* remove(Word* & pnode, QString key);

    Word* minimum(Word*pnode)const;
    Word* maximum(Word*pnode)const;

    Word* search_recurse(Word* pnode, QString key) const;
    QStringList search_iterator(Word* pnode, QString key) const;

    Word* leftRotation(Word* pnode);
    Word* rightRotation(Word* pnode);
    Word* leftRightRotation(Word* pnode);
    Word* rightLeftRotation(Word* pnode);
};
