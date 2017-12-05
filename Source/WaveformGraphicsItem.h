#pragma once

#include <QGraphicsItem>
#include <QResizeEvent>

class QPolygon;

class WaveformGraphicsItem : public QGraphicsItem
{
	public:
	    WaveformGraphicsItem();
	    ~WaveformGraphicsItem();

	    QRectF boundingRect() const;
	    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

		void SetActiveTransient(std::size_t activeTransientNumber);

	private:
		QPolygon CreateWaveformPolygon();
		void DrawTransientLines(QPainter* painter);

		std::size_t activeTransientNumber_;
};
