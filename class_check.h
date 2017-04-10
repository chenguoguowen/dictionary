#ifndef __class_check__
#define __class_check__

#include "class_newword.h"
#include "class_addword.h"
#include <QApplication>
#include <QtGui>

class Mycheck : public QWidget
{
Q_OBJECT
private:
	QPushButton *btnSearch;
	QTextEdit *editText;
	QLineEdit *editSearch;
	QPushButton *btnAddNewWord;
	QPushButton *btnNewWord;
	QPushButton *btnQuit;
	MyNewWord NewWord;
	
	signals:
	void addNewWord(const QString & str1, const QString &str2);

public:
	Mycheck();
public slots:

	void slotSearch(const QString &);
	void slotNewWord();
	void sendNewWord();
};


#endif

