#include "WaveformGraphicsItem.h"
#include "AudioFile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <algorithm>
#include <Windows.h>

WaveformGraphicsItem::WaveformGraphicsItem() : activeTransientNumber_{1}
{
}

WaveformGraphicsItem::~WaveformGraphicsItem()
{
}

QRectF WaveformGraphicsItem::boundingRect() const
{
	return scene()->sceneRect();
}

QPolygon WaveformGraphicsItem::CreateWaveformPolygon()
{
	QPolygon polygon;
	std::vector<QPoint> lowerPoints;

	auto audioData{AudioFile::GetInstance().GetAudioData()};

	std::size_t width{static_cast<std::size_t>(scene()->sceneRect().width())};
	std::size_t height{static_cast<std::size_t>(scene()->sceneRect().height())};
	std::size_t samplesPerPixel{audioData.size() / width};
	std::size_t halfHeight{height/2};

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

	return polygon;
}

void WaveformGraphicsItem::DrawTransientLines(QPainter* painter)
{
	std::size_t width{static_cast<std::size_t>(scene()->sceneRect().width())};
	std::size_t height{static_cast<std::size_t>(scene()->sceneRect().height())};

	QPen darkGrayPen(Qt::darkGray);
	darkGrayPen.setWidth(2);

	QPen redPen(Qt::red);
	redPen.setWidth(2);

	painter->setPen(darkGrayPen);

	auto audioData{AudioFile::GetInstance().GetAudioData()};
	auto transients{AudioFile::GetInstance().GetTransients()};
	std::size_t transientCount{0};
	for(auto transient : transients)
	{
		if(transientCount != 0)
		{
			if(transientCount == activeTransientNumber_) { painter->setPen(redPen); }
			else { painter->setPen(darkGrayPen); }

			std::size_t xPosition{static_cast<std::size_t>(static_cast<double>(transient) / static_cast<double>(audioData.size()) * static_cast<double>(width) + 0.5)};
			QLine transientLine(xPosition, 0, xPosition, height);
			painter->drawLine(QLine(xPosition, 0, xPosition, height));
		}

		++transientCount;
	}
}

void WaveformGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /* widget */)
{
	if(AudioFile::GetInstance().GetWaveFile().get())
	{
		painter->setPen(QPen(Qt::darkBlue));
		painter->setBrush(Qt::darkBlue);
		painter->drawPolygon(CreateWaveformPolygon());

		DrawTransientLines(painter);
	}
}

void WaveformGraphicsItem::SetActiveTransient(std::size_t activeTransientNumber)
{
	activeTransientNumber_ = activeTransientNumber;
	update();
}
