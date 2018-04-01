#include "documenthandler.h"

#include <QFile>
#include <QFileInfo>
#include <QFileSelector>
#include <QQmlFile>
#include <QQmlFileSelector>
#include <QQuickTextDocument>
#include <QTextCharFormat>
#include <QTextCodec>
#include <QTextDocument>
#include <QDebug>

DocumentHandler::DocumentHandler(QObject *parent)
    :QObject(parent)
    ,m_document(nullptr)
    ,m_cursorPosition(-1)
    ,m_selectionStart(0)
    ,m_selectionEnd(0)
{
    QStringList * list;
    loadFileList(*list);

    FileLoader loader;
    words = loader.loadAllFile();
}

QQuickTextDocument* DocumentHandler::document() const
{
    qDebug() << "document()" ;
    return m_document;
}

void DocumentHandler::setDocument(QQuickTextDocument *document)
{
    qDebug() << "setDocument" ;

    if (document == m_document)
        return;

    m_document = document;
    emit documentChanged();
    qDebug() << "emit DocumentChanged";
}

int DocumentHandler::cursorPosition() const
{
    qDebug() << "cursorPosition" ;
    return m_cursorPosition;
}

void DocumentHandler::setCursorPosition(int position)
{
    if(position == m_cursorPosition)
        return;

    m_cursorPosition = position;
    reset();
    emit cursorPositionChanged();
    qDebug() << "emit cursorPositionChanged";
}

int DocumentHandler::selectionStart() const
{
    qDebug() << "selectionStart";
    return m_selectionStart;
}

void DocumentHandler::setSelectionStart(int position)
{
    qDebug() << "setSelectionStart";
    if(position == m_selectionStart)
        return;
    m_selectionStart = position;
    emit selectionStartChanged();
    qDebug() << "emit selectionStartChanged";
}

int DocumentHandler::selectionEnd() const
{
    qDebug() << "SelectionEnd";
    return m_selectionEnd;
}

void DocumentHandler::setSelectionEnd(int position)
{
    qDebug() << "setSelectionEnd";
    if(position == m_selectionEnd)
        return;
    m_selectionEnd = position;
    emit selectionEndChanged();
    qDebug() << "emit selectionEndChanged";
}

QString DocumentHandler::fontFamily() const
{
    qDebug() << "fontFamily";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return QString();
    QTextCharFormat format = cursor.charFormat();
    return format.font().family();
}

void DocumentHandler::setFontFamily(const QString &family)
{
    qDebug() << "setFontFamily";
    QTextCharFormat format;
    format.setFontFamily(family);
    mergeFormarOnWordOrSelection(format);
    emit fontFamilyChanged();
    qDebug() << "emit fontFamilyChanged";
}

QColor DocumentHandler::textColor() const
{
    qDebug() << "textColor";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return QColor(Qt::black);
    QTextCharFormat format = cursor.charFormat();
    return format.foreground().color();
}

void DocumentHandler::setTextColor(const QColor &color)
{
    qDebug() << "setTextColor";
    QTextCharFormat format;
    format.setForeground(QBrush(color));
    mergeFormarOnWordOrSelection(format);
    emit textColorChanged();
    qDebug() << "emit textColorChanged";
}

Qt::Alignment DocumentHandler::alignment() const
{
    qDebug() << "alignment";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return Qt::AlignLeft;
    return textCursor().blockFormat().alignment();
}

void DocumentHandler::setAlignment(Qt::Alignment alignment)
{
    qDebug() << "setAlignment";
    QTextBlockFormat format;
    format.setAlignment(alignment);
    QTextCursor cursor = textCursor();
    cursor.mergeBlockFormat(format);
    emit alignmentChanged();
    qDebug() << "emit alignmentChanged";
}

bool DocumentHandler::bold() const
{
    qDebug() << "bold";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return false;
    return textCursor().charFormat().fontWeight() == QFont::Bold;
}

void DocumentHandler::setBold(bool bold)
{
    qDebug() << "setBold";
    QTextCharFormat format;
    format.setFontWeight(bold ? QFont::Bold : QFont::Normal);
    mergeFormarOnWordOrSelection(format);
    emit boldChanged();
    qDebug() << "emit boldChanged";
}

bool DocumentHandler::italic() const
{
    qDebug() << "italic";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return false;
    return textCursor().charFormat().fontItalic();
}

void DocumentHandler::setItalic(bool italic)
{
    qDebug() << "setItalic";
    QTextCharFormat format;
    format.setFontItalic(italic);
    mergeFormarOnWordOrSelection(format);
    emit italicChanged();
}

