#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "ui_setting.h"
#include "myDialog.h"

class setting : public QWidget
{
	Q_OBJECT

public:
	setting(QWidget *parent = 0);
	~setting();
	void stylesheet();

public slots:
	void Click_pushButton_open();
	void Click_pushButton_close();
private:
	Ui::setting ui;
	
};

#endif // SETTING_H
