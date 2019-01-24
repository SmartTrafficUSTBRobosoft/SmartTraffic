#include "myDialog.h"
#include <QPen>
#include<QPainter>
myDialog::myDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

myDialog::~myDialog()
{
}
void myDialog::paintEvent(QPaintEvent *event)
{
	QDialog::paintEvent(event);

	int w = this->width(), h = this->height();


	// »­±³¾°Í¼Æ¬ 
	QPainter painter(this);

	// »­Ê®×ÖÏß
	int x = m_pos.x(), y = m_pos.y();
	//x -= 1; y -= 1;
	x += 1; y += 1;
	//qDebug("repaint: (%dx%d)", x, y);
	painter.setPen(QColor(255, 0, 0, 150));
	painter.drawLine(0, y, w, y);
	painter.drawLine(x, 0, x, h);
	painter.setPen(QColor(255, 0, 0, 150));
	painter.drawLine(0, y, w, y);
	painter.drawLine(x, 0, x, h);


	QRect selected(m_start, m_pos);
	// ÇøÓò
	painter.setPen(QColor(255, 0, 0));
	painter.drawRect(selected);

}
void myDialog::mouseMoveEvent(QMouseEvent * event)
{
	m_pos = event->pos();
	update();
}
void myDialog::mousePressEvent(QMouseEvent * event)
{
	m_dragging = true;
	m_start = event->pos();
}
void myDialog::mouseReleaseEvent(QMouseEvent * event)
{

	m_end = event->pos();
	m_dragging = false;
	update();


}