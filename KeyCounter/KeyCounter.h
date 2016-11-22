#ifndef KEYCOUNTER_H
#define KEYCOUNTER_H

#include <QtWidgets/QMainWindow>
#include "ui_KeyCounter.h"

class KeyCounter : public QMainWindow
{
	Q_OBJECT

public:
	KeyCounter(QWidget *parent = 0);
	~KeyCounter();

private:
	Ui::KeyCounterClass ui;
};

#endif // KEYCOUNTER_H
