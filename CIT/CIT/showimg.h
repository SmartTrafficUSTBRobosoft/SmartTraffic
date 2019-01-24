#ifndef SHOWIMG_H
#define SHOWIMG_H

#include <QDialog>
#include "ui_showimg.h"

class showImg : public QDialog
{
	Q_OBJECT

public:
	showImg(QWidget *parent = 0);
	~showImg();

public:
	Ui::showImg ui;
};

#endif // SHOWIMG_H
