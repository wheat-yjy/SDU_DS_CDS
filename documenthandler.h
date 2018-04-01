#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QUrl>
#include <QTextCursor>
#include <QFont>
#include <QStringList>

#include "search.h"
#include "word.h"
#include "fileloader.h"

QT_BEGIN_NAMESPACE
class QTextDocument;
class QQuickTextDocument;
QT_END_NAMESPACE

class DocumentHandler:public QObject
{
    Q_OBJECT


//    DocumentHandler {
//        id:document
//        document: textArea.textDocument
//        cursorPosition: textArea.cursorPosition
//        selectionStart: textArea.selectionStart
//        selectionEnd: textArea.selectionEnd
//        textColor: textArea.color
////        Component.onCompleted: document.load()
//        onLoaded: {
//            textArea.text = text
//        }
//        onError: {
//            errorDialog.text = message
//            errorDialog.visible = true
//        }

//    }

    Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

    Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
    Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
    Q_PROPERTY(bool underline READ underline WRITE setUnderline NOTIFY underlineChanged)

    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

    Q_PROPERTY(QString fileName READ fileName NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileType READ fileType NOTIFY fileUrlChanged)
    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)

    Q_PROPERTY(QString result READ result WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(QList<double> searchTime READ searchTime WRITE setSearchTime NOTIFY searchTimeChanged)
    Q_PROPERTY(QList<int> searchCounts READ searchCounts WRITE setSearchCounts NOTIFY searchCountsChanged)

    Q_PROPERTY(QStringList fileList READ fileList WRITE loadFileList NOTIFY fileListChanged)

    Q_PROPERTY(QString input READ input WRITE setInput NOTIFY inputChanged)

public:
    explicit DocumentHandler(QObject* parent = nullptr);

    QQuickTextDocument *document() const;
    void setDocument(QQuickTextDocument *document);

    int cursorPosition() const;
    void setCursorPosition(int position);

    int selectionStart() const;
    void setSelectionStart(int position);

    int selectionEnd() const;
    void setSelectionEnd(int position);

    QString fontFamily() const;
    void setFontFamily(const QString &family);

    QColor textColor() const;
    void setTextColor(const QColor &color);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    bool bold() const;
    void setBold(bool bold);

    bool italic() const;
    void setItalic(bool italic);

    bool underline() const;
    void setUnderline(bool underline);

    int fontSize() const;
    void setFontSize(int size);

    QString fileName() const;
    QString fileType() const;
    QUrl fileUrl() const;

    QString result() const;
    void setResult(QString resu);

    QStringList fileList() const;
    void loadFileList(QStringList& list);

    QList<double> searchTime() const;
    void setSearchTime(QList<double> stime);

    QList<int> searchCounts() const;
    void setSearchCounts(QList<int> scounts);

    QString input() const;
    void setInput(QString input);

public Q_SLOTS:
    void load(const QUrl& fileUrl);
    void saveAs(const QUrl& fileUrl);

Q_SIGNALS:
    void documentChanged();
    void cursorPositionChanged();
    void selectionStartChanged();
    void selectionEndChanged();

    void fontFamilyChanged();
    void textColorChanged();
    void alignmentChanged();

    void boldChanged();
    void italicChanged();
    void underlineChanged();

    void fontSizeChanged();

    void textChanged();
    void fileUrlChanged();

    void fileListChanged();

    void loaded(const QString& text);
    void error(const QString& message);

    void resultChanged();
    void searchTimeChanged();
    void searchCountsChanged();
    void inputChanged();
private:
    void reset();
    QTextCursor textCursor() const;
    QTextDocument* textDocument() const;
    void mergeFormarOnWordOrSelection(const QTextCharFormat& format);

    QQuickTextDocument* m_document;

    int m_cursorPosition;
    int m_selectionStart;
    int m_selectionEnd;

    QFont m_font;
    int m_fontSize;
    QUrl m_fileUrl;

    QStringList m_fileList;

    QString m_result;
    QList<double> m_searchTime;
    QList<int> m_searchCounts;
    QString m_input;

    QStringList search(QString key);
    QList<Word> words;
};

#endif // DOCUMENTHANDLER_H
