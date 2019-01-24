#pragma once

#include <QDialog>
#include "ui_myDialog.h"
#include <QPoint>
#include <QColor>
#include <QPaintEvent>
class myDialog : public QDialog
{
	Q_OBJECT

public:
	myDialog(QWidget *parent = Q_NULLPTR);
	~myDialog();
private:
	virtual void	paintEvent(QPaintEvent *event);
	virtual void	mouseMoveEvent(QMouseEvent * event);
	virtual void	mousePressEvent(QMouseEvent * event);
	virtual void	mouseReleaseEvent(QMouseEvent * event);
private:
	Ui::myDialog ui;
	QRect selectRegion; // 输出选中的区域
	QPoint m_start, m_end;
	QPoint m_pos;
	bool m_dragging;
	QPixmap m_image;
};
