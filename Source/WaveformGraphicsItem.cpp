#include "WaveformGraphicsItem.h"
#include "AudioFile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QImage>
#include <algorithm>

WaveformGraphicsItem::WaveformGraphicsItem() : activeTransientNumber_{1}
{
}

WaveformGraphicsItem::~WaveformGraphicsItem()
{
}

void WaveformGraphicsItem::HighlightAnalysisArea(bool highlightAnalysisArea)
{
	highlightAnalysisArea_ = highlightAnalysisArea;
}

QRectF WaveformGraphicsItem::boundingRect() const
{
	return scene()->sceneRect();
}

QPolygon WaveformGraphicsItem::CreateWaveformPolygon()
{
	QPolygon polygon;
	std::vector<QPoint> lowerPoints;

	auto audioData{AudioFile::GetInstance().GetAudioData().GetData()};

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
	if(!displayTransients_)
	{
		return;
	}

	std::size_t width{static_cast<std::size_t>(scene()->sceneRect().width())};
	std::size_t height{static_cast<std::size_t>(scene()->sceneRect().height())};

	QPen orangePen(QColor(255, 128, 64));
	orangePen.setWidth(2);

	painter->setPen(orangePen);

	auto audioData{AudioFile::GetInstance().GetAudioData()};
	auto transients{AudioFile::GetInstance().GetTransients()};
	std::size_t transientCount{0};
	for(auto transient : transients)
	{
		if(transientCount != 0)
		{
			std::size_t xPosition{static_cast<std::size_t>(static_cast<double>(transient) / static_cast<double>(audioData.GetSize()) * static_cast<double>(width) + 0.5)};
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
		std::size_t currentWidth{static_cast<std::size_t>(scene()->sceneRect().width())};
		std::size_t currentHeight{static_cast<std::size_t>(scene()->sceneRect().height())};

		if(currentWidth != previousWidth_ || currentHeight != previousHeight_)
		{
			UpdateWaveformImage();
			previousWidth_ = currentWidth;
			previousHeight_ = currentHeight;
		}

		painter->drawImage(0, 0, *(waveformImage_.get()));

		AddInvertedArea(painter);

		DrawTransientLines(painter);
	}
}

void WaveformGraphicsItem::AddInvertedArea(QPainter* painter)
{
	if(highlightAnalysisArea_ == false)
	{
		return;
	}

	std::size_t currentWidth{static_cast<std::size_t>(scene()->sceneRect().width())};
	std::size_t currentHeight{static_cast<std::size_t>(scene()->sceneRect().height())};

	auto startPercent{static_cast<double>(analysisSampleStart_) / static_cast<double>(AudioFile::GetInstance().GetSampleCount())};
	auto endPercent{static_cast<double>(analysisSampleEnd_) / static_cast<double>(AudioFile::GetInstance().GetSampleCount())};
	if(endPercent > 100.0)
	{
		endPercent = 100.0;
	}

	auto startPixelX{static_cast<std::size_t>((startPercent * currentWidth) + 0.5)};
	auto endPixelX{static_cast<std::size_t>((endPercent * currentWidth) + 0.5)};

	auto length{endPixelX - startPixelX};

	painter->drawImage(startPixelX, 0, *(waveformImageInverted_.get()), startPixelX, 0, length, currentHeight);
}

void WaveformGraphicsItem::UpdateWaveformImage()
{
	std::size_t currentWidth{static_cast<std::size_t>(scene()->sceneRect().width())};
	std::size_t currentHeight{static_cast<std::size_t>(scene()->sceneRect().height())};

	waveformImage_.reset(new QImage(currentWidth, currentHeight, QImage::Format_RGB32));

	QPainter imagePainter(waveformImage_.get());

	imagePainter.setPen(QPen(Qt::darkBlue));
	imagePainter.setBrush(Qt::darkBlue);
	imagePainter.drawPolygon(CreateWaveformPolygon());

	waveformImageInverted_.reset(new QImage(*waveformImage_));
	waveformImageInverted_->invertPixels();
}

void WaveformGraphicsItem::DisplayTransients(bool displayTransients)
{
	displayTransients_ = displayTransients;
	update();
}

void WaveformGraphicsItem::UpdateAnalysisWindow(std::size_t sampleStart, std::size_t sampleEnd)
{
	analysisSampleStart_ = sampleStart;
	analysisSampleEnd_ = sampleEnd;
}
