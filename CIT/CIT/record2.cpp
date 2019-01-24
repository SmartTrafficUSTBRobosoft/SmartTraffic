#include "record2.h"
#pragma execution_character_set("utf-8") 
QString address2[15];
record2::record2(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableWidget_3->setColumnCount(5);
	ui.tableWidget_3->setRowCount(10);
	QStringList header2;
	header2 << "��ͨ�¼�" << tr("��س���") << "�������" << "�����ص�" << "����ʱ��";
	ui.tableWidget_3->setHorizontalHeaderLabels(header2);
	ui.tableWidget_3->verticalHeader()->setHidden(true);
	//ui.tableWidget_2->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '����';};"));
	ui.tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < 5; j++)
		{
			ui.tableWidget_3->setItem(i, j, new QTableWidgetItem("δ֪"));
			ui.tableWidget_3->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
	stylesheet();
	connect(ui.pushButton_1_2, SIGNAL(clicked()), this, SLOT(Click_Result_Right_Button()));
	connect(ui.pushButton_1_1, SIGNAL(clicked()), this, SLOT(Click_Result_Left_Button()));
	connect(ui.tableWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(select_ShowImg(const QModelIndex &)));//˫��
	select_identifyLog();
}

record2::~record2()
{
}
void record2::select_identifyLog()
{
	index_Result = 0;
	ui.lineEdit_4->setText(QString::number(index_Result + 1));
	QString qindex = QString::number(index_Result * 12);

	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		//���ӳɹ�

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,type,posture,color,gender,age,nation,headFeature,upperbodyFeature,illegal,picPath from NonmotoHistory order by identifyDate desc,identifyTime desc  limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("ʶ������"));
		model->setHeaderData(1, Qt::Horizontal, tr("ʶ��ʱ��"));
		model->setHeaderData(2, Qt::Horizontal, tr("����"));
		model->setHeaderData(3, Qt::Horizontal, tr("����̬"));
		model->setHeaderData(4, Qt::Horizontal, tr("��ɫ"));
		model->setHeaderData(5, Qt::Horizontal, tr("�Ա�"));
		model->setHeaderData(6, Qt::Horizontal, tr("����"));
		model->setHeaderData(7, Qt::Horizontal, tr("����"));
		model->setHeaderData(8, Qt::Horizontal, tr("ͷ������"));
		model->setHeaderData(9, Qt::Horizontal, tr("��������"));
		model->setHeaderData(10, Qt::Horizontal, tr("��ȫʶ��"));

		ui.tableWidget->setModel(model);
		ui.tableWidget->setColumnWidth(0, 90);
		ui.tableWidget->setColumnWidth(1, 90);
		ui.tableWidget->setColumnWidth(2, 90);
		ui.tableWidget->setColumnWidth(3, 90);
		ui.tableWidget->setColumnWidth(4, 90);
		ui.tableWidget->setColumnWidth(5, 90);
		ui.tableWidget->setColumnWidth(6, 90);
		ui.tableWidget->setColumnWidth(7, 90);
		ui.tableWidget->setColumnWidth(8, 90);
		ui.tableWidget->setColumnWidth(9, 90);
		ui.tableWidget->setColumnWidth(10, 90);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(11, true);
		for (int j = 0; j< 15; j++)
		{
			address2[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 11, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(11);
		model->setHeaderData(11, Qt::Horizontal, tr("������Ƭ"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address2[s]));
			;

			//QString a;
			//txt->setText("�鿴ʶ��");
			ui.tableWidget->setIndexWidget(model->index(s, 11), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		qDebug() << address2[0];
		QSqlQuery query;
		QString sql2 = "select count(*) from NonmotoHistory";
		query.exec(sql2);
		query.next();
		number_Result = query.value(0).toInt();
	}
	d.close();

}
void record2::select_ShowImg(const QModelIndex &index)
{
	if (index.column() == 11)
	{
		QSqlQuery query;
		QString imgPath = address2[index.row()];
		QTextCodec *code = QTextCodec::codecForName("gb2312");
		string img_Address = code->fromUnicode(imgPath).data();		//�˴���Ҫ���õ�������·��ת��Ϊgb2312����ʶ��
		const cv::Mat img1 = cv::imread(img_Address);
		if (img1.empty())
		{
			//��ͼƬ���ڱ����ϣ���Ҫ��ʾno photo
		}
		else
		{
			showImg2 dialog(this);
			cv::cvtColor(img1, img1, CV_BGR2RGB);
			QImage img = QImage((const unsigned char*)(img1.data), img1.cols,
				img1.rows, img1.cols*img1.channels(), QImage::Format_RGB888);
			QPixmap pixMap = QPixmap::fromImage(img).scaled(245, 245, Qt::KeepAspectRatio, Qt::FastTransformation);
			QGraphicsScene *scene = new QGraphicsScene;
			scene->addPixmap(pixMap);
			dialog.ui.graphicsView->setScene(scene);
			int current_row = index.row();
			QAbstractItemModel *model = ui.tableWidget->model();
			QModelIndex index = model->index(current_row, 2);//ѡ���е�һ�е�����
			QVariant Type_data = model->data(index);
			QModelIndex index2 = model->index(current_row, 3);//ѡ���е�һ�е�����
			QVariant Posture_data = model->data(index2);
			QModelIndex index3 = model->index(current_row, 4);//ѡ���е�һ�е�����
			QVariant Color_data = model->data(index3);
			QModelIndex index4 = model->index(current_row, 5);//ѡ���е�һ�е�����
			QVariant Gender_data = model->data(index4);
			QModelIndex index5 = model->index(current_row, 6);//ѡ���е�һ�е�����
			QVariant Age_data = model->data(index5);
			QModelIndex index6 = model->index(current_row, 7);//ѡ���е�һ�е�����
			QVariant Nation_data = model->data(index6);
			QModelIndex index7 = model->index(current_row, 8);//ѡ���е�һ�е�����
			QVariant Head_data = model->data(index7);
			QModelIndex index8 = model->index(current_row, 9);//ѡ���е�һ�е�����
			QVariant upperbody_data = model->data(index8);
			QModelIndex index9 = model->index(current_row, 10);//ѡ���е�һ�е�����
			QVariant Illegal_data = model->data(index9);
			
			QString qType = Type_data.toString();//����
			QString qPosture = Posture_data.toString();//����
			QString qColor = Color_data.toString();//Ʒ��
			QString qGender = Gender_data.toString();//��ɫ
			QString qAge = Age_data.toString();//��־��
			QString qNation = Nation_data.toString();//Υ�����
			QString qHead = Head_data.toString();//Ʒ��
			QString qupperbody = upperbody_data.toString();//��ɫ
			QString qIllegal = Illegal_data.toString();//Υ�����
			dialog.ui.Label_W2_1->setText(qType);//����
			dialog.ui.Label_W2_2->setText(qNation);//����
			dialog.ui.Label_W2_3->setText(qPosture);//��̬
			dialog.ui.Label_W2_4->setText(qHead);//ͷ������
			dialog.ui.Label_W2_5->setText(qColor);//��ɫ
			dialog.ui.Label_W2_6->setText(qupperbody);//��������
			dialog.ui.Label_W2_7->setText(qGender);//�Ա�
			dialog.ui.Label_W2_8->setText(qIllegal);//��ȫʶ��
			if (dialog.exec()) {}
		}
	}
}
void record2::select_ShowImg1(const QModelIndex &index)
{
	QString adddata = index.data().toString();
	address2[index.row()] = adddata;
}
void record2::Click_Result_Right_Button()
{
	/***TODO���ж�һ���ж���ҳ����ǰ�Ƿ񳬳�ҳ����Χ***/
	int number_pages = number_Result / 12;
	if (number_Result % 12 != 0)
		number_pages++;
	if (index_Result + 1 == number_pages)
		QMessageBox::information(NULL, "����", "�Ѿ������һҳ��", QMessageBox::Ok);
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
		//���ӳɹ�

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,type,posture,color,gender,age,nation,headFeature,upperbodyFeature,illegal,picPath from NonmotoHistory order by identifyDate desc,identifyTime desc  limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("ʶ������"));
		model->setHeaderData(1, Qt::Horizontal, tr("ʶ��ʱ��"));
		model->setHeaderData(2, Qt::Horizontal, tr("����"));
		model->setHeaderData(3, Qt::Horizontal, tr("����̬"));
		model->setHeaderData(4, Qt::Horizontal, tr("��ɫ"));
		model->setHeaderData(5, Qt::Horizontal, tr("�Ա�"));
		model->setHeaderData(6, Qt::Horizontal, tr("����"));
		model->setHeaderData(7, Qt::Horizontal, tr("����"));
		model->setHeaderData(8, Qt::Horizontal, tr("ͷ������"));
		model->setHeaderData(9, Qt::Horizontal, tr("��������"));
		model->setHeaderData(10, Qt::Horizontal, tr("��ȫʶ��"));

		ui.tableWidget->setModel(model);
		ui.tableWidget->setColumnWidth(0, 90);
		ui.tableWidget->setColumnWidth(1, 90);
		ui.tableWidget->setColumnWidth(2, 90);
		ui.tableWidget->setColumnWidth(3, 90);
		ui.tableWidget->setColumnWidth(4, 90);
		ui.tableWidget->setColumnWidth(5, 90);
		ui.tableWidget->setColumnWidth(6, 90);
		ui.tableWidget->setColumnWidth(7, 90);
		ui.tableWidget->setColumnWidth(8, 90);
		ui.tableWidget->setColumnWidth(9, 90);
		ui.tableWidget->setColumnWidth(10, 90);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(11, true);
		for (int j = 0; j< 15; j++)
		{
			address2[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 11, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(11);
		model->setHeaderData(11, Qt::Horizontal, tr("������Ƭ"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address2[s]));
			;

			//QString a;
			//txt->setText("�鿴ʶ��");
			ui.tableWidget->setIndexWidget(model->index(s, 11), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		qDebug() << address2[0];
		QSqlQuery query;
		QString sql2 = "select count(*) from NonmotoHistory";
		query.exec(sql2);
		query.next();
		number_Result = query.value(0).toInt();
	}
	d.close();

}
void record2::Click_Result_Left_Button()
{
	if (index_Result == 0)
		QMessageBox::information(NULL, "����", "�Ѿ��ǵ�һҳ��", QMessageBox::Ok);
	else
		index_Result--;
	ui.lineEdit_4->setText(QString::number(index_Result + 1));
	QString qindex = QString::number(index_Result * 12);

	QSqlDatabase d = QSqlDatabase::addDatabase("QSQLITE");
	d.setDatabaseName("history.db");
	if (d.open())
	{
		//���ӳɹ�

		QSqlQueryModel *model = new QSqlQueryModel(ui.tableWidget);
		QString sql = "select identifyDate,identifyTime,type,posture,color,gender,age,nation,headFeature,upperbodyFeature,illegal,picPath from NonmotoHistory order by identifyDate desc,identifyTime desc  limit " + qindex + ", 12 ";
		model->setQuery(sql, d);
		model->setHeaderData(0, Qt::Horizontal, tr("ʶ������"));
		model->setHeaderData(1, Qt::Horizontal, tr("ʶ��ʱ��"));
		model->setHeaderData(2, Qt::Horizontal, tr("����"));
		model->setHeaderData(3, Qt::Horizontal, tr("����̬"));
		model->setHeaderData(4, Qt::Horizontal, tr("��ɫ"));
		model->setHeaderData(5, Qt::Horizontal, tr("�Ա�"));
		model->setHeaderData(6, Qt::Horizontal, tr("����"));
		model->setHeaderData(7, Qt::Horizontal, tr("����"));
		model->setHeaderData(8, Qt::Horizontal, tr("ͷ������"));
		model->setHeaderData(9, Qt::Horizontal, tr("��������"));
		model->setHeaderData(10, Qt::Horizontal, tr("��ȫʶ��"));

		ui.tableWidget->setModel(model);
		ui.tableWidget->setColumnWidth(0, 90);
		ui.tableWidget->setColumnWidth(1, 90);
		ui.tableWidget->setColumnWidth(2, 90);
		ui.tableWidget->setColumnWidth(3, 90);
		ui.tableWidget->setColumnWidth(4, 90);
		ui.tableWidget->setColumnWidth(5, 90);
		ui.tableWidget->setColumnWidth(6, 90);
		ui.tableWidget->setColumnWidth(7, 90);
		ui.tableWidget->setColumnWidth(8, 90);
		ui.tableWidget->setColumnWidth(9, 90);
		ui.tableWidget->setColumnWidth(10, 90);
		ui.tableWidget->verticalHeader()->hide();
		ui.tableWidget->setColumnHidden(11, true);
		for (int j = 0; j< 15; j++)
		{
			address2[j] = "NULL";
		}
		for (int k = 0; k < model->rowCount(); k++)
		{
			QModelIndex index1 = model->index(k, 11, QModelIndex());
			select_ShowImg1(index1);
		}
		model->insertColumn(11);
		model->setHeaderData(11, Qt::Horizontal, tr("������Ƭ"));
		for (int s = 0; s < model->rowCount(); s++)
		{
			QLabel *txt = new QLabel();
			txt->setProperty("row", s);
			txt->setAlignment(Qt::AlignCenter);

			txt->setStyleSheet(QString("image: url(%1);").arg(address2[s]));
			;

			//QString a;
			//txt->setText("�鿴ʶ��");
			ui.tableWidget->setIndexWidget(model->index(s, 11), txt);
			ui.tableWidget->setRowHeight(s, 35);
		}

		qDebug() << address2[0];
		QSqlQuery query;
		QString sql2 = "select count(*) from NonmotoHistory";
		query.exec(sql2);
		query.next();
		number_Result = query.value(0).toInt();
	}
	d.close();

}
void record2::stylesheet()
{
	QPalette palette(this->palette());
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(248, 248, 248, 248));	this->setPalette(palette);
	this->setPalette(palette);

	QStringList qssbtn;//��ť


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


	ui.tabWidget->setStyleSheet(                                            //��ǩ

		QString("QTabWidget::tab-bar{left:20px;background:green; }"//��ǩ����λ��
			"QTabBar::tab{"
			"min-width:175px;min-height:20px;"
			"background: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #E1E1E1, stop:0.4 #DDDDDD,stop:0.5 #D8D8D8,stop:1.0 #D3D3D3);"
			"border:1px solid %1;border-bottom-color:%1; /* same as the pane color */"
			"border-top-left-radius:4px;border-top-right-radius:4px;min-width:14ex;padding: 2px;}"
			"QTabBar::tab:selected, QTabBar::tab:hover {background:qlineargradient(x1:0,y1:0, x2:0,y2:1,stop:0 #fafafa,stop:0.4 #f4f4f4,stop:0.5 #e7e7e7,stop:1.0 #fafafa);"
			" 	border: 1px solid #FF0000;border-bottom: none;border-top-left-radius:4px;border-top-right-radius: 4px;"
			"}"
			"QTabBar::tab:selected{margin-top: 2px;border-bottom-color: #FFFFFF; background:%1;border-color:#FFFFFF;color:white;min-width:90px;}"//ѡ��
			"QTabBar::tab:!selected{margin-top: 5px; border-bottom-color: #DDDDDD; background:%2;border-color:#DDDDDD;color:#F5F5F5;min-width:90px;}"//δѡ��
		).arg(color1).arg(color3));



	QStringList qss;//�ı�����ʾ
	qss.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:5px;border:2px solid %1;}").arg("#555555"));
	qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg("#555555"));

	//ui.lineEdit->setStyleSheet(qss.join(""));
	//ui.lineEdit_2->setStyleSheet(qss.join(""));
	//ui.lineEdit_3->setStyleSheet(qss.join(""));
	//ui.lineEdit_4->setStyleSheet(qss.join(""));


	QStringList qsstext;//�ı��򽻻�
	qsstext.append(QString("QLineEdit{border-style:none;padding:2px;border-radius:5px;border:2px solid %1;}").arg(color1));
	qsstext.append(QString("QLineEdit:focus{border:2px solid %1;}").arg("#996666"));
	qsstext.append(QString("QLineEdit:font:12pt '����';"));
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
		"border: 2px solid %1;          /*�߿���ɫ*/  "
		"gridline-color:#ffffff;             /*grid����ɫ*/  "
		"background-color: rgb(255, 255, 255);  "
		"alternate-background-color: #F5F5F5; /*�н�����ɫ*/ "
		"selection-background-color: rgb(130, 190, 100); /*ѡ���б�����ɫ*/  "
		" }  "

		" QTableView::item:!alternate:!selected{  "
		"  background-color:#d4e8c5;    /*�����е���һ��ɫ*/ "
		" }  }").arg("#999999"));
	ui.tableWidget->setStyleSheet(qsstable.join(""));
	ui.tableWidget->setAlternatingRowColors(true);
	ui.tableWidget->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '����';};"));

	/*ui.tableWidget_2->setStyleSheet(qsstable.join(""));
	ui.tableWidget_2->setAlternatingRowColors(true);
	ui.tableWidget_2->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '����';};"));*/
	//ui.tableWidget_2->verticalHeader()->hide();

	ui.tableWidget_3->setStyleSheet(qsstable.join(""));
	ui.tableWidget_3->setAlternatingRowColors(true);
	ui.tableWidget_3->horizontalHeader()->setStyleSheet(QString("QHeaderView{font:12pt '����';};"));
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