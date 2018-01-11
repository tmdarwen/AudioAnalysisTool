#pragma once

#include <cstddef>

class QGraphicsView;
class QGraphicsScene;
class WaveformGraphicsItem;
class QVBoxLayout;

class WaveformView
{
	public:
		WaveformView();
		void AddControl(QVBoxLayout* hBoxLayout);
		void Resize(int width, int height);
		void Update();
		void DisplayTransients(bool displayTransients);
		void HighlightAnalysisArea(bool highlightAnalysisArea);
		void UpdateAnalysisArea(std::size_t sampleStart, std::size_t sampleEnd);

	private:
		QGraphicsView*        graphicsView_;
		WaveformGraphicsItem* waveformGraphicsItem_;
		QGraphicsScene*       scene_;
};