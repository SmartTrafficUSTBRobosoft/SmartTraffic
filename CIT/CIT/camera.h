#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <qdebug.h>
#include "ui_camera.h"
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "myThread.h"
#include "record.h"
#include "record2.h"
#include "GBK.h"
#include <Python.h>
#include<iostream>
#include<windows.h>
#include <QtSql/qsqlquerymodel.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>


class camera : public QWidget
{
	Q_OBJECT

public:
	camera(QWidget *parent = 0);
	~camera();
	void displayMat(cv::Mat frame, int fps);
	QImage  Mat2QImage(cv::Mat cvImg);
	void stylesheet();
	QMediaPlayer* player;
	QVideoWidget* vw;
	QVBoxLayout *layout;
	int generateRandomNumber();
	myThread *thread1;
	yolo_console_dll *yolo;
	QImage image;
	void image_show(int i);
	void car_feature(cv::Mat img);
	void bicycle_feature(cv::Mat img);
	void person_feature(cv::Mat img);
	void insert_carfeature(QString brand, QString type, QString color, QString plate, QString feature, QString picPath, QString identifyDate, QString identifyTime, QString illegal);
	void insert_NonMotofeature(QString poster, QString type, QString color, QString gender, QString age, QString nation, QString headFeature, QString upperbodyFeature, QString picPath, QString illegal, QString identifyDate, QString identifyTime);
	
public slots:
        void Click_pushButton_local();
		void Click_pushButton_local_pause();
		bool DataRefresh1();
		void DataRefresh2();
		void Click_pushButton_record();
		void Click_pushButton_record2();
		void displayslot();
		void Click_pushButton_cam_open();
		void select_carfeature();
		void select_nonmotofeature();

	signals:
		void refresh();
		
private:
	Ui::camera ui;
	QTimer *timer1;
	int i = 0;
	string modelCfg;
	string modelBin;
	string classFilename;
	string classFilename2;
	string classFilename3;
	string classFilename4;

	string modelCfg2;
	string modelBin2;
	string classFilename5;
	string classFilename6;
	QTimer *select_timer;

	QString type;//车型
	QString color ;//颜色
	QString plate;//车牌
};

#endif // CAMERA_H
