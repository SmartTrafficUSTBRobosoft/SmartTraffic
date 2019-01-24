#include "cit.h"
#pragma execution_character_set("utf-8") 
QString color1 = "rgb(18, 150, 219)";
QString color2 = "#17abe3";
QString color3 = "#2a79bd";
QString Data[12];

int count =0;
CIT::CIT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//setWindowFlags(Qt::FramelessWindowHint );
	//setWindowFlags(Qt::Window);
	//showFullScreen();
	//this->setStyleSheet("background-color:black;");
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(DataRefresh()));
	timer->start(200);
	ui.comboBox_light->clear();
	ui.comboBox_light->insertItems(0, QStringList()
		<< QApplication::translate("MainWindowClass", "交通灯1", Q_NULLPTR)
		<< QApplication::translate("MainWindowClass", "交通灯2", Q_NULLPTR)
		<< QApplication::translate("MainWindowClass", "交通灯3", Q_NULLPTR)
		);

//	ui.tableWidget->setItem(0,0,"无");
	stylesheet();
	view = new QWebEngineView(this);

	view->load(QUrl("https://map.baidu.com/"));
	//view->load(QUrl("https://www.jd.com/"));
	timer_1 = new QTimer;  //初始化定时器
	isStart = false;
	timer_2 = new QTimer;  //初始化定时器
	isStart2 = false;
	sec = 0;
	sec2 = 0;
	cartimeCount = 0;
	cartimePlus = 0;
	timePlus = 0;
	view->show();
	btnonpic = new QPushButton(this);
	btnonpic->setGeometry(QRect(400, 300, 50,50));
	btnonpic->setText("");
	btnonpic->setStyleSheet("QPushButton {border-image:url(:/CIT/Resources/place.png);color:white} "
		"QPushButton:hover { border-image:url(:/CIT/Resources/place.png);color:white }"
		" QPushButton:pressed     {border-image:url(:/CIT/Resources/place.png);color:white}");
	connect(btnonpic, SIGNAL(clicked()), this, SLOT(Click_pushButton_btnonpic()));
	connect(ui.pushButton_record, SIGNAL(clicked()), this, SLOT(Click_pushButton_record()));
	connect(ui.pushButton_setting, SIGNAL(clicked()), this, SLOT(Click_pushButton_setting()));
	connect(timer_1, SIGNAL(timeout()), this, SLOT(updateTime()));
	connect(timer_2, SIGNAL(timeout()), this, SLOT(updateTime2()));
	//yolo_console_dll *yolo = new yolo_console_dll;
	//QObject::connect(yolo, SIGNAL(updatemat()), this, SLOT(displayslot()));
	//myThread *thread1 = new myThread; //新建线程对象
	//thread1->yolo1 = yolo;
	//QObject::connect(thread1, SIGNAL(updatematT()), this, SLOT(displayslot()));
	//thread1->start();

}

CIT::~CIT()
{

}
void CIT::Click_pushButton_btnonpic()
{
	camera *b = new camera();
	QObject::connect(b, SIGNAL(refresh()), this, SLOT(refresh_data()));
	//b->setWindowModality(Qt::ApplicationModal);
	b->setFixedSize(b->width(), b->height());
	b->setWindowTitle(QObject::tr("实时路况"));
	b->show();
}
void CIT::Click_pushButton_record()
{
	record *r = new record();
	//r->setWindowModality(Qt::ApplicationModal);
	r->setFixedSize(r->width(), r->height());
	r->setWindowTitle(QObject::tr("车辆记录"));
	r->show();
}
void CIT::Click_pushButton_setting()
{
	setting *s = new setting();

	//s->setWindowModality(Qt::ApplicationModal);
	s->setFixedSize(s->width(), s->height());
	s->setWindowTitle(QObject::tr("设置"));
	s->show();
}
void CIT::on_pushButton_14_clicked()
{
	this->close();
	//QMessageBox::information(NULL, "抱歉", "请输入18位身份证号", QMessageBox::Ok);

}
void CIT::refresh_data()
{

	float space_occupancy;
	float car_spacing;

	int checksec2 = 0;
	space_occupancy = 4.5*traffic_density / 10;
	if (traffic_density != 0)
		car_spacing = 1000 / (float)traffic_density - 4.5;
	else
		car_spacing = 25;

	if (timer_start)
	{
		checksec2 = stopTime2();
		timePlus = timePlus + checksec2;
		cartimeCount++;
		if (cartimeCount == 5)
		{
			ui.Label_W1_6->setText( QString::number(cartimePlus / timePlus * 200) );
			cartimeCount = 0;
			cartimePlus = 0;
			timePlus = 0;
		}
		startTime2();
		timer_start = false;
		ui.Label_W1_7->setText( QString::number(checksec2) );
	}

	ui.Label_W1_1->setText(QString::number(traffic_density));
	ui.Label_W1_2->setText(QString::number(ave_carspeed));
	ui.Label_W1_5->setText(QString::number(car_spacing));
	ui.Label_W1_8->setText(QString::number(space_occupancy));

	
}
void CIT::resizeEvent(QResizeEvent *)
{
	view->setGeometry(ui.frame1_2->x() + ui.label_road->x(), ui.frame1_2->y()+ ui.label_road->y(),
		ui.label_road->width(), ui.label_road->height());
}
bool CIT::DataRefresh()
{    
	generateRandomNumber(count);
	//qDebug() << Data[0];
	ui.Label_W1_1->setText(Data[0]);
	//qDebug() << Data[1];
	ui.Label_W1_2->setText(Data[1]);
	//qDebug() << Data[2];
	ui.Label_W1_3->setText(Data[2]);
	ui.Label_W1_4->setText(Data[3]);
	ui.Label_W1_5->setText(Data[4]);
	//ui.Label_W1_6->setText(Data[5]);
	//ui.Label_W1_7->setText(Data[6]);
	ui.Label_W1_8->setText(Data[7]);


	ui.Label_W2_1->setText(Data[8]);
	ui.Label_W2_2->setText(Data[9]);
	ui.Label_W2_3->setText(Data[10]);
	ui.Label_W2_4->setText(Data[11]);

	return true;

}

