#ifndef CIT_H
#define CIT_H
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <qdebug.h>
#include <QtWidgets/QMainWindow>
#include "ui_cit.h"
#include <qmessagebox.h>
#include <QtWebEngineWidgets>
#include "record.h"
#include "camera.h"
#include "setting.h"
#include "setting.h"
#include "trafficApplication.h"
#include "yolo_console_dll.h"

extern QString color1;
extern QString color2 ;
extern QString color3 ;
class CIT : public QMainWindow
{
	Q_OBJECT

public:
	CIT(QWidget *parent = 0);
	~CIT();
	QWebEngineView* view;
	void stylesheet();
	int generateRandomNumber(int test);
	int sec;
	int sec2;
	int cartimeCount;
	float cartimePlus;
	int timePlus;
	void startTime2();
	int stopTime2();
	QTimer *timer_1;
	QImage image;
	QTimer *timer_2;
	bool isStart;
	bool isStart2;
private:
	Ui::CITClass ui;
public:
	QPushButton *btnonpic;
	myThread *thread1;
	yolo_console_dll *yolo;

private slots:
    void on_pushButton_14_clicked();					//点击按“文字”查询按键的响应
	bool DataRefresh();
	void Click_pushButton_btnonpic();
	void Click_pushButton_record();
	void Click_pushButton_setting();
	void updateTime();
	void startTime();
	void stopTime();
	void updateTime2();
public slots:
     void refresh_data();

protected:
	void resizeEvent(QResizeEvent *);

};

#endif // CIT_H
