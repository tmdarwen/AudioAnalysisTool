#pragma once

#include <QGraphicsItem>
#include <QResizeEvent>
#include <memory>

class QPolygon;
class QImage;

class WaveformGraphicsItem : public QGraphicsItem
{
	public:
	    WaveformGraphicsItem();
	    ~WaveformGraphicsItem();

	    QRectF boundingRect() const;
	    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

		void DisplayTransients(bool displayTransients);

		void UpdateAnalysisWindow(std::size_t sampleStart, std::size_t sampleEnd);

		void HighlightAnalysisArea(bool highlightAnalysisArea);

		void Redraw();

	private:
		void UpdateWaveformImage();

		QPolygon CreateWaveformPolygon();
		void DrawTransientLines(QPainter* painter);

		void AddInvertedArea(QPainter* painter);

		bool displayTransients_{false};

		std::size_t analysisSampleStart_;
		std::size_t analysisSampleEnd_;

		std::size_t previousWidth_{0};
		std::size_t previousHeight_{0};

		std::unique_ptr<QImage> waveformImage_;
		std::unique_ptr<QImage> waveformImageInverted_;

		bool highlightAnalysisArea_{false};
		bool redraw_{false};
};
