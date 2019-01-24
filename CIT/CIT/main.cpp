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
	w.setWindowTitle(QObject::tr("城市智能交通感知与决策系统"));
	//c.setWindowModality(Qt::ApplicationModal);
	//b.setWindowModality(Qt::ApplicationModal);
	//c.setFixedSize(c.width(), c.height());
	//c.setWindowTitle(QObject::tr("车辆记录"));
	//b.setFixedSize(b.width(), b.height());
	//b.setWindowTitle(QObject::tr("实时路况"));
	//s.setWindowTitle(QObject::tr("设置"));
	//t.show();
	w.show();
	//c.show();
	//b.show();
	//s.show();
	return a.exec();
}
