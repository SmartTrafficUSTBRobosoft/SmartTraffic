#pragma once

#include <QDialog>
#include "ui_showImg2.h"

class showImg2 : public QDialog
{
	Q_OBJECT

public:
	showImg2(QWidget *parent = Q_NULLPTR);
	~showImg2();

public:
	Ui::showImg2 ui;
};
