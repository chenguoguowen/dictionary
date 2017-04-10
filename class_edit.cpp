#include "class_edit.h"

MyEditWord::MyEditWord()
{
    labedit = new QLabel("����");
    explain = new QLabel("����");
    editword = new QLineEdit;
	editword->setReadOnly(true);
    editexplain = new QTextEdit;
    confirm = new QPushButton("ȷ��");
    clear = new QPushButton("���");
    cancel = new QPushButton("ȡ��");

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(labedit);
		
	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(editword);
	layout2->addWidget(clear);
		
	QHBoxLayout *layout3 = new QHBoxLayout;
	layout3->addWidget(explain);

	QHBoxLayout *layout4 = new QHBoxLayout;
	layout4->addWidget(editexplain);
		
	QHBoxLayout *layout5 = new QHBoxLayout;
	layout5->addWidget(confirm);
	layout5->addWidget(cancel);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(layout1);
	layout->addLayout(layout2);
	layout->addLayout(layout3);
	layout->addLayout(layout4);
	layout->addLayout(layout5);
		
	this->setLayout(layout);
	setWindowTitle("�༭����");
	
//	connect(&word1, SIGNAL(editfrom(const QString &, const QString &), this, SLOT(editto(const QString &, const QString &)));

	connect(confirm, SIGNAL(clicked()),this,SLOT(myconfirm()));
	connect(clear, SIGNAL(clicked()), this, SLOT(myclear()));
	connect(cancel, SIGNAL(clicked()),this, SLOT(close()));
	
	QIcon qi("1.jpg");
	setWindowIcon(qi);
	
}
void MyEditWord::myclear()
{
	editword->setText("");
	editexplain->setPlainText("");
}

void MyEditWord::editto(const QString & str1, const QString &str2)
{
	editword->setText(str1);
	editexplain->setPlainText(str2);
}

void MyEditWord::myconfirm()
{
	QDate qdate = qdate.currentDate();
	QString strDate = qdate.toString("yyyy��MM��dd��");

	emit fromEditWord(editword->text(), editexplain->toPlainText(), strDate);
}


