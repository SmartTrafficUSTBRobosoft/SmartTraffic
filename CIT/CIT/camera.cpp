
#include "camera.h"
#include "Pipeline.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace pr;
using namespace cv;
#pragma execution_character_set("utf-8") 
int local_state = 0;
QString DataCam[14];
int probability[14];
myThread thread2; //新建线程对象

camera::camera(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_cam->clear();
	ui.comboBox_cam->insertItems(0, QStringList()
		<< QApplication::translate("MainWindowClass", "本地摄像头1", Q_NULLPTR)
		<< QApplication::translate("MainWindowClass", "本地摄像头2", Q_NULLPTR)
		<< QApplication::translate("MainWindowClass", "本地摄像头3", Q_NULLPTR)
		);
	stylesheet();
	timer1 = new QTimer(this);
	connect(timer1, SIGNAL(timeout()), this, SLOT(DataRefresh2()));
	select_timer = new QTimer(this);
	connect(select_timer, SIGNAL(timeout()), this, SLOT(select_carfeature()));
	connect(select_timer, SIGNAL(timeout()), this, SLOT(select_nonmotofeature()));
	//select_timer->start(5000);
	//timer1->start(1000);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(1);
	QVideoWidget* vw = new QVideoWidget();
	vw->resize(ui.label_camera->size());
	layout->addWidget(vw);
	ui.label_camera->setLayout(layout);
	player = new QMediaPlayer();
	player->setVideoOutput(vw);
	qDebug() << "begin";
	vw->show();
	yolo_console_dll *yolo = new yolo_console_dll;
	QObject::connect(yolo, SIGNAL(updatemat()), this, SLOT(displayslot()));

	thread2.yolo1 = yolo;
	//QString path = QFileDialog::getOpenFileName(this, tr("选择视频"), ".", tr("Image Files(*.flv *.mp4)"));//得到视频路径
	//QObject::connect(thread1, SIGNAL(updatematT()), this, SLOT(displayslot()));
	//thread1->start();

	connect(ui.pushButton_local, SIGNAL(clicked()), this, SLOT(Click_pushButton_local()));
	connect(ui.pushButton_local_pause, SIGNAL(clicked()), this, SLOT(Click_pushButton_local_pause()));
	connect(ui.pushButton_record1, SIGNAL(clicked()), this, SLOT(Click_pushButton_record()));
	connect(ui.pushButton_record2, SIGNAL(clicked()), this, SLOT(Click_pushButton_record2()));
	connect(ui.pushButton_cam_open, SIGNAL(clicked()), this, SLOT(Click_pushButton_cam_open()));

}

