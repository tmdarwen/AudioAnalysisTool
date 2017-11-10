#include "Waveform.h"
#include <QGraphicsScene>
#include <QPainter>

Waveform::Waveform()
{
}

Waveform::~Waveform()
{
}

QRectF Waveform::boundingRect() const
{
	return scene()->sceneRect();
}

void Waveform::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /* widget */)
{
	QPolygon polygon;
	polygon << QPoint(10, 10) << QPoint(30, 10) << QPoint(30, 30) << QPoint(10, 30);
    painter->setPen(QPen(Qt::darkBlue));
    painter->setBrush(Qt::darkBlue);
	painter->drawPolygon(polygon);
}
