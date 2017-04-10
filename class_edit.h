#ifndef __class_edit__
#define __class_edit__

//#include "class_newword.h"
#include <QApplication>
#include <QtGui>

class MyEditWord : public QWidget
{
Q_OBJECT

private:
    QLabel *labedit;
    QLabel *explain;
    QLineEdit *editword;
    QTextEdit *editexplain;
    QPushButton *confirm;
    QPushButton *clear;
    QPushButton *cancel;
    //MyNewWord word1;
    
public:
    MyEditWord();
signals:
        void fromEditWord(const QString &, const QString &, const QString &);
    
public slots:
    void myconfirm();
    void myclear();
    void editto(const QString &, const QString &);
//    void myaddword(const QString &);
};

#endif


