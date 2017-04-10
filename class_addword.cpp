#include "class_addword.h"

MyAddWord::MyAddWord()
{
    labword = new QLabel("单词");
    explain = new QLabel("解释");
    editword = new QLineEdit;
    editexplain = new QTextEdit;
    confirm = new QPushButton("确认");
    clear = new QPushButton("清除");
    cancel = new QPushButton("取消");

	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(labword);
		
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
	setWindowTitle("添加单词");
	
	connect(confirm, SIGNAL(clicked()),this,SLOT(myconfirm()));
	connect(clear, SIGNAL(clicked()), this, SLOT(myclear()));
	connect(editword, SIGNAL(textChanged(const QString &)), SLOT(myaddword(const QString &)));
	connect(cancel, SIGNAL(clicked()),this, SLOT(close()));
	
	QIcon qi("1.jpg");
	setWindowIcon(qi);
	
}
void MyAddWord::myclear()
{
	editword->setText("");
	editexplain->setPlainText("");
}
void MyAddWord::myaddword(const QString & text)
{
	QString line,strDisplay;
	int flag = 0;
	
	QString strSearch = editword->text();
	
	QFile file("word.txt");
	
	if (!file.open(QFile::ReadOnly))
	return;
	
	QTextStream in(&file);

	line = in.readLine();
		
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
				editexplain->setPlainText(strDisplay);
				break;
			}
		}
		else
		{
			editexplain->setPlainText("");
		}
	}
}

void MyAddWord::myconfirm()
{
	emit myNewWord(editword->text(), editexplain->toPlainText ());
}

