#pragma once

#include <QGraphicsItem>
#include <QResizeEvent>

class WaveformGraphicsItem : public QGraphicsItem
{
	public:
	    WaveformGraphicsItem();
	    ~WaveformGraphicsItem();

	    QRectF boundingRect() const;
	    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};