bool DocumentHandler::underline() const
{
    qDebug() << "underline";
    QTextCursor cursor = textCursor();
    if(cursor.isNull())
        return false;
    return textCursor().charFormat().fontUnderline();
}

void DocumentHandler::setUnderline(bool underline)
{
    qDebug() << "setUnderline";
    QTextCharFormat format;
    format.setFontUnderline(underline);
    mergeFormarOnWordOrSelection(format);
    emit underlineChanged();
    qDebug() << "emit underlineChanged";
}

int DocumentHandler::fontSize() const
{
    qDebug() << "fontSize";
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return 0;
    QTextCharFormat format = cursor.charFormat();
    return format.font().pointSize();
}

void DocumentHandler::setFontSize(int size)
{
    qDebug() << "setFontSize";
    if (size <= 0)
        return;

    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if (cursor.charFormat().property(QTextFormat::FontPointSize).toInt() == size)
        return;

    QTextCharFormat format;
    format.setFontPointSize(size);
    mergeFormarOnWordOrSelection(format);
    emit fontSizeChanged();
    qDebug() << "emit fontSizeChanged";
}

QStringList DocumentHandler::fileList() const
{
    return m_fileList;
}

void DocumentHandler::loadFileList(QStringList& list)
{
    // from file read info for fileList
    // file format: xml
    // <root><file fileName:name CreateTime:time><file></root>
    // itemInList: name|time in two rows
    // learn how to operate XML
    // everyTime open , show the first file
    qDebug() << "load FileList";
    emit fileListChanged();
}

QString DocumentHandler::fileName() const
{
    qDebug() << "fileName";
    const QString filePath = QQmlFile::urlToLocalFileOrQrc(m_fileUrl);
    const QString fileName = QFileInfo(filePath).fileName();
    if (fileName.isEmpty())
        return QStringLiteral("untitled.txt");
    return fileName;
}

QString DocumentHandler::fileType() const
{
    qDebug() << "fileType";
    return QFileInfo(fileName()).suffix();
}

QUrl DocumentHandler::fileUrl() const
{
    qDebug() << "fileUrl";
    return m_fileUrl;
}

void DocumentHandler::load(const QUrl &fileUrl)
{
    qDebug() << fileUrl.fileName();

    if (fileUrl == m_fileUrl)
        return;

    QQmlEngine *engine = qmlEngine(this);
    if (!engine) {
        qWarning() << "load() called before DocumentHandler has QQmlEngine";
        return;
    }

    const QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrl);
    const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
    if (QFile::exists(fileName)) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            QByteArray data = file.readAll();
            QTextCodec *codec = QTextCodec::codecForHtml(data);
            if (QTextDocument *doc = textDocument())
                doc->setModified(false);

            emit loaded(codec->toUnicode(data));
            qDebug() << "emit loaded()";
            reset();
        }
    }
qDebug() << fileUrl.fileName();
    m_fileUrl = fileUrl;
    emit fileUrlChanged();
    qDebug() << "emit fileUrlChanged";
}

void DocumentHandler::saveAs(const QUrl &fileUrl)
{

    QTextDocument *doc = textDocument();
    if (!doc)
        return;

    const QString filePath = fileUrl.toLocalFile();
    const bool isHtml = QFileInfo(filePath).suffix().contains(QLatin1String("htm"));
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | (isHtml ? QFile::NotOpen : QFile::Text))) {
        emit error(tr("Cannot save: ") + file.errorString());
        qDebug() << "emit errorChanged";
        return;
    }

    file.write((isHtml ? doc->toHtml() : doc->toPlainText()).toUtf8());
    file.close();

    if (fileUrl == m_fileUrl)
        return;

    m_fileUrl = fileUrl;
    emit fileUrlChanged();
    qDebug() << "emit fileUrlChanged";
}

void DocumentHandler::reset()
{
    emit fontFamilyChanged();
    emit alignmentChanged();
    emit boldChanged();
    emit italicChanged();
    emit underlineChanged();
    emit fontSizeChanged();
    emit textColorChanged();
}

QTextCursor DocumentHandler::textCursor() const
{
    qDebug() << "textCursor";
    QTextDocument *doc = textDocument();
    if (!doc)
        return QTextCursor();

    QTextCursor cursor = QTextCursor(doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }
    return cursor;
}

QTextDocument* DocumentHandler::textDocument() const
{
    qDebug() << "textDocument";
    if (!m_document)
        return nullptr;

    return m_document->textDocument();
}

void DocumentHandler::mergeFormarOnWordOrSelection(const QTextCharFormat &format)
{
    qDebug() << "mergeFormatOnWordOrSelection";
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
}

QString DocumentHandler::result() const
{
    return m_result;
}

