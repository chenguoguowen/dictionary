#include "class_check.h"
#include "class_addword.h"
//#include "class_mewword.h"
#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTextCodec *code = QTextCodec::codecForName("gbk");
	QTextCodec::setCodecForCStrings(code);
	Mycheck win;
	win.show();

	return app.exec();

	return 0;
}