camera::~camera()
{

}
void camera::Click_pushButton_record()
{

	record *r = new record();
	//r->setWindowModality(Qt::ApplicationModal);
	r->setFixedSize(r->width(), r->height());
	r->setWindowTitle(QObject::tr("车辆记录"));
	r->show();
}
void camera::Click_pushButton_record2()
{

	record2 *r = new record2();
	//r->setWindowModality(Qt::ApplicationModal);
	r->setFixedSize(r->width(), r->height());
	r->setWindowTitle(QObject::tr("车辆记录"));
	r->show();
}
bool camera::DataRefresh1()
{
	generateRandomNumber();
	ui.Label_W1_1->setText(DataCam[0]);
	ui.Label_W1_2->setText(DataCam[1]);
	ui.Label_W1_3->setText(DataCam[2]);
	ui.Label_W1_4->setText(DataCam[3]);
	ui.Label_W1_5->setText(DataCam[4]);
	//ui.Label_W1_6->setText(DataCam[5]);
	ui.Label_W2_1->setText(DataCam[6]);
	ui.Label_W2_2->setText(DataCam[7]);
	ui.Label_W2_3->setText(DataCam[8]);
	ui.Label_W2_4->setText(DataCam[9]);
	ui.Label_W2_5->setText(DataCam[10]);
	ui.Label_W2_6->setText(DataCam[11]);
	ui.Label_W2_7->setText(DataCam[12]);
	ui.Label_W2_8->setText(DataCam[13]);
	return true;

}
void camera::DataRefresh2()
{
	i++;

	switch (i)
	{
	case 1:
		image_show(1);
		break;
	case 2:
		image_show(2);
		break;
	case 3:
		image_show(3);
		break;
	case 4:
		image_show(4);
		break;
	case 5:
		image_show(5);
		i = 0;
		break;
	}
}
void camera::image_show(int i)
{
	QString path1 = "car1.jpg";
	QString path2 = "bike1.jpg";
	QString path3 = "car2.jpg";
	QString path4 = "bike2.png";
	QString path5 = "car3.jpg";
	QString path6 = "bike3.png";
	QString path7 = "car4.jpg";
	QString path8 = "bike1.jpg";
	QString path9 = "car5.jpg";
	QString path10 = "bike1.jpg";

	if (i == 1)
	{
		cv::Mat image = cv::imread(GBK::FromUnicode(path1));
		cv::cvtColor(image, image, CV_BGR2RGB);
		QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
		QPixmap pixmap = QPixmap::fromImage(img).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_1->setPixmap(pixmap);
		ui.Label_W1_1->setText("无");//特征
		ui.Label_W1_2->setText("黑色");//车身颜色
		ui.Label_W1_3->setText("SUV");//车型
		ui.Label_W1_4->setText("京PF3691");//车牌号码
		ui.Label_W1_5->setText("别克");//品牌
		ui.Label_W1_6->setText("无");//违法情况
		cv::Mat image2 = cv::imread(GBK::FromUnicode(path2));
		cv::cvtColor(image2, image2, CV_BGR2RGB);
		QImage img2 = QImage((const unsigned char*)(image2.data), image2.cols, image2.rows, image2.cols*image2.channels(), QImage::Format_RGB888);
		QPixmap pixmap2 = QPixmap::fromImage(img2).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_2->setPixmap(pixmap2);
		ui.Label_W2_1->setText("电动车");//车型
		ui.Label_W2_2->setText("15-30岁");//民族
		ui.Label_W2_3->setText("正向");//姿态
		ui.Label_W2_4->setText("黑色眼镜");//头部特征
		ui.Label_W2_5->setText("红色");//颜色
		ui.Label_W2_6->setText("白色衬衫");//上身特征
		ui.Label_W2_7->setText("男");//性别
		ui.Label_W2_8->setText("正常");//安全识别

	}
	if (i == 2)
	{
		cv::Mat image3 = cv::imread(GBK::FromUnicode(path3));
		cv::cvtColor(image3, image3, CV_BGR2RGB);
		QImage img3 = QImage((const unsigned char*)(image3.data), image3.cols, image3.rows, image3.cols*image3.channels(), QImage::Format_RGB888);
		QPixmap pixmap3 = QPixmap::fromImage(img3).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_1->setPixmap(pixmap3);
		ui.Label_W1_1->setText("无");//特征
		ui.Label_W1_2->setText("棕色");//车身颜色
		ui.Label_W1_3->setText("SUV");//车型
		ui.Label_W1_4->setText("无");//车牌号码
		ui.Label_W1_5->setText("宝马");//品牌
		ui.Label_W1_6->setText("遮挡车牌");//违法情况
		cv::Mat image4 = cv::imread(GBK::FromUnicode(path4));
		cv::cvtColor(image4, image4, CV_BGR2RGB);
		QImage img4 = QImage((const unsigned char*)(image4.data), image4.cols, image4.rows, image4.cols*image4.channels(), QImage::Format_RGB888);
		QPixmap pixmap4 = QPixmap::fromImage(img4).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_2->setPixmap(pixmap4);
		ui.Label_W2_1->setText("电动车");//车型
		ui.Label_W2_2->setText("30-45岁");//民族
		ui.Label_W2_3->setText("正向");//姿态
		ui.Label_W2_4->setText("短发");//头部特征
		ui.Label_W2_5->setText("黑色");//颜色
		ui.Label_W2_6->setText("黑色上衣");//上身特征
		ui.Label_W2_7->setText("男");//性别
		ui.Label_W2_8->setText("正常");//安全识别

	}
	if (i == 3)
	{
		cv::Mat image5 = cv::imread(GBK::FromUnicode(path5));
		cv::cvtColor(image5, image5, CV_BGR2RGB);
		QImage img5 = QImage((const unsigned char*)(image5.data), image5.cols, image5.rows, image5.cols*image5.channels(), QImage::Format_RGB888);
		QPixmap pixmap5 = QPixmap::fromImage(img5).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_1->setPixmap(pixmap5);
		ui.Label_W1_1->setText("无");//特征
		ui.Label_W1_2->setText("银色");//车身颜色
		ui.Label_W1_3->setText("sedan");//车型
		ui.Label_W1_4->setText("新AB3857");//车牌号码
		ui.Label_W1_5->setText("马自达");//品牌
		ui.Label_W1_6->setText("无");//违法情况
		cv::Mat image6 = cv::imread(GBK::FromUnicode(path6));
		cv::cvtColor(image6, image6, CV_BGR2RGB);
		QImage img6 = QImage((const unsigned char*)(image6.data), image6.cols, image6.rows, image6.cols*image6.channels(), QImage::Format_RGB888);
		QPixmap pixmap6 = QPixmap::fromImage(img6).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_2->setPixmap(pixmap6);
		ui.Label_W2_1->setText("电动车");//车型
		ui.Label_W2_2->setText("30-45岁");//民族
		ui.Label_W2_3->setText("正向");//姿态
		ui.Label_W2_4->setText("短发");//头部特征
		ui.Label_W2_5->setText("红色");//颜色
		ui.Label_W2_6->setText("黑色上衣");//上身特征
		ui.Label_W2_7->setText("男");//性别
		ui.Label_W2_8->setText("正常");//安全识别

	}
	if (i == 4)
	{
		cv::Mat image7 = cv::imread(GBK::FromUnicode(path7));
		cv::cvtColor(image7, image7, CV_BGR2RGB);
		QImage img7 = QImage((const unsigned char*)(image7.data), image7.cols, image7.rows, image7.cols*image7.channels(), QImage::Format_RGB888);
		QPixmap pixmap7 = QPixmap::fromImage(img7).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_1->setPixmap(pixmap7);
		ui.Label_W1_1->setText("无");//特征
		ui.Label_W1_2->setText("白色");//车身颜色
		ui.Label_W1_3->setText("SUV");//车型
		ui.Label_W1_4->setText("新P11157");//车牌号码
		ui.Label_W1_5->setText("丰田");//品牌
		ui.Label_W1_6->setText("无");//违法情况
		cv::Mat image8 = cv::imread(GBK::FromUnicode(path8));
		cv::cvtColor(image8, image8, CV_BGR2RGB);
		QImage img8 = QImage((const unsigned char*)(image8.data), image8.cols, image8.rows, image8.cols*image8.channels(), QImage::Format_RGB888);
		QPixmap pixmap8 = QPixmap::fromImage(img8).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_2->setPixmap(pixmap8);
		ui.Label_W2_1->setText("电动车");//车型
		ui.Label_W2_2->setText("30-45岁");//民族
		ui.Label_W2_3->setText("正向");//姿态
		ui.Label_W2_4->setText("黑色眼镜");//头部特征
		ui.Label_W2_5->setText("红色");//颜色
		ui.Label_W2_6->setText("白色衬衫");//上身特征
		ui.Label_W2_7->setText("男");//性别
		ui.Label_W2_8->setText("正常");//安全识别

	}
	if (i == 5)
	{
		cv::Mat image9 = cv::imread(GBK::FromUnicode(path9));
		cv::cvtColor(image9, image9, CV_BGR2RGB);
		QImage img9 = QImage((const unsigned char*)(image9.data), image9.cols, image9.rows, image9.cols*image9.channels(), QImage::Format_RGB888);
		QPixmap pixmap9 = QPixmap::fromImage(img9).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_1->setPixmap(pixmap9);
		ui.Label_W1_1->setText("无");//特征
		ui.Label_W1_2->setText("蓝色");//车身颜色
		ui.Label_W1_3->setText("SUV");//车型
		ui.Label_W1_4->setText("新K25517");//车牌号码
		ui.Label_W1_5->setText("不详");//品牌
		ui.Label_W1_6->setText("未系安全带");//违法情况
		cv::Mat image10 = cv::imread(GBK::FromUnicode(path10));
		cv::cvtColor(image10, image10, CV_BGR2RGB);
		QImage img10 = QImage((const unsigned char*)(image10.data), image10.cols, image10.rows, image10.cols*image10.channels(), QImage::Format_RGB888);
		QPixmap pixmap10 = QPixmap::fromImage(img10).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
		ui.label_pic_2->setPixmap(pixmap10);
		ui.Label_W2_1->setText("电动车");//车型
		ui.Label_W2_2->setText("30-45岁");//民族
		ui.Label_W2_3->setText("正向");//姿态
		ui.Label_W2_4->setText("黑色眼镜");//头部特征
		ui.Label_W2_5->setText("红色");//颜色
		ui.Label_W2_6->setText("白色衬衫");//上身特征
		ui.Label_W2_7->setText("男");//性别
		ui.Label_W2_8->setText("正常");//安全识别

	}

}
int camera::generateRandomNumber()

