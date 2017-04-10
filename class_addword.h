#ifndef __class_addword__
#define __class_addword__

#include <QApplication>
#include <QtGui>

class MyAddWord : public QWidget
{
Q_OBJECT

private:
    QLabel *labword;
    QLabel *explain;
    QLineEdit *editword;
    QTextEdit *editexplain;
    QPushButton *confirm;
    QPushButton *clear;
    QPushButton *cancel;
public:
    MyAddWord();
signals:
    void myNewWord(const QString &, const QString &);
    
public slots:
    void myconfirm();
    void myclear();
    void myaddword(const QString &);
};

#endif

