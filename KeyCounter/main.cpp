#include "KeyCounter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KeyCounter w;
	w.show();
	return a.exec();
}
