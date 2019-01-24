#include "record.h"
#pragma execution_character_set("utf-8") 
QString address[15];
record::record(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//ui.tableWidget->setColumnCount(7);
	//ui.tableWidget->setRowCount(10);

	//QStringList header;
	//header << "机动车" << tr("特征") << "车型" << "品牌" << "颜色" << "标志物" << "违法情况";
	//ui.tableWidget->setHorizontalHeaderLabels(header);
	//ui.tableWidget->verticalHeader()->setHidden(true);
	////ui.tableWidget->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//for (int i = 0; i<10; i++)
	//{
	//	ui.tableWidget->setItem(i, 0, new QTableWidgetItem("未知机动车"));
	//	ui.tableWidget->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//	for (int j = 1; j < 7; j++)
	//	{
	//		ui.tableWidget->setItem(i, j, new QTableWidgetItem("无"));
	//		ui.tableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//	}
	//}
	connect(ui.pushButton_1_2, SIGNAL(clicked()), this, SLOT(Click_Result_Right_Button()));
	connect(ui.pushButton_1_1, SIGNAL(clicked()), this, SLOT(Click_Result_Left_Button()));
	connect(ui.tableWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(select_ShowImg(const QModelIndex &)));//双击
	select_identifyLog();
	//ui.tableWidget_2->setColumnCount(9);
	//ui.tableWidget_2->setRowCount(10);
	//QStringList header1;
	//header1 << "非机动车" << tr("车型") << "姿态" << "颜色" << "性别" << "民族" << "头部特征" << "上身特征" << "安全识别";
	//ui.tableWidget_2->setHorizontalHeaderLabels(header1);
	//ui.tableWidget_2->verticalHeader()->setHidden(true);
	////ui.tableWidget_2->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));
	////ui.tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.tableWidget_2->setColumnWidth(0, 100);
	//ui.tableWidget_2->setColumnWidth(1, 50);
	//ui.tableWidget_2->setColumnWidth(2, 50);
	//ui.tableWidget_2->setColumnWidth(3, 50);
	//ui.tableWidget_2->setColumnWidth(4, 50);
	//ui.tableWidget_2->setColumnWidth(5, 50);
	//ui.tableWidget_2->setColumnWidth(6, 80);
	//ui.tableWidget_2->setColumnWidth(7, 80);
	//ui.tableWidget_2->setColumnWidth(8, 85);


	//for (int i = 0; i < 10; i++)
	//{
	//	ui.tableWidget_2->setItem(i, 0, new QTableWidgetItem("未知非机动车"));
	//	ui.tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//	for (int j = 1; j < 9; j++)
	//	{
	//		ui.tableWidget_2->setItem(i, j, new QTableWidgetItem("无"));
	//		ui.tableWidget_2->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//	}
	//}
	

	ui.tableWidget_3->setColumnCount(5);
	ui.tableWidget_3->setRowCount(10);
	QStringList header2;
	header2 << "交通事件" << tr("相关车辆") << "处理情况" << "发生地点" << "发生时间";
	ui.tableWidget_3->setHorizontalHeaderLabels(header2);
	ui.tableWidget_3->verticalHeader()->setHidden(true);
	//ui.tableWidget_2->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));
	ui.tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 5; j++)
		{
			ui.tableWidget_3->setItem(i, j, new QTableWidgetItem("未知"));
			ui.tableWidget_3->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}

	stylesheet();
}

record::~record()
{

}

