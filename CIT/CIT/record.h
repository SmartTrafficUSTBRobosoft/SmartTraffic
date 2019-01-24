#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include "ui_record.h"
#include "cit.h"
#include "showimg.h"
#include "showimg2.h"

class record : public QWidget
{
	Q_OBJECT

public:
	record(QWidget *parent = 0);
	~record();
	void stylesheet();
	void select_identifyLog();
	void select_ShowImg1(const QModelIndex &index);
private slots:
	void select_ShowImg(const QModelIndex &index);
	void Click_Result_Right_Button();
	void Click_Result_Left_Button();
private:
	Ui::record ui;
	int index_Result = 0;							//当前查询信息的页数
	int select_mode = 0;							//查询的模式
	int number_Result = 0;							//总的查询记录数量
};

#endif // RECORD_H
