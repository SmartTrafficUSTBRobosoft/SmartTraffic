#include "cit.h"
#include "record.h"
#include "camera.h"
#include "setting.h"
#include "trafficApplication.h"
#include <QtWidgets/QApplication>
#pragma execution_character_set("utf-8") 
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CIT w;
	//record c;
	//camera b;
	//setting s;
	//trafficApplication t;
	w.setFixedSize(w.width(), w.height());
	w.setWindowTitle(QObject::tr("�������ܽ�ͨ��֪�����ϵͳ"));
	//c.setWindowModality(Qt::ApplicationModal);
	//b.setWindowModality(Qt::ApplicationModal);
	//c.setFixedSize(c.width(), c.height());
	//c.setWindowTitle(QObject::tr("������¼"));
	//b.setFixedSize(b.width(), b.height());
	//b.setWindowTitle(QObject::tr("ʵʱ·��"));
	//s.setWindowTitle(QObject::tr("����"));
	//t.show();
	w.show();
	//c.show();
	//b.show();
	//s.show();
	return a.exec();
}
