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
		void Redraw(); // Redraws the waveform image
		void Update(); // Just updates the waveform display without redrawing the underlying waveform image
		void DisplayTransients(bool displayTransients);
		void HighlightAnalysisArea(bool highlightAnalysisArea);
		void UpdateAnalysisArea(std::size_t sampleStart, std::size_t sampleEnd);

	private:
		QGraphicsView*        graphicsView_;
		WaveformGraphicsItem* waveformGraphicsItem_;
		QGraphicsScene*       scene_;
};