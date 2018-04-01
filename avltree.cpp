#include <algorithm>
#include "avltree.h"

AVLTree::AVLTree():root(nullptr){}

AVLTree::~AVLTree()
{
    destory(root);
}

void AVLTree::insert(QString key, QStringList fileNames)
{
    this->insert(root, key, fileNames);
}

void AVLTree::remove(QString key)
{
    remove(key);
}

int AVLTree::height() {
    return height(root);
}

int AVLTree::height(Word* pnode) {
    if (pnode != nullptr) {
        return pnode->height;
    }
    return 0;
}

Word* AVLTree::leftRotation(Word* proot) {

    Word* prchild = proot->right_child;
    proot->right_child = prchild->left_child;
    prchild->left_child = proot;

    proot->height = std::max(height(proot->left_child),height(proot->right_child))+1;
    prchild->height = std::max(height(prchild->left_child), height(prchild->right_child)) + 1;

    return prchild;
}

Word* AVLTree::rightRotation(Word* proot) {
    Word* plchild = proot->left_child;
    proot->left_child = plchild->right_child;
    plchild->right_child = proot;

    proot->height = std::max(height(proot->left_child), height(proot->right_child)) + 1;
    plchild->height = std::max(height(plchild->left_child), height(plchild->right_child)) + 1;

    return plchild;
}

Word* AVLTree::rightLeftRotation(Word* proot) {
    proot->right_child = rightRotation(proot->right_child);
    return leftRotation(proot);
}

Word* AVLTree::leftRightRotation(Word* proot) {
    proot->left_child= leftRotation(proot->left_child);
    return rightRotation(proot);
}

Word* AVLTree::insert(Word* &pnode, QString key, QStringList fileNames) {
    if (pnode == nullptr) {
        pnode = new Word(key, fileNames, nullptr, nullptr);
    }
    else if (key > pnode->word) {
        pnode->right_child = this->insert(pnode->right_child, key, fileNames);
        if (height(pnode->right_child) - height(pnode->left_child) == 2) {
            if (key > pnode->right_child->word)
                pnode=leftRotation(pnode);
            else if (key < pnode->right_child->word)
                pnode=rightLeftRotation(pnode);
        }
    }
    else if (key < pnode->word) {

        pnode->left_child = this->insert(pnode->left_child, key, fileNames);
        if (height(pnode->left_child) - height(pnode->right_child) == 2) {

            if (key < pnode->left_child->word)
                pnode = rightRotation(pnode);
            else if (key>pnode->left_child->word)
                pnode = leftRightRotation(pnode);
        }
    }
    pnode->height = std::max(height(pnode->left_child), height(pnode->right_child)) + 1;
    return pnode;
}

Word* AVLTree::remove(Word* &pnode, QString key) {
    if (pnode != nullptr) {
        if (key == pnode->word) {
            if (pnode->left_child != nullptr&&pnode->right_child != nullptr)
            {
                if (height(pnode->left_child) > height(pnode->right_child)) {
                    Word* ppre = maximum(pnode->left_child);
                    pnode->word = ppre->word;
                    pnode->left_child = this->remove(pnode->left_child, ppre->word);
                }
                else  {
                    Word* psuc = minimum(pnode->right_child);
                    pnode->word = psuc->word;
                    pnode->right_child = this->remove(pnode->right_child, psuc->word);
                }
            }
            else {
                Word * ptemp = pnode;
                if (pnode->left_child != nullptr)
                    pnode = pnode->left_child;
                else if (pnode->right_child != nullptr)
                    pnode = pnode->right_child;
                delete ptemp;
                return nullptr;
            }

        }
        else if (key > pnode->word) {

            pnode->right_child =  this->remove(pnode->right_child, key);
            if (height(pnode->left_child) - height(pnode->right_child) == 2) {
                if (height(pnode->left_child->right_child)>height(pnode->left_child->left_child))
                    pnode = leftRightRotation(pnode);
                else
                    pnode = rightRotation(pnode);
            }
        }
        else if (key < pnode->word) {
            pnode->left_child= this->remove(pnode->left_child, key);
            if (height(pnode->right_child) - height(pnode->left_child) == 2) {
                if (height(pnode->right_child->left_child)>height(pnode->right_child->right_child))
                    pnode = rightLeftRotation(pnode);
                else
                    pnode = leftRotation(pnode);
            }
        }
        return pnode;
    }
    return nullptr;
}

Word* AVLTree::search_recurse(QString key) {
    return search_recurse(root,key);
}

Word* AVLTree::search_recurse(Word* pnode, QString key) const {
    if (pnode != nullptr) {
        if (key == pnode->word)
            return pnode;
        if (key > pnode->word)
            return search_recurse(pnode->right_child,key);
        else
            return search_recurse(pnode->left_child,key);
    }
    return nullptr;
}

QStringList AVLTree::search_iterator(QString key) {
    return search_iterator(root, key);
}

QStringList AVLTree::search_iterator(Word* pnode, QString key) const {
    int count = 0;
    QStringList list;
    while (pnode != nullptr) {
        count++;
        if (pnode->word == key){
            list = pnode->getConsistIn();
            list.append(QString::number(count));
            return list;
        }
        else if (key > pnode->word)
            pnode = pnode->right_child;
        else
            pnode = pnode->left_child;
    }
    list.append("null");
    list.append(QString::number(count));
    return list;
}

void AVLTree::preOrder(Word* pnode) const {
    if (pnode != nullptr) {
qDebug() << pnode->word;
        inOrder(pnode->left_child);
        inOrder(pnode->right_child);
    }
}

void AVLTree::preOrder() {
    preOrder(root);
}

void AVLTree::inOrder(Word* pnode) const
{
    if (pnode != nullptr)
    {
        inOrder(pnode->left_child);
qDebug() << pnode->word;
        inOrder(pnode->right_child);
    }
}

void AVLTree::InOrder()
{

qDebug() << "qiao li lai lai";
    inOrder(root);
}

void AVLTree::postOrder(Word* pnode) const
{
    if (pnode != nullptr)
    {
        inOrder(pnode->left_child);
        inOrder(pnode->right_child);
qDebug()<< pnode->word;
    }
}

void AVLTree::postOrder()
{
    postOrder(root);
}

void AVLTree::destory(Word* & pnode)
{
    if (pnode != nullptr)
    {
        destory(pnode->left_child);
        destory(pnode->right_child);
        delete pnode;
        pnode = nullptr;
    }
}

void AVLTree::destory()
{
    destory(root);
}

Word* AVLTree::maximum(Word* pnode)const
{
    if (pnode != nullptr)
    {
        while (pnode->right_child != nullptr)
            pnode = pnode->right_child;
        return pnode;
    }
    return nullptr;
}

QString AVLTree::maximum()
{
    Word* presult = maximum(root);
    if (presult != nullptr)
        return presult->word;
    return "null";
}

Word* AVLTree::minimum(Word* pnode)const
{
    if (pnode != nullptr)
    {
        while (pnode->left_child != nullptr)
            pnode = pnode->left_child;
        return pnode;
    }
    return nullptr;
}

QString AVLTree::minimum()
{
    Word* presult = minimum(root);
    if (presult != nullptr)
        return presult->word;
}