void record::select_identifyLog()
{
	index_Result = 0;
	ui.lineEdit_4->setText(QString::number(index_Result + 1));
	QString qindex = QString::number(index_Result * 12);

	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		//连接成功

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,brand,type,color,plate,feature,picPath from carHistory order by identifyDate desc,identifyTime desc limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("识别日期"));
		model->setHeaderData(1, Qt::Horizontal, tr("识别时间"));
		model->setHeaderData(2, Qt::Horizontal, tr("品牌"));
		model->setHeaderData(3, Qt::Horizontal, tr("车型"));
		model->setHeaderData(4, Qt::Horizontal, tr("颜色"));
		model->setHeaderData(5, Qt::Horizontal, tr("车牌"));
		model->setHeaderData(6, Qt::Horizontal, tr("特征"));
		
		ui.tableWidget->setModel(model);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(7, true);
		for (int j = 0; j< 15; j++)
		{
			address[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 7, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(7);
		model->setHeaderData(7, Qt::Horizontal, tr("车辆照片"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address[s]));
			;

			//QString a;
			//txt->setText("查看识别");
			ui.tableWidget->setIndexWidget(model->index(s, 7), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		//qDebug() << address[0];
		QSqlQuery query;
		QString sql2 = "select count(*) from carHistory";
		query.exec(sql2);
		query.next();
		number_Result = query.value(0).toInt();
	}
	d.close();
		
}
void record::select_ShowImg(const QModelIndex &index)
{
	if (index.column() == 7)
	{
		QSqlQuery query;
		QString imgPath = address[index.row()];
		QTextCodec *code = QTextCodec::codecForName("gb2312");
		string img_Address = code->fromUnicode(imgPath).data();		//此处需要将得到的中文路径转化为gb2312进行识别
		const cv::Mat img1 = cv::imread(img_Address);
		if (img1.empty())
		{
			//该图片不在本机上，需要显示no photo
		}
		else
		{
			showImg dialog(this);
			cv::cvtColor(img1, img1, CV_BGR2RGB);
			QImage img = QImage((const unsigned char*)(img1.data), img1.cols,
				img1.rows, img1.cols*img1.channels(), QImage::Format_RGB888);
			QPixmap pixMap = QPixmap::fromImage(img).scaled(245, 245, Qt::KeepAspectRatio, Qt::FastTransformation);
			QGraphicsScene *scene = new QGraphicsScene;
			scene->addPixmap(pixMap);
			dialog.ui.graphicsView->setScene(scene);
			int current_row = index.row();
			QAbstractItemModel *model = ui.tableWidget->model();
			QModelIndex index = model->index(current_row, 6);//选中行第一列的内容
			QVariant Feature_data = model->data(index);
			QModelIndex index2 = model->index(current_row, 3);//选中行第一列的内容
			QVariant Type_data = model->data(index2);
			QModelIndex index3 = model->index(current_row, 2);//选中行第一列的内容
			QVariant Brand_data = model->data(index3);
			QModelIndex index4 = model->index(current_row, 4);//选中行第一列的内容
			QVariant Color_data = model->data(index4);
			QModelIndex index5 = model->index(current_row, 5);//选中行第一列的内容
			QVariant Plate_data = model->data(index5);
			QModelIndex index6 = model->index(current_row, 6);//选中行第一列的内容
			QVariant Illegal_data = model->data(index6);
			QString qFeature = Feature_data.toString();//特征
			QString qType = Type_data.toString();//车型
			QString qBrand = Brand_data.toString();//品牌
			QString qColor = Color_data.toString();//颜色
			QString qPlate = Plate_data.toString();//标志物
			QString qIllegal = Illegal_data.toString();//违法情况

			dialog.ui.Label_W1_1->setText(qFeature);//特征
			dialog.ui.Label_W1_2->setText(qColor);//车身颜色
			dialog.ui.Label_W1_3->setText(qType);//车型
			dialog.ui.Label_W1_4->setText(qPlate);//车牌号码
			dialog.ui.Label_W1_5->setText(qBrand);//品牌
			dialog.ui.Label_W1_6->setText(qIllegal);//违法情况
			if (dialog.exec()) {}

			
			
		}
	}
}
void record::select_ShowImg1(const QModelIndex &index)
{
	QString adddata = index.data().toString();
	address[index.row()] = adddata;
}
void record::Click_Result_Right_Button()
{
	/***TODO：判断一共有多少页，当前是否超出页数范围***/
	int number_pages = number_Result / 12;
	if (number_Result % 12 != 0)
		number_pages++;
	if (index_Result + 1 == number_pages)
		QMessageBox::information(NULL, "错误", "已经是最后一页！", QMessageBox::Ok);
	else
	{
		index_Result++;
		ui.lineEdit_4->setText(QString::number(index_Result + 1));
	}
	/***END***/
	QString qindex = QString::number(index_Result * 12);
	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		//连接成功

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,brand,type,color,plate,feature,picPath from carHistory order by identifyDate desc,identifyTime desc limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("识别日期"));
		model->setHeaderData(1, Qt::Horizontal, tr("识别时间"));
		model->setHeaderData(2, Qt::Horizontal, tr("品牌"));
		model->setHeaderData(3, Qt::Horizontal, tr("车型"));
		model->setHeaderData(4, Qt::Horizontal, tr("颜色"));
		model->setHeaderData(5, Qt::Horizontal, tr("车牌"));
		model->setHeaderData(6, Qt::Horizontal, tr("特征"));

		ui.tableWidget->setModel(model);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(7, true);
		for (int j = 0; j< 15; j++)
		{
			address[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 7, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(7);
		model->setHeaderData(7, Qt::Horizontal, tr("车辆照片"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address[s]));
			;

			//QString a;
			//txt->setText("查看识别");
			ui.tableWidget->setIndexWidget(model->index(s, 7), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		//qDebug() << address[0];
	}
	d.close();

}
void record::Click_Result_Left_Button()
{
	if (index_Result == 0)
		QMessageBox::information(NULL, "错误", "已经是第一页！", QMessageBox::Ok);
	else
		index_Result--;
	ui.lineEdit_4->setText(QString::number(index_Result + 1));
	QString qindex = QString::number(index_Result * 12);

	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		//连接成功

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,brand,type,color,plate,feature,picPath from carHistory order by identifyDate desc,identifyTime desc limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("识别日期"));
		model->setHeaderData(1, Qt::Horizontal, tr("识别时间"));
		model->setHeaderData(2, Qt::Horizontal, tr("品牌"));
		model->setHeaderData(3, Qt::Horizontal, tr("车型"));
		model->setHeaderData(4, Qt::Horizontal, tr("颜色"));
		model->setHeaderData(5, Qt::Horizontal, tr("车牌"));
		model->setHeaderData(6, Qt::Horizontal, tr("特征"));

		ui.tableWidget->setModel(model);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(7, true);
		for (int j = 0; j< 15; j++)
		{
			address[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 7, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(7);
		model->setHeaderData(7, Qt::Horizontal, tr("车辆照片"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address[s]));
			;

			//QString a;
			//txt->setText("查看识别");
			ui.tableWidget->setIndexWidget(model->index(s, 7), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		//qDebug() << address[0];
	}
	d.close();

}
void record::stylesheet()
{
	QPalette palette(this->palette());
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(248, 248, 248, 248));	this->setPalette(palette);
	this->setPalette(palette);

	QStringList qssbtn;//按钮


	qssbtn.append(QString(
		"QPushButton:!enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid #AAAAAA;background:#e1e1e1;color:#777777} "
		"QPushButton:enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid %1;background:%1;color:#FFFFFF} "
		"QPushButton:hover {border-style:none;padding:2px;border-radius:5px;border:2px solid %2;background:%2;color:#FFFFFF}"
		"QPushButton:pressed{border-style:none;padding:2px;border-radius:5px;border:2px solid %3;background:%3;color:#FFFFFF}"
		).arg(color1).arg(color2).arg(color3));


	ui.pushButton_1_1->setStyleSheet(qssbtn.join(""));
	ui.pushButton_1_2->setStyleSheet(qssbtn.join(""));
	ui.pushButton_1_3->setStyleSheet(qssbtn.join(""));
	/*ui.pushButton_2_1->setStyleSheet(qssbtn.join(""));
	ui.pushButton_2_2->setStyleSheet(qssbtn.join(""));
	ui.pushButton_2_3->setStyleSheet(qssbtn.join(""));*/
	ui.pushButton_3_1->setStyleSheet(qssbtn.join(""));
	ui.pushButton_3_2->setStyleSheet(qssbtn.join(""));
	ui.pushButton_3_3->setStyleSheet(qssbtn.join(""));


	ui.tabWidget->setStyleSheet(                                            //标签

		QString("QTabWidget::tab-bar{left:20px;background:green; }"//标签左右位置
		"QTabBar::tab{"
		"min-width:175px;min-height:20px;"
		"background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #E1E1E1, stop:0.4 #DDDDDD,stop:0.5 #D8D8D8,stop:1.0 #D3D3D3);"
		"border:1px solid %1;border-bottom-color:%1; /* same as the pane color */"
		"border-top-left-radius:4px;border-top-right-radius:4px;min-width:14ex;padding: 2px;}"
		"QTabBar::tab:selected, QTabBar::tab:hover {background:qlineargradient(x1:0,y1:0, x2:0,y2:1,stop:0 #fafafa,stop:0.4 #f4f4f4,stop:0.5 #e7e7e7,stop:1.0 #fafafa);"
		" 	border: 1px solid #FF0000;border-bottom: none;border-top-left-radius:4px;border-top-right-radius: 4px;"
		"}"
		"QTabBar::tab:selected{margin-top: 2px;border-bottom-color: #FFFFFF; background:%1;border-color:#FFFFFF;color:white;min-width:90px;}"//选择
		"QTabBar::tab:!selected{margin-top: 5px; border-bottom-color: #DDDDDD; background:%2;border-color:#DDDDDD;color:#F5F5F5;min-width:90px;}"//未选择
		).arg(color1).arg(color3));



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

	/*ui.lineEdit_3->setFont(font_1);*/
	ui.lineEdit_4->setFont(font_1);
	ui.lineEdit_5->setFont(font_1);
	/*ui.lineEdit_3->setStyleSheet(qsstext.join(""));*/
	ui.lineEdit_4->setStyleSheet(qsstext.join(""));
	ui.lineEdit_5->setStyleSheet(qsstext.join(""));

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
	ui.tableWidget->setStyleSheet(qsstable.join(""));
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));

	/*ui.tableWidget_2->setStyleSheet(qsstable.join(""));
	ui.tableWidget_2->setAlternatingRowColors(true);
	ui.tableWidget_2->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));*/
	//ui.tableWidget_2->verticalHeader()->hide();

	ui.tableWidget_3->setStyleSheet(qsstable.join(""));
	ui.tableWidget_3->setAlternatingRowColors(true);
	ui.tableWidget_3->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '黑体';};"));
	//ui.tableWidget->verticalHeader()->hide();
	//ui.tableWidget_2->setStyleSheet(QString("background-color: %1").arg(color1));

	QFont font;
	font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font.setPointSize(14);
	font.setBold(true);
	font.setItalic(false);
	font.setWeight(75);




	QFont font1;
	font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font1.setPointSize(12);
	font1.setBold(true);
	font1.setWeight(75);


}