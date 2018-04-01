#include <sys/time.h>

#include "search.h"
#include "rbtree.h"

Search::Search()
{
}

QStringList Search::sequential_search(QString key, QList<Word> words) const
{
    // result need check.
    int count = 0;
    double time_start = (double)clock();
    Word result;
    for(Word w: words) {
        count++;
        if(key == w.word) {
            result = w;
        }
    }
    double time_end = (double)clock();
    double time = time_end - time_start;

    QStringList result_list = result.getConsistIn();
    result_list.append(QString::number(count));
    result_list.append(QString::number(time/80));

qDebug() << "sequential_search" << result_list;

    return result_list;
}

QStringList Search::binary_search(QString key, QList<Word> words)
{
    // 1. sort
    // 2. search
    // 3. time last


    int count = 0;
    int left = 0;
    int right = words.length() - 1;
    int mid;
    Word result;
    quick_sort(words, 1, words.length()-1);
    double time_start = (double)clock();
    while(left <= right)
    {
        count++;
        mid = (left + right)>>1;   // move positionv faster than division
        if(key < words[mid].word)
        {
            right = mid - 1;
        } else if(words[mid].word < key) {
            left = mid + 1;
        } else {
            result = words[mid];
            break;
        }
    }

    double time_end = (double)clock();
    double time = time_end - time_start;
    QStringList result_list = result.getConsistIn();
    result_list.append(QString::number(count));
    result_list.append(QString::number(time/80));
qDebug() << "binary_search" << result_list;

    return result_list;
}

//QStringList Search::interpolation_search(QString key, QList<Word> words)
//{
//    // maybe can't
//    // how to express string's sub
//    return QStringList;
//}

//QStringList Search::fibonacci_search(QString key, QList<Word> words)
//{
//    // can't create a QString fibonacci array
//    return QList<Word>();
//}

QStringList Search::avl_search(QString key, QList<Word> words)
{

    QStringList result_list;
    AVLTree* tree = new AVLTree();
    for(Word w: words)
        tree->insert(w.word, w.getConsistIn());

    double time_start = (double)clock();
    result_list = tree->search_iterator(key);
    double time_end = (double)clock();
    double time = time_end - time_start;

    result_list.append(QString::number(time/80));

qDebug() << "avl_search" << result_list;

    return result_list;
}

QStringList Search::hash_search(QString key, QList<Word> words)
{
    double time_start = (double)clock();
    QStringList result;
    QHash<QString, QStringList> hashTable;
    for(int i = 0;i < words.length();i++) {
        hashTable.insert(words[i].word, words[i].getConsistIn());
    }

    if(hashTable.contains(key)) {
        result.append(hashTable[key]);
    }
    double time_end = (double)clock();
    double time = time_end - time_start;
    result.append(QString::number(1));
    result.append(QString::number(time/80));

    return result;
}

QStringList Search::rbt_search(QString key, QList<Word> words) {
    RBT<QString, QStringList>* rbt = new RBT<QString, QStringList>();
    for(Word w: words) {
        rbt->put(w.word, w.getConsistIn());
    }

    double time_start = (double)clock();
    QStringList result = rbt->get(key);
    double time_end = (double)clock();
    double time = time_end - time_start;
    qDebug() << Node<QString, QStringList>::count << "Count";
    result.append(QString::number(Node<QString, QStringList>::count));
    result.append(QString::number(time/80));
    Node<QString,QStringList>::count = 0;
    return result;
}

//int Search::hash(QString key)
//{
//    int seed = 131;

//    int hash = 0;

//    for (int i = 0; i < key.length(); i++) {
//     hash = hash * seed + (int)key.at(i);
//    }

//    return hash & 0x7FFFFFFF;
//}

void Search::quick_sort(QList<Word>& words, int low, int high)
{
    // with no recurrence for saving 栈

    std::stack<int> st;
    if(low < high)
    {
        int mid = partition(words, low, high);
        if(low < mid - 1) {
            st.push(low);
            st.push(mid-1);
        }
        if(mid + 1 < high) {
            st.push(mid+1);
            st.push(high);
        }
        while(!st.empty()){
            int q = st.top();
            st.pop();
            int p = st.top();
            st.pop();
            mid = partition(words, p, q);
            if(p<mid-1){
                st.push(p);
                st.push(mid-1);
            }
            if(mid+1<q){
                st.push(mid+1);
                st.push(q);
            }
        }
    }
}

int Search::partition(QList<Word>& vec,int low,int high)
{
    Word pivot = vec[low];
    while(low < high){
        while(low < high && vec[high].word >= pivot.word)
            high--;
        vec[low] = vec[high];
        while(low < high && vec[low].word <= pivot.word)
            low++;
        vec[high] = vec[low];
    }
    vec[low] = pivot;
    return low;
}
