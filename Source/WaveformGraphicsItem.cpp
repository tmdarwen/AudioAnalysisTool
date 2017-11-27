#include "WaveformGraphicsItem.h"
#include "AudioFile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <algorithm>

WaveformGraphicsItem::WaveformGraphicsItem()
{
}

WaveformGraphicsItem::~WaveformGraphicsItem()
{
}

QRectF WaveformGraphicsItem::boundingRect() const
{
	return scene()->sceneRect();
}

void WaveformGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /* widget */)
{
	if(AudioFile::GetInstance().GetWaveFile().get())
	{
		auto audioData{AudioFile::GetInstance().GetAudioData()};

		std::size_t width{static_cast<std::size_t>(scene()->sceneRect().width())};
		std::size_t halfHeight{static_cast<std::size_t>(scene()->sceneRect().height())/2};
		std::size_t samplesPerPixel{audioData.size() / width};

		QPolygon polygon;
		std::vector<QPoint> lowerPoints;

		for(std::size_t i{0}; i < width; ++i)
		{
			std::size_t currentPosition{i * samplesPerPixel};
			auto minMaxSamples{std::minmax_element(audioData.begin() + currentPosition, audioData.begin() + currentPosition + samplesPerPixel)};

			auto minPoint = halfHeight - (*(minMaxSamples.first) * halfHeight);
			auto maxPoint = halfHeight - (*(minMaxSamples.second) * halfHeight);

			polygon << QPoint(i, minPoint);
			lowerPoints.push_back(QPoint(i, maxPoint));
		}

		std::for_each(lowerPoints.rbegin(), lowerPoints.rend(), [&polygon](QPoint& point) { polygon << point; });

		painter->setPen(QPen(Qt::darkBlue));
		painter->setBrush(Qt::darkBlue);
		painter->drawPolygon(polygon);
	}
}
