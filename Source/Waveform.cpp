#include "Waveform.h"
#include "AudioFile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <algorithm>

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
	if(AudioFile::GetInstance().GetWaveFile().get())
	{
		auto waveFile{AudioFile::GetInstance().GetWaveFile()};
		std::size_t width{static_cast<std::size_t>(scene()->sceneRect().width())};
		std::size_t height{static_cast<std::size_t>(scene()->sceneRect().height())};
		std::size_t halfHeight{static_cast<std::size_t>(scene()->sceneRect().height())/2};
		std::size_t samplesPerPixel{waveFile->GetSampleCount() / width};

		auto audioData{waveFile->GetAudioData()[0].GetData()};

		QPolygon polygon;

		for(std::size_t i{0}; i < width; ++i)
		{
			std::size_t currentPosition{i * samplesPerPixel};
			auto minMaxSamples{std::minmax_element(audioData.begin() + currentPosition, audioData.begin() + currentPosition + samplesPerPixel)};

			auto minPoint = halfHeight - (*(minMaxSamples.first) * halfHeight);
			auto maxPoint = halfHeight - (*(minMaxSamples.second) * halfHeight);

			polygon << QPoint(i, minPoint) << QPoint(i, maxPoint);
		}

		painter->setPen(QPen(Qt::darkBlue));
		painter->setBrush(Qt::darkBlue);
		painter->drawPolygon(polygon);
	}
}
