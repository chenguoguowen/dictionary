#include "class_check.h"

Mycheck::Mycheck()
{
	editSearch = new QLineEdit;
	editText = new QTextEdit;
	editText->setReadOnly(true);

	btnSearch = new QPushButton("查一下");
	btnAddNewWord = new QPushButton("加入生词本");
	btnNewWord = new QPushButton("进入生词本");
	btnQuit = new QPushButton("退出");

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(editSearch);
	layout1->addWidget(btnSearch);
	
	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(editText);
	
	QHBoxLayout *layout3 = new QHBoxLayout;
	layout3->addWidget(btnAddNewWord);
	layout3->addWidget(btnNewWord);
	layout3->addWidget(btnQuit);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(layout1);
	layout->addLayout(layout2);
	layout->addLayout(layout3);
	
	this->setLayout(layout);
	setWindowTitle("英汉词典");

	connect(editSearch, SIGNAL(textChanged(const QString &)), this, SLOT(slotSearch(const QString &)));
	connect(this, SIGNAL(addNewWord(const QString & , const QString &)), &NewWord, SLOT(slotAddNewWord(const QString & , const QString &)));
	connect(btnAddNewWord, SIGNAL(clicked()), this, SLOT(slotNewWord()));//send message
	connect(btnQuit, SIGNAL(clicked()),qApp, SLOT(quit()));
	connect(btnNewWord, SIGNAL(clicked()), this, SLOT(sendNewWord()));//display show

	QIcon qi("1.jpg");
	setWindowIcon(qi);

}
void Mycheck::slotSearch(const QString & text)
{	
	QString line,strDisplay;
	int flag = 0;
	QString strSearch = editSearch->text();
	QFile file("word.txt");
	if (!file.open(QFile::ReadOnly))
	return;
	
	QTextStream in(&file);
	line = in.readLine();
	//modify
/*	
	while(!line.isNull())
	{
		if (line.left(text.size) == text)
		{
			strDisplay.append(line);
			strDisplay.append('\n');
		}
		line = in.readLine();
	} 
	editText->setPlainText(strDisplay);

*/
	while(!line.isNull())
	{
		if (line.compare(strSearch) == 0)
		{
		   flag = 1;
		}
		line = in.readLine();
		if (flag == 1)
		{
			if (line != "*")
			{
				strDisplay.append(line);
				
				strDisplay.append('\n');
			}
			else
			{
				editText->setPlainText(strDisplay);
				break;
			}
		}
		else
		{
			editText->setPlainText("");
		}
	} 

}

void Mycheck::slotNewWord()
{
	emit addNewWord(editSearch->text(), editText->toPlainText ());
}
void Mycheck::sendNewWord()
{
	NewWord.show();
}