int CIT::generateRandomNumber(int test)

{
	int i, j; count++;
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	for (int i = 0; i < 12; i++)
	{
		if (i < 8)
		{
			Data[i] = QString::number(qrand() % 100);
		}
		else
		{
			if (count == 10)
			{
				Data[i] = QString::number(qrand() % 100);
				if (Data[8].toInt() < 90)
				{
					Data[8] = "路况良好";
					Data[9] = "无";
					Data[10] = "无";
					Data[11] = "无";

				}
				else if (Data[8].toInt() < 100)
				{
					Data[8] = "路况拥堵";
					Data[9] = "城区中心";
					Data[10] = "无";
					Data[11] = "出行高峰";
				}
				count = 0;
			}
		}
	}
	return 0;

}

void CIT::stylesheet()
{
	QPalette palette(this->palette());
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(248, 248, 248, 248));	this->setPalette(palette);

	QStringList qssbtn;//按钮


	qssbtn.append(QString(
		"QPushButton:!enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid #AAAAAA;background:#e1e1e1;color:#777777} "
		"QPushButton:enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid %1;background:%1;color:#FFFFFF} "
		"QPushButton:hover {border-style:none;padding:2px;border-radius:5px;border:2px solid %2;background:%2;color:#FFFFFF}"
		"QPushButton:pressed{border-style:none;padding:2px;border-radius:5px;border:2px solid %3;background:%3;color:#FFFFFF}"
		).arg(color1).arg(color2).arg(color3));

	ui.pushButton_save->setStyleSheet(qssbtn.join(""));
	ui.pushButton_auto->setStyleSheet(qssbtn.join(""));
	ui.pushButton_record->setStyleSheet(qssbtn.join(""));

	ui.pushButton_setting->setStyleSheet("QPushButton {border-image:url(:/CIT/Resources/setting.png);color:white} "
		"QPushButton:hover { border-image:url(:/CIT/Resources/setting_press.png);color:white }"
		" QPushButton:pressed     {border-image:url(:/CIT/Resources/setting_press.png);color:white}");
	ui.pushButton_ghost->setStyleSheet("QPushButton {border-image:url(:/CIT/Resources/people.png);color:white} "
		"QPushButton:hover { border-image:url(:/CIT/Resources/people_press.png);color:white }"
		" QPushButton:pressed     {border-image:url(:/CIT/Resources/people_press.png);color:white}");
	ui.pushButton_exit->setStyleSheet("QPushButton {border-image:url(:/CIT/Resources/exit.png);color:white} "
		"QPushButton:hover { border-image:url(:/CIT/Resources/exit_press.png);color:white }"
		" QPushButton:pressed     {border-image:url(:/CIT/Resources/exit_press.png);color:white}");

	



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
	ui.lineEdit_period->setFont(font_1);
	ui.lineEdit_time->setFont(font_1);


	ui.lineEdit_period->setStyleSheet(qsstext.join(""));
	ui.lineEdit_time->setStyleSheet(qsstext.join(""));



	//ui.tableWidget->verticalHeader()->hide();
	//ui.tableWidget_2->setStyleSheet(QString("background-color: %1").arg(color1));

	QFont font;
	font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font.setPointSize(14);
	font.setBold(true);
	font.setItalic(false);
	font.setWeight(75);


	ui.label_11->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_11->setFont(font);
	ui.label_14->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_14->setFont(font);
	ui.label_20->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_20->setFont(font);
	ui.Label_3_34->setStyleSheet(QString("color: %1").arg(color2));
	ui.Label_3_34->setFont(font);
	ui.label_15->setStyleSheet(QString("color: %1").arg(color1));
	ui.label_15->setFont(font);


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
	ui.comboBox_light->setStyleSheet(qss1.join(""));


	ui.label_5->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_18->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_21->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_16->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg(color2));
	ui.label_17->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_19->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg(color2));

}
void CIT::updateTime()
{
	sec++;
}

void CIT::startTime()
{
	if (!isStart)
	{
		timer_1->start(1000);
		isStart = true;
	}

}

void CIT::stopTime()
{
	if (isStart)
	{
		timer_1->stop();
		isStart = false;
	}
}

void CIT::updateTime2()
{
	sec2++;
}

void CIT::startTime2()
{
	if (!isStart2)
	{
		timer_2->start(1000);
		isStart2 = true;
	}
}

int CIT::stopTime2()
{
	int checksec2 = 0;
	if (isStart2)
	{
		timer_2->stop();
		isStart2 = false;
	}
	checksec2 = sec2;
	sec2 = 0;
	if (car_speed != 0)
		cartimePlus = cartimePlus + 4.5 / ((float)car_speed / 3.6);
	else
		cartimePlus = cartimePlus + checksec2;
	return checksec2;
}
