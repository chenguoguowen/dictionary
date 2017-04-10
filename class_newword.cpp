#include "class_newword.h"

MyNewWord::MyNewWord()
{
	tableWidget = new QTableWidget(0, 3, this);
	btnAdd   = new QPushButton("添加");
	btnEdit  = new QPushButton("编辑");
	btnDelete= new QPushButton("删除");
	btnSave  = new QPushButton("保存");
	
	lblWord = new QTableWidgetItem("单词");
	lblExplain= new QTableWidgetItem("解释");
	lbltimer= new QTableWidgetItem("添加时间");
	tableWidget->setHorizontalHeaderItem(0,lblWord);
	tableWidget->setHorizontalHeaderItem(1,lblExplain);
	tableWidget->setHorizontalHeaderItem(2,lbltimer);
	
	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(tableWidget);
	
	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(btnAdd);
	layout2->addWidget(btnEdit);
	layout2->addWidget(btnDelete);
	layout2->addWidget(btnSave);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(layout1);
	layout->addLayout(layout2);
	
	this->setLayout(layout);
	setWindowTitle("单词本");
	
	connect(this, SIGNAL(editfrom(const QString &, const QString &)), &editword, SLOT(editto(const QString &, const QString &)));
	
	connect(&addWord, SIGNAL(myNewWord(const QString & , const QString &)), this, SLOT(slotAddNewWord(const QString & , const QString &)));
	connect(&editword, SIGNAL(fromEditWord(const QString &, const QString &,const QString &)), this, SLOT(toEditWord(const QString &, const QString &,const QString &)));

//	connect(btnEdit, SIGNAL(editfrom(const QString &, const QString &), &editword, SLOT(editto(const QString &, const QString &)));

	connect(btnAdd, SIGNAL(clicked()), this, SLOT(slotAdd()));
	connect(btnEdit, SIGNAL(clicked()), this, SLOT(slotEdit()));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(slotSave()));
	connect(btnDelete, SIGNAL(clicked()),this, SLOT(slotDelete()));


	QIcon qi("1.jpg");
	setWindowIcon(qi);
	/* read file */
	QString line,strDisplay;
	
	QFile file("save.txt");
	if (!file.open(QFile::ReadOnly))
	return;
	
	QTextStream in(&file);
	line = in.readLine();
	while(!line.isNull())
	{
		int i = tableWidget->rowCount();
		tableWidget->setRowCount(++i);
		QTableWidgetItem *iter1, *iter2, *iter3;
	
		iter1 = new QTableWidgetItem(line);//  qDebug()<<"-----"<<line;
		tableWidget->setItem(i-1, 0, iter1);
		
		line = in.readLine();
		while (line != "*" )//&& !line.isNull())
		{
			strDisplay.append(line);
			strDisplay.append('\n');
			line = in.readLine();
		}
		iter2 = new QTableWidgetItem(strDisplay);// qDebug()<<"-----"<<strDisplay;
		tableWidget->setItem(i-1, 1, iter2);
		strDisplay="";
		
		if(line == "*")line = in.readLine();
		iter3 = new QTableWidgetItem(line);  //  qDebug()<<"-----"<<line;
		tableWidget->setItem(i-1, 2, iter3);
		
		line = in.readLine();
		if(line == "*")line = in.readLine();
	}
}

void MyNewWord::toEditWord(const QString & str1, const QString &str2, const QString &str3)
{
	int j = 0, i = tableWidget->rowCount();//获取表格当前的行数
	for(j = 0; j< i; j++)
	{
		QTableWidgetItem * cell = tableWidget->item(j, 0);
		if(cell == NULL)
		{
			break;
		}	
		QString str = cell->text();
			
		if(str == str1)
		{
			QTableWidgetItem  *iter2, *iter3;

			iter2 = new QTableWidgetItem(str2);
			iter3 = new QTableWidgetItem(str3);
			tableWidget->setItem(i-1, 1, iter2);
			tableWidget->setItem(i-1, 2, iter3);
			break;
		}
	}
}

void MyNewWord::slotAdd()
{
	addWord.show();
}

void MyNewWord::slotAddNewWord(const QString & s1, const QString & s2)
{
	int j = 0,i = tableWidget->rowCount();//获取表格当前的行数
	for(j = 0; j< i; j++)
	{
		QTableWidgetItem * cell = tableWidget->item(j, 0);
		if(cell == NULL)
		{
			break;
		}	
		QString str = cell->text();
			
		if(str == s1)
		{
			QMessageBox box(QMessageBox::Information,"提示","单词已添加!");
			box.exec();
			break;
		}
	}
	
	if(j == i)
	{
		if(s1 == "")
		{
			return;
		}
		tableWidget->setRowCount(++i);
		date = date.currentDate();
		QTableWidgetItem *iter1, *iter2, *iter3;
		
		QString strDate = date.toString("yyyy年MM月dd日");
		iter1 = new QTableWidgetItem(s1);
		iter2 = new QTableWidgetItem(s2);
		iter3 = new QTableWidgetItem(strDate);
		tableWidget->setItem(i-1, 0, iter1);
		tableWidget->setItem(i-1, 1, iter2);
		tableWidget->setItem(i-1, 2, iter3);

		/*禁止表格被编辑*/
		tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//table->setStyleSheet("QTableView::Item{background-color:#FF3EFF}");
		tableWidget->setStyleSheet("QTableView{background-color:deeppink}");
	}
}

void MyNewWord::slotEdit()
{
	int row = tableWidget->currentItem()->row();
	QTableWidgetItem *getitem1 = tableWidget->item(row, 0);
	QTableWidgetItem *getitem2 = tableWidget->item(row, 1);
	QString str1 = getitem1->text();
	QString str2 = getitem2->text();

    emit editfrom(str1, str2);
	
	editword.show();
}

void MyNewWord::slotDelete()
{
	int line = tableWidget->rowCount();
	/*如果单词本是空的，弹出警告*/
	if(line == 0)
	{
		QMessageBox box(QMessageBox::Warning,"警告","生词本已经是空的!");
		box.exec();
		return;
	}
	
	tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);//允许选中多行
	int row = tableWidget->currentItem()->row();
	tableWidget->removeRow(row);
}

void MyNewWord::slotSave()
{
	int j=0, i = tableWidget->rowCount();
	QFile wfile("save.txt");
	if(!wfile.open(QFile::WriteOnly))
	return ;
	QTextStream in(&wfile);
	
	while(j < i)
	{

		QTableWidgetItem *iter1, *iter2, *iter3;
		iter1 = tableWidget->item(j, 0);
		iter2 = tableWidget->item(j, 1);
		iter3 = tableWidget->item(j, 2);
		QString str1, str2, str3;
		str1 = iter1->text();
		str2 = iter2->text();
		str3 = iter3->text();
		
		in<<str1<<"\n"<<str2<<"*\n"<<str3<<"\n*\n";
		
		j ++;
	}
}

