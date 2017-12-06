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
		void HighlightTransient(std::size_t transientNumber);
		void DisplayTransients(bool displayTransients);

	private:
		QGraphicsView*        graphicsView_;
		WaveformGraphicsItem* waveformGraphicsItem_;
		QGraphicsScene*       scene_;
};