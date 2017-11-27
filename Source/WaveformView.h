#pragma once

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

	private:
		QGraphicsView*        graphicsView_;
		WaveformGraphicsItem* waveformGraphicsItem_;
		QGraphicsScene*       scene_;
};