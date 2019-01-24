#pragma once

#include <QWidget>
#include "ui_record2.h"
#include "cit.h"
#include "showimg2.h"

class record2 : public QWidget
{
	Q_OBJECT

public:
	record2(QWidget *parent = Q_NULLPTR);
	~record2();
	void stylesheet();
	void select_identifyLog();
	void select_ShowImg1(const QModelIndex &index);
private slots:
	void select_ShowImg(const QModelIndex &index);
	void Click_Result_Right_Button();
	void Click_Result_Left_Button();

private:
	Ui::record2 ui;
	int index_Result = 0;							//��ǰ��ѯ��Ϣ��ҳ��
	int select_mode = 0;							//��ѯ��ģʽ
	int number_Result = 0;							//�ܵĲ�ѯ��¼����
};