void DocumentHandler::setResult(QString resu)
{
    m_result = resu;
    emit resultChanged();
}

QList<double> DocumentHandler::searchTime() const
{
    return m_searchTime;
}

void DocumentHandler::setSearchTime(QList<double> stime)
{
    m_searchTime = stime;
    for(int i = 0;i < stime.length();i++) {
        qDebug() << stime[i];
    }
    emit searchTimeChanged();
}

QList<int> DocumentHandler::searchCounts() const
{
    return m_searchCounts;
}

void DocumentHandler::setSearchCounts(QList<int> scounts)
{
    m_searchCounts = scounts;
    for(int i = 0;i < scounts.length();i++) {
        qDebug() << scounts[i];
    }
    emit searchCountsChanged();
}

QString DocumentHandler::input() const
{
    return m_input;
}

void DocumentHandler::setInput(QString input)
{
    m_input = input;
    qDebug() << input;
    if(!(m_input == "null")) {

        input.replace("and", "AND");
        input.replace("And", "AND");
        input.replace("ANd", "AND");
        input.replace("aNd", "AND");
        input.replace("aND", "AND");
        input.replace("anD", "AND");
        input.replace("AnD", "AND");

        input.replace("or", "OR");
        input.replace("Or", "OR");
        input.replace("oR", "OR");

        QStringList a_inputWords = input.split(" ");
        QStringList and_list;
        QStringList or_list;
        for(int i = 0;i < a_inputWords.length();i++) {
            if(i == 0 && a_inputWords[1] == "AND") {
                and_list.append(a_inputWords[0]);
                continue;
            }
            if(i == 0 && a_inputWords[1] == "OR") {
                or_list.append(a_inputWords[0]);
                continue;
            }
            if(i % 2 == 0 && a_inputWords[i-1] == "AND") {
                and_list.append(a_inputWords[i]);
            }
            if(i % 2 == 0 && a_inputWords[i-1] == "OR") {
                or_list.append(a_inputWords[i]);
            }
        }

        qDebug() << "and_list" << and_list;
        qDebug() << "or_list" << or_list;

        QStringList and_result; // dou chu xian
        for(int i = 0;i < and_list.length();i++) {
            QStringList temp = search(and_list[i]);
            if(i == 0) {
                and_result = temp;
                continue;
            }
            QStringList temp_result;
            for(int k = 0;k < temp.length();k++) {
                if(and_result.contains(temp[k]))
                    temp_result.append(temp[k]);
            }
            and_result = temp_result;
        }

        QSet<QString> or_set; // chu xian jiu suan
        for(QString key: or_list) {
            QStringList temp = search(key);
            for(int i = 0;i < temp.length();i++)
                or_set.insert(temp[i]);
        }

        QStringList result = and_result + QStringList().fromSet(or_set);

        m_result = "";

        for(int i = 0;i < result.length();i++) {
            QStringList temp = result[i].split("/");

            if(i % 3 == 0) {
                m_result += "\n" + temp[temp.length()-1];
            }
            m_result += "\t\t" + temp[temp.length()-1];
        }
        qDebug() << "final result" << m_result;
        setResult(m_result);
        emit inputChanged();
    }
}

QStringList DocumentHandler::search(QString key)
{
    Search s;
    QStringList sequential_search = s.sequential_search(key, words);
    QStringList binary_search = s.binary_search(key, words);
    QStringList avl_search = s.avl_search(key, words);
    QStringList hash_search = s.hash_search(key, words);
    QStringList rbt_search = s.rbt_search(key, words);

    QList<int> scounts;
    bool ok;
    scounts.append(sequential_search[sequential_search.length()-2].toInt(&ok, 10)/100);
    scounts.append(binary_search[binary_search.length()-2].toInt(&ok, 10));
    scounts.append(avl_search[avl_search.length()-2].toInt(&ok, 10));
    scounts.append(hash_search[hash_search.length()-2].toInt(&ok, 10));
    scounts.append(rbt_search[rbt_search.length()-2].toInt(&ok, 10));
    setSearchCounts(scounts);

    QList<double> stime;
    QString a;
    stime.append(sequential_search[sequential_search.length()-1].toDouble(&ok));
    stime.append(binary_search[binary_search.length()-1].toDouble(&ok));
    stime.append(avl_search[avl_search.length()-1].toDouble(&ok));
    stime.append(hash_search[hash_search.length()-1].toDouble(&ok));
    stime.append(rbt_search[rbt_search.length()-1].toDouble(&ok));
    setSearchTime(stime);

    sequential_search.removeLast();
    sequential_search.removeLast();
    return sequential_search;
}
