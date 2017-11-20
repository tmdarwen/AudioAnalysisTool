#pragma once

#include <QGraphicsItem>
#include <QResizeEvent>

class Waveform : public QGraphicsItem
{
	public:
	    Waveform();
	    ~Waveform();

	    QRectF boundingRect() const;
	    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};
