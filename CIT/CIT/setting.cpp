#include "setting.h"
#pragma execution_character_set("utf-8") 
#include "cit.h"

setting::setting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	stylesheet();
	connect(ui.pushButton_open, SIGNAL(clicked()), this, SLOT(Click_pushButton_open()));
	connect(ui.pushButton_close, SIGNAL(clicked()), this, SLOT(Click_pushButton_close()));
}

setting::~setting()
{

}
void setting::stylesheet()
{
	QPalette palette(this->palette());
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(248, 248, 248, 248));
	this->setPalette(palette);




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
		"QTabBar::tab:selected{margin-top: 2px;margin-left: -1px; margin-right: -1px;border-bottom-color: #FFFFFF; background:%1;border-color:#FFFFFF;color:white;min-width:90px;}"//选择
		"QTabBar::tab:!selected{margin-top: 5px;margin-left: 1px; margin-right: 1px;border-bottom-color: #DDDDDD; background:%2;border-color:#DDDDDD;color:#F5F5F5;min-width:90px;}"//未选择
		).arg(color2).arg(color1));

	ui.label->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_2->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_3->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 5px;border: 2px solid %1;}").arg("#999999"));
	ui.label_4->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 3px;border: 2px solid %1;}").arg("#999999"));
	ui.label_5->setStyleSheet(QString::fromUtf8("QFrame{border-radius:3px;border: 2px solid %1;}").arg("#999999"));
	ui.label_6->setStyleSheet(QString::fromUtf8("QFrame{border-radius: 3px;border: 2px solid %1;}").arg("#999999"));

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
	ui.comboBox_type->setStyleSheet(qss1.join(""));
	QStringList qssbtn;//按钮


	qssbtn.append(QString(
		"QPushButton:!enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid #AAAAAA;background:#e1e1e1;color:#777777} "
		"QPushButton:enabled {border-style:none;padding:2px;border-radius:5px;border:2px solid %1;background:%1;color:#FFFFFF} "
		"QPushButton:hover {border-style:none;padding:2px;border-radius:5px;border:2px solid %2;background:%2;color:#FFFFFF}"
		"QPushButton:pressed{border-style:none;padding:2px;border-radius:5px;border:2px solid %3;background:%3;color:#FFFFFF}"
	).arg(color1).arg(color2).arg(color3));

	ui.pushButton_open->setStyleSheet(qssbtn.join(""));
	ui.pushButton_close->setStyleSheet(qssbtn.join(""));

}

void setting::Click_pushButton_open()
{
	myDialog md(this);
	md.exec();
	
}
void setting::Click_pushButton_close()
{
	
}