{
	int i, j; 
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	for (int i = 0; i < 14; i++)
	{
		probability[i] = qrand() % 100;
		//qDebug()<<probability[i];
		if (i == 0)
		{
			DataCam[i] = "未知";
		}
		if (i == 1)
		{
			if (probability[i] <= 20)
			{
				DataCam[i] = "红";
			}
			else if (probability[i] <= 40)
			{
				DataCam[i] = "黄";
			}
			else if (probability[i] <= 60)
			{
				DataCam[i] = "蓝";
			}
			else if (probability[i] <= 80)
			{
				DataCam[i] = "绿";
			}
			else if (probability[i] <= 100)
			{
				DataCam[i] = "黑";
			}
		}
		if (i == 2)
		{
			DataCam[i] = "未知";
		}
		if (i == 3)
		{
			DataCam[i] = "未知";
		}
	
		if (i == 4)//logo
		{
			if (probability[i] <= 13)
			{
				DataCam[i] = "大众";
			}
			else if (probability[i] <= 25)
			{
				DataCam[i] = "丰田";
			}
			else if (probability[i] <= 38)
			{
				DataCam[i] = "奥迪";
			}
			else if (probability[i] <= 50)
			{
				DataCam[i] = "奔驰";
			}
			else if (probability[i] <= 68)
			{
				DataCam[i] = "现代";
			}
			else if (probability[i] <= 75)
			{
				DataCam[i] = "别克";
			}
			else if (probability[i] <= 88)
			{
				DataCam[i] = "吉利";
			}
			else if (probability[i] <= 100)
			{
				DataCam[i] = "宝马";
			}
			
		}
		if (i == 5)
		{
			DataCam[i] = "未知";
		}
		if (i == 6)
		{
			DataCam[i] = "未知";
		}
		if (i == 7)
		{
			DataCam[i] = "未知";
		}
		if (i == 8)
		{
			DataCam[i] = "未知";
		}
		if (i == 9)
		{
			DataCam[i] = "未知";
		}
		if (i == 10)
		{
			if (probability[i] <= 20)
			{
				DataCam[i] = "红";
			}
			else if (probability[i] <= 40)
			{
				DataCam[i] = "黄";
			}
			else if (probability[i] <= 60)
			{
				DataCam[i] = "蓝";
			}
			else if (probability[i] <= 80)
			{
				DataCam[i] = "绿";
			}
			else if (probability[i] <= 100)
			{
				DataCam[i] = "黑";
			}

		}
		if (i == 11)
		{
			DataCam[i] = "未知";
		}
		if (i == 12)
		{
			if (probability[i] <= 50)
			{
				DataCam[i] = "男";
			}
			else if (probability[i] <= 100)
			{
				DataCam[i] = "女";
			}
		}
		if (i == 13)
		{
			DataCam[i] = "未知";
		}
	}
	//Data[i] = QString::number(qrand() % 100);

	return 0;

}

void camera::Click_pushButton_local()//演示版本
{
	thread2.start();
	//QString path = QFileDialog::getOpenFileName(this, tr("选择视频"), ".", tr("Image Files(*.flv *.mp4 *.avi)"));//得到视频路径
	//QString path = "./result.avi";//演示视频
	//player->setMedia(QUrl::fromLocalFile((path)));
	//player->play();
	//timer1->start(5000);
	//DataRefresh2();

}
void camera::Click_pushButton_local_pause()
{

	//if (local_state == 1)
	//{
	stopornot = false;
		//player->pause();
		local_state = 0;
	//}
	//else
	//{
		//player->play();
		local_state = 1;

	//}

}
void camera::stylesheet()
{
	QPalette palette(this->palette());
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(248, 248, 248, 248));	
	this->setPalette(palette);

	QStringList qssbtn;//按钮


	qssbtn.append(QString(
		"QPushButton:!enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid #AAAAAA;background:#e1e1e1;color:#777777} "
		"QPushButton:enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid %1;background:%1;color:#FFFFFF} "
		"QPushButton:hover {border-style:none;padding:2px;border-radius:5px;border:2px solid %2;background:%2;color:#FFFFFF}"
		"QPushButton:pressed{border-style:none;padding:2px;border-radius:5px;border:2px solid %3;background:%3;color:#FFFFFF}"
		).arg(color1).arg(color2).arg(color3));
	
	ui.pushButton_cam_open->setStyleSheet(qssbtn.join(""));
	ui.pushButton_cam_close->setStyleSheet(qssbtn.join(""));
	ui.pushButton_record1->setStyleSheet(qssbtn.join(""));
	ui.pushButton_record2->setStyleSheet(qssbtn.join(""));
	ui.pushButton_local->setStyleSheet(qssbtn.join(""));
	ui.pushButton_local_pause->setStyleSheet(qssbtn.join(""));

	
	
	QStringList qss;//文本框显示
	qss.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:5px;border:2px solid %1;}").arg("#555555"));
	qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg("#555555"));

	//ui.lineEdit->setStyleSheet(qss.join(""));
	//ui.lineEdit_2->setStyleSheet(qss.join(""));
	//ui.lineEdit_3->setStyleSheet(qss.join(""));
	//ui.lineEdit_4->setStyleSheet(qss.join(""));


	QStringList qsstext;//文本框交互
	qsstext.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:5px;border:2px solid %1;}").arg(color1));
	qsstext.append(QString("QLineEdit:focus{border:2px solid %1;}").arg("#996666"));
	qsstext.append(QString("QLineEdit:font:12pt '黑体';"));
	QFont font_1;
	font_1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font_1.setPointSize(9);
	font_1.setBold(false);
	font_1.setItalic(false);
	font_1.setWeight(45);


	QStringList qsstable;
	qsstable.append(QString(""
		"QTableView{ "
		"color: rgb(0, 0, 0);  "
		"border: 2px solid %1;          /*边框颜色*/  "
		"gridline-color:#ffffff;             /*grid线颜色*/  "
		"background-color: rgb(255, 255, 255);  "
		"alternate-background-color: #F5F5F5; /*行交替颜色*/ "
		"selection-background-color: rgb(130, 190, 100); /*选中行背景颜色*/  "
		" }  "

		" QTableView::item:!alternate:!selected{  "
		"  background-color:#d4e8c5;    /*交替行的另一颜色*/ "
		" }  }").arg("#999999"));

	//ui.tableWidget->verticalHeader()->hide();
	//ui.tableWidget_2->setStyleSheet(QString("background-color: %1").arg(color1));

	QFont font;
	font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font.setPointSize(14);
	font.setBold(true);
	font.setItalic(false);
	font.setWeight(75);

	ui.label_7->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_7->setFont(font);
	ui.label_8->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_8->setFont(font);
	ui.label_9->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_9->setFont(font);


	QFont font1;
	font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font1.setPointSize(12);
	font1.setBold(true);
	font1.setWeight(75);






	QStringList qss1;//选择
	qss1.append(QString(("QComboBox{"          //选择框  
		" border: 2px solid %1;;"
		" border-radius: 5px;"
		"padding: 1px 2px 1px 2px;"
		" min-width: 4em; "
		"}"
		"QComboBox QAbstractItemView::item {min-height: 30px;}" //下拉选项高度
		"QComboBox::down-arrow{border-image:url(:/CIT/Resources/arrow_down_gray.png);}" //下拉箭头
		"QComboBox::drop-down {"
		"subcontrol-origin: padding;"
		" subcontrol-position: top right;"
		" width: 20px;"
		" border-left-width: 1px;"
		"border-left-color: darkgray;"
		"border-left-style: solid; /* just a single line */"
		"border-top-right-radius: 3px; /* same radius as the QComboBox */"
		" border-bottom-right-radius: 3px;"
		" }"
		" }"
		"QComboBox:focus{border: 2px solid #996666;}"
		)).arg(color1));
	ui.comboBox_cam->setStyleSheet(qss1.join(""));




	ui.label_1->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_2->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_10->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_6->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 3px;border: 2px solid %1;}").arg(color1));
	ui.label_15->setStyleSheet(QString::fromUtf8("QFrame{border-radius:3px;border: 2px solid %1;}").arg(color1));
	ui.label_17->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 3px;border: 2px solid %1;}").arg(color1));

}

void camera::displayslot()
{
	//qDebug("FPS:123");
	displayMat(mat, fps);
	emit refresh();
}

void camera::displayMat(cv::Mat frame, int fps)
{
	float space_occupancy;
	float car_spacing;
	if (!frame.empty())
	{
		if (frame.u != NULL)
		{
			image = Mat2QImage(frame);
			QImage newImg = image.scaled(ui.label_camera->width(), ui.label_camera->height());
			space_occupancy = 4.5*traffic_density / 10;
			if (traffic_density != 0)
				car_spacing = 1000 / (float)traffic_density - 4.5;
			else
				car_spacing = 25;

			ui.label_camera->setPixmap(QPixmap::fromImage(newImg));
			//ui->label_2->setText("Traffic Density:\n" + QString::number(traffic_density));
			//ui->label_3->setText("Car Count:\n" + QString::number(carcount) + "\n" + "Space Occupancy:\n" + QString::number(space_occupancy) + "\n" + "Car Spacing:\n" + QString::number(car_spacing));
		}
	}
}

QImage  camera::Mat2QImage(cv::Mat cvImg)
{
	QImage qImg;
	if (cvImg.channels() == 3)                             //3 channels color image
	{

		cv::cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1)                    //grayscale image
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_Indexed8);
	}
	else
	{
		qImg = QImage((const unsigned char*)(cvImg.data),
			cvImg.cols, cvImg.rows,
			cvImg.cols*cvImg.channels(),
			QImage::Format_RGB888);
	}

	return qImg;

}

void camera::Click_pushButton_cam_open()  //手动选择图片进行车辆细粒度识别并录入数据库
{
	
	QString path = QFileDialog::getOpenFileName(this, tr("选择图片"), ".", tr("Image Files(*.jpg *.png)"));//得到图片路径
	if (path.isEmpty())
	{
		QMessageBox::warning(this, tr("警告"), tr("路径不能为空"));
		return;
	}
	
	cv::Mat image = cv::imread(GBK::FromUnicode(path));
	if (image.empty())
	{
		QMessageBox::warning(this, tr("警告"), tr("图片不能为空"));
		return;
	}
	//car_feature(image);//识别车辆特征并录入数据库
	//person_feature(image);//识别非机动车和乘客特征并录入数据库
	bicycle_feature(image);
	
}

void camera::car_feature(Mat img)//机动车辆特征
{
	pr::PipelinePR prc("../lpr/model/cascade.xml",
		"../lpr/model/HorizonalFinemapping.prototxt", "../lpr/model/HorizonalFinemapping.caffemodel",
		"../lpr/model/Segmentation.prototxt", "../lpr/model/Segmentation.caffemodel",
		"../lpr/model/CharacterRecognization.prototxt", "../lpr/model/CharacterRecognization.caffemodel"
	);

	std::vector<pr::PlateInfo> res = prc.RunPiplineAsImage(img);
	float conf = 0;
	for (auto st : res) {
		if (st.confidence>0.1) {
			std::cout << st.getPlateName() << " " << st.confidence << std::endl;
			ui.Label_W1_4->setText(GBK::ToUnicode(st.getPlateName()));
			plate = GBK::ToUnicode(st.getPlateName());//车牌
			conf += st.confidence;
		}
	}

	//cv::imshow("image", image);
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	QString qDate = time.toString("yyyy-MM-dd"); //设置显示格式
	QString qTime = time.toString("hhmmsszzz");
	QString qTime2 = time.toString("hh:mm:ss");
	QDir temp;
	temp.mkpath(".\\record\\car_identify\\" + qDate);
	QTextCodec *code = QTextCodec::codecForName("UTF-8");
	string sDate = code->fromUnicode(qDate).data();
	string sTime = code->fromUnicode(qTime).data();
	string sTime2 = code->fromUnicode(qTime2).data();
	string pic_Path = "./record/car_identify/" + sDate + "/" + sTime + ".jpg";
	cv::imwrite(pic_Path, img);

	cv::cvtColor(img, img, CV_BGR2RGB);
	QImage img_show = QImage((const unsigned char*)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_RGB888);
	QPixmap pixmap = QPixmap::fromImage(img_show).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
	ui.label_pic_1->setPixmap(pixmap);
	

	
	//cvSaveImage(pic_Path.c_str(), &IplImage(img));
	QString path = GBK::ToUnicode(pic_Path);
	//调用tensorflow模型
	/**********调用颜色模型***********/
	QByteArray ba = path.toLatin1();
	char *path2 = ba.data();
	Py_Initialize();
	PyEval_InitThreads();
	PyObject*pFunc = NULL;
	PyObject*pArg = NULL;
	PyObject* module = NULL;
	PyObject *result = NULL;
	/***********************/
	/*********调用车型模型**********/
	PyObject*pFunc2 = NULL;
	PyObject*pArg2 = NULL;
	PyObject* module2 = NULL;
	PyObject *result2 = NULL;
	/*******************/
	/********************/
	module = PyImport_ImportModule("color_prediction");//myModel:Python文件名  
	if (!module)
	{
		printf("cannot open module!");
		Py_Finalize();
		return;
	}
	pFunc = PyObject_GetAttrString(module, "test_one_image");//test_one_image:Python文件中的函数名
	if (!pFunc)
	{
		printf("cannot open FUNC!");
		Py_Finalize();
		return;
	}
	//开始调用model  
	pArg = Py_BuildValue("(s)", path2);
	if (module != NULL)
	{
		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();
		//result=PyEval_CallObject(pFunc, pArg);
		result = PyObject_CallObject(pFunc, pArg);//调用函数
												  //c用来保存c/c++类型的返回值
		char* c;
		//将python类型的返回值转换为c/c++类型
		PyArg_Parse(result, "s", &c);
		//PyArg_ParseTuple(result, "s", &c);
		//输出返回值
		printf("%s", c);
		QString c_s = QString(QLatin1String(c));

		if (c_s == "champagne")
		{
			ui.Label_W1_2->setText("香槟色");
		}
		if (c_s == "blue")
		{
			ui.Label_W1_2->setText("蓝色");
		}
		if (c_s == "green")
		{
			ui.Label_W1_2->setText("绿色");
		}
		if (c_s == "black")
		{
			ui.Label_W1_2->setText("黑色");
		}
		if (c_s == "brown")
		{
			ui.Label_W1_2->setText("棕色");
		}
		if (c_s == "purple")
		{
			ui.Label_W1_2->setText("紫色");
		}
		if (c_s == "red")
		{
			ui.Label_W1_2->setText("红色");
		}
		if (c_s == "silvery")
		{
			ui.Label_W1_2->setText("银色");
		}
		if (c_s == "white")
		{
			ui.Label_W1_2->setText("白色");
		}
		if (c_s == "yellow")
		{
			ui.Label_W1_2->setText("黄色");
		}
		//ui.Label_W1_2->setText(QString(QLatin1String(c)));
		color = ui.Label_W1_2->text();
		PyGILState_Release(gstate);
	}
	/*****************************/
	/****************************/
	module2 = PyImport_ImportModule("type_prediction");//myModel:Python文件名  
	if (!module2)
	{
		printf("cannot open module2!");
		Py_Finalize();
		return;
	}
	pFunc2 = PyObject_GetAttrString(module2, "test_one_image");//test_one_image:Python文件中的函数名
	if (!pFunc2)
	{
		printf("cannot open FUNC2!");
		Py_Finalize();
		return;
	}
	//开始调用model  
	pArg2 = Py_BuildValue("(s)", path2);
	if (module2 != NULL)
	{
		PyGILState_STATE gstate2;
		gstate2 = PyGILState_Ensure();
		//result=PyEval_CallObject(pFunc, pArg);
		result2 = PyObject_CallObject(pFunc2, pArg2);//调用函数
													 //c用来保存c/c++类型的返回值
		char* c2;
		//将python类型的返回值转换为c/c++类型
		PyArg_Parse(result2, "s", &c2);
		//PyArg_ParseTuple(result, "s", &c);
		//输出返回值
		printf("%s", c2);
		type = QString(QLatin1String(c2));//车型
		ui.Label_W1_3->setText(QString(QLatin1String(c2)));
		PyGILState_Release(gstate2);
	}
	/*********车辆主品牌识别部分***********/
	QString brand = "奥迪";//车辆品牌
	
	/*************************************/
	QString picPath = GBK::ToUnicode(pic_Path);//图片路径
	QString identifyDate =GBK::ToUnicode(sDate) ;//识别日期
	QString identifyTime = GBK::ToUnicode(sTime2);//识别时间
	QString feature = "无";//车辆特征
	QString illegal = "无";//车辆违法
	insert_carfeature(brand, type, color,  plate,  feature, picPath,  identifyDate,  identifyTime,  illegal);

}
void camera::bicycle_feature(Mat img)//非机动车辆特征
{
	String label_file = "color_classes.txt";
	String tf_pb_file = "new_tensor_model.pb";
	vector<string>classNamesVec;
	classNamesVec.clear();
	ifstream classNamesFile(label_file);
	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(tf_pb_file);
	vector<String> layersNames = net.getLayerNames();
	cv::Mat inputBlob = dnn::blobFromImage(img, 1.0f, Size(224, 224), Scalar(), true, false); //Convert Mat to batch of images
	net.setInput(inputBlob);                   //set the network input
	Mat probMat = net.forward();   //compute output

	Point classNumber;
	int classId;
	double classProb;
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	classId = classNumber.x;
	cout << classNamesVec.at(classId);//品牌
									  //string PP = classNamesVec.at(classId);
}
void camera::person_feature(Mat img)//行人特征
{
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	QString qDate = time.toString("yyyy-MM-dd"); //设置显示格式
	QString qTime = time.toString("hhmmsszzz");
	QString qTime2 = time.toString("hh:mm:ss");
	QDir temp;
	temp.mkpath(".\\record\\person_identify\\" + qDate);
	QTextCodec *code = QTextCodec::codecForName("UTF-8");
	string sDate = code->fromUnicode(qDate).data();
	string sTime = code->fromUnicode(qTime).data();
	string sTime2 = code->fromUnicode(qTime2).data();
	string pic_Path = "./record/person_identify/" + sDate + "/" + sTime + ".jpg";
	//cvSaveImage(pic_Path.c_str(), &IplImage(img));
	cv::imwrite(pic_Path, img);

	cv::cvtColor(img, img, CV_BGR2RGB);
	QImage img2 = QImage((const unsigned char*)(img.data), img.cols, img.rows, img.cols*img.channels(), QImage::Format_RGB888);
	QPixmap pixmap2 = QPixmap::fromImage(img2).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
	ui.label_pic_2->setPixmap(pixmap2);
	/*****************************/
	modelCfg = "deploy2.prototxt";
	modelBin = "train_iter_10000.caffemodel";
	classFilename = "Age.txt";
	classFilename2 = "Hair.txt";
	classFilename3 = "Gender.txt";
	classFilename4 = "upperBody.txt";

	vector<string>classNamesVec;

	classNamesVec.clear();
	ifstream classNamesFile(classFilename);
	if (classNamesFile.is_open())
	{
		string className = "";
		while (std::getline(classNamesFile, className))
			classNamesVec.push_back(className);
	}

	vector<string>classNamesVec2;

	classNamesVec2.clear();
	ifstream classNamesFile2(classFilename2);
	if (classNamesFile2.is_open())
	{
		string className2 = "";
		while (std::getline(classNamesFile2, className2))
			classNamesVec2.push_back(className2);
	}

	vector<string>classNamesVec3;

	classNamesVec3.clear();
	ifstream classNamesFile3(classFilename3);
	if (classNamesFile3.is_open())
	{
		string className3 = "";
		while (std::getline(classNamesFile3, className3))
			classNamesVec3.push_back(className3);
	}

	vector<string>classNamesVec4;

	classNamesVec4.clear();
	ifstream classNamesFile4(classFilename4);
	if (classNamesFile4.is_open())
	{
		string className4 = "";
		while (std::getline(classNamesFile4, className4))
			classNamesVec4.push_back(className4);
	}

	//cvtColor(image, image, COLOR_BGRA2BGR);
	cv::dnn::Net net = cv::dnn::readNetFromCaffe(modelCfg, modelBin);
	vector<String> layersNames = net.getLayerNames();
	cv::Mat inputBlob = dnn::blobFromImage(img, 1.0f, Size(227, 227), Scalar(), true, false); //Convert Mat to batch of images
	net.setInput(inputBlob);                   //set the network input
	Mat probMat = net.forward("prob_1_Age");   //compute output
	Mat probMat2 = net.forward("prob_2_Hair");   //compute output
	Mat probMat3 = net.forward("prob_3_Gender");   //compute output
	Mat probMat4 = net.forward("prob_4_upperbody");   //compute output

	Point classNumber;
	int classId;
	double classProb;
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	classId = classNumber.x;
	cout << classNamesVec.at(classId);//年龄
	string age = classNamesVec.at(classId);
	if (age == "personalLess15")
	{
		ui.Label_W2_2->setText("15岁以下");

	}
	if (age == "personalLess30")
	{
		ui.Label_W2_2->setText("15-30岁");
	}
	if (age == "personalLess45")
	{
		ui.Label_W2_2->setText("30-45岁");
	}
	if (age == "personalLess60")
	{
		ui.Label_W2_2->setText("45-60岁");
	}
	if (age == "personalLarger60")
	{
		ui.Label_W2_2->setText("60岁以上");
	}
	//cout << classProb;

	Point classNumber2;
	int classId2;
	double classProb2;
	minMaxLoc(probMat2, NULL, &classProb2, NULL, &classNumber2);
	classId2 = classNumber2.x;
	cout << classNamesVec2.at(classId2);//头发
	string hair = classNamesVec2.at(classId2);
	if (hair == "hairShort")
	{
		ui.Label_W2_4->setText("短发");
	}
	if (hair == "hairLong")
	{
		ui.Label_W2_4->setText("长发");
	}
	if (hair == "hairBald")
	{
		ui.Label_W2_4->setText("秃发");
	}
	//cout << classProb2;

	Point classNumber3;
	int classId3;
	double classProb3;
	minMaxLoc(probMat3, NULL, &classProb3, NULL, &classNumber3);
	classId3 = classNumber3.x;
	//cout << classNamesVec3.at(classId3);//性别
	string gender = classNamesVec3.at(classId3);
	if (gender == "personalMale")
	{
		ui.Label_W2_7->setText("男");
	}
	else
	{
		ui.Label_W2_7->setText("女");
	}
	//cout << classProb3;

	Point classNumber4;
	int classId4;
	double classProb4;
	minMaxLoc(probMat4, NULL, &classProb4, NULL, &classNumber4);
	classId4 = classNumber4.x;
	cout << classNamesVec4.at(classId4);//上身特征
	string upperbody = classNamesVec4.at(classId4);
	if (upperbody == "upperbodyBlack")
	{
		ui.Label_W2_6->setText("上身黑色");
	}
	if (upperbody == "upperbodyBlue")
	{
		ui.Label_W2_6->setText("上身蓝色");
	}
	if (upperbody == "upperbodyBrown")
	{
		ui.Label_W2_6->setText("上身棕色");
	}
	if (upperbody == "upperbodyGreen")
	{
		ui.Label_W2_6->setText("上身绿色");
	}
	if (upperbody == "upperbodyGrey")
	{
		ui.Label_W2_6->setText("上身灰色");
	}
	if (upperbody == "upperbodyOrange")
	{
		ui.Label_W2_6->setText("上身橙色");
	}
	if (upperbody == "upperbodyPink")
	{
		ui.Label_W2_6->setText("上身粉色");
	}
	if (upperbody == "upperbodyPurple")
	{
		ui.Label_W2_6->setText("上身紫色");
	}
	if (upperbody == "upperbodyRed")
	{
		ui.Label_W2_6->setText("上身红色");
	}
	if (upperbody == "upperbodyWhite")
	{
		ui.Label_W2_6->setText("上身白色");
	}
	if (upperbody == "upperbodyYellow")
	{
		ui.Label_W2_6->setText("上身黄色");
	}
	if (upperbody == "upperBodyMixture")
	{
		ui.Label_W2_6->setText("上身混合色");
	}
	//cout << classProb4;
	QString poster = "正向";
	QString type = "电动车";
	QString color = "黑色";
	QString nation = "汉族";
	QString qage = ui.Label_W2_2->text();
	QString qgender = ui.Label_W2_7->text();
	QString headFeature = ui.Label_W2_4->text();
	QString illegal = "安全";
	QString upperbodyFeature = ui.Label_W2_6->text();
	QString picPath = GBK::ToUnicode(pic_Path);//图片路径
	QString identifyDate = GBK::ToUnicode(sDate);//识别日期
	QString identifyTime = GBK::ToUnicode(sTime2);//识别时间
	insert_NonMotofeature( poster,  type,  color, qgender, qage,  nation,  headFeature,  upperbodyFeature,  picPath,  illegal,  identifyDate, identifyTime);
}

