#ifndef __class_newwork__
#define __class_newwork__

#include "class_addword.h"
#include "class_edit.h"
#include <QApplication>
#include <QtGui>

class MyNewWord : public QWidget
{
Q_OBJECT
private:
    QDate date;
    
    QTableWidget *tableWidget;
    QTableWidgetItem *lblWord;
    QTableWidgetItem *lblExplain;
    QTableWidgetItem *lbltimer;
    
	QPushButton *btnAdd;
	QPushButton *btnEdit;
	QPushButton *btnDelete;
	QPushButton *btnSave;
	
	MyEditWord editword;
	MyAddWord addWord;
	signals:
    	void editfrom(const QString &str1, const QString &str2);
public:
	MyNewWord();
	
public slots:

    void toEditWord(const QString &, const QString &, const QString &);

	void slotAddNewWord(const QString &, const QString &);

	void slotAdd();
	
	void slotEdit();
	
	void slotDelete();
	
	void slotSave();
};

#endif