void camera::insert_carfeature(QString brand, QString type, QString color, QString plate, QString feature, QString picPath, QString identifyDate, QString identifyTime,QString illegal )
{
	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		QSqlQuery sql_query;
		QString insert_sql = "insert into carHistory(brand, type, color, plate, feature, picPath, identifyDate,identifyTime,illegal) values('" +
			brand + "','" + type + "','" + color+ "','" + plate + "','" + feature + "','" + picPath+ "','" + identifyDate + "','" + identifyTime + "','"+illegal+"')";
		sql_query.prepare(insert_sql);
		if (!sql_query.exec())
		{
			qDebug() << "insert error";
		}
		else
		{
			qDebug() << "insert success!";
		}

	}
	d.close();
}
void camera::insert_NonMotofeature(QString poster,QString type,QString color,QString gender,QString age,QString nation,QString headFeature,QString upperbodyFeature,QString picPath,QString illegal, QString identifyDate, QString identifyTime)
{
	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		QSqlQuery sql_query;
		QString insert_sql = "insert into NonmotoHistory(posture, type, color, gender, age, nation,headFeature,upperbodyFeature,picPath, identifyDate,identifyTime,illegal) values('" +
			poster + "','" + type + "','" + color + "','" + gender + "','" + age + "','" + nation + "','" + headFeature + "','" + upperbodyFeature + "','" + picPath + "','" + identifyDate + "','" + identifyTime + "','" + illegal + "')";
		sql_query.prepare(insert_sql);
		if (!sql_query.exec())
		{
			qDebug() << "insert error";
		}
		else
		{
			qDebug() << "insert success!";
		}

	}
	d.close();
}
void camera::select_carfeature()
{
	QString brand;
	QString type;
	QString color;
	QString plate;
	QString feature;
	QString picPath;
	QString illegal;
	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		QSqlQuery sql_query;
		QString select_sql = "select brand,type,color,plate,feature,picPath,illegal from carHistory order by ID desc limit 1 offset 0";
		sql_query.prepare(select_sql);
		if (!sql_query.exec())
		{
			qDebug() << "select error";
		}
		else
		{
			while (sql_query.next())
			{
				brand = sql_query.value("brand").toString();
				type = sql_query.value("type").toString();
				color = sql_query.value("color").toString();
				plate = sql_query.value("plate").toString();
				feature = sql_query.value("feature").toString();
				picPath = sql_query.value("picPath").toString();
				illegal = sql_query.value("illegal").toString();
			
			}
			cv::Mat image9 = cv::imread(GBK::FromUnicode(picPath));
			cv::cvtColor(image9, image9, CV_BGR2RGB);
			QImage img9 = QImage((const unsigned char*)(image9.data), image9.cols, image9.rows, image9.cols*image9.channels(), QImage::Format_RGB888);
			QPixmap pixmap9 = QPixmap::fromImage(img9).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
			ui.label_pic_1->setPixmap(pixmap9);
			ui.Label_W1_1->setText(brand);//特征
			ui.Label_W1_2->setText(color);//车身颜色
			ui.Label_W1_3->setText(type);//车型
			ui.Label_W1_4->setText(plate);//车牌号码
			ui.Label_W1_5->setText(brand);//品牌
			ui.Label_W1_6->setText(illegal);//违法情况
			qDebug() << "select success!";
		}
	}
	d.close();
}
void camera::select_nonmotofeature()
{
	QString posture;
	QString type;
	QString color;
	QString gender;
	QString age;
	QString nation;
	QString headFeature;
	QString upperbodyFeature;
	QString picPath;
	QString illegal;
	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		QSqlQuery sql_query;
		QString select_sql = "select posture,type,color,gender,age,nation,headFeature,upperbodyFeature,picPath,illegal from NonmotoHistory order by ID desc limit 1 offset 0";
		sql_query.prepare(select_sql);
		if (!sql_query.exec())
		{
			qDebug() << "select error";
		}
		else
		{
			while (sql_query.next())
			{
				posture = sql_query.value("posture").toString();
				type = sql_query.value("type").toString();
				color = sql_query.value("color").toString();
				gender = sql_query.value("gender").toString();
				age = sql_query.value("age").toString();
				nation = sql_query.value("nation").toString();
				headFeature = sql_query.value("headFeature").toString();
				upperbodyFeature = sql_query.value("upperbodyFeature").toString();
				picPath = sql_query.value("picPath").toString();
				illegal = sql_query.value("illegal").toString();

			}
			cv::Mat image8 = cv::imread(GBK::FromUnicode(picPath));
			cv::cvtColor(image8, image8, CV_BGR2RGB);
			QImage img8 = QImage((const unsigned char*)(image8.data), image8.cols, image8.rows, image8.cols*image8.channels(), QImage::Format_RGB888);
			QPixmap pixmap8 = QPixmap::fromImage(img8).scaled(281, 291, Qt::IgnoreAspectRatio, Qt::FastTransformation);
			ui.label_pic_2->setPixmap(pixmap8);
			ui.Label_W2_1->setText(type);//车型
			ui.Label_W2_2->setText(nation);//民族
			ui.Label_W2_3->setText(posture);//姿态
			ui.Label_W2_4->setText(headFeature);//头部特征
			ui.Label_W2_5->setText(color);//颜色
			ui.Label_W2_6->setText(upperbodyFeature);//上身特征
			ui.Label_W2_7->setText(gender);//性别
			ui.Label_W2_8->setText(illegal);//安全识别
			qDebug() << "select success!";
		}
	}
	d.close();
}