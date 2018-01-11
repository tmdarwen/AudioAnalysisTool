#include "WaveformView.h"
#include "WaveformGraphicsItem.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>

WaveformView::WaveformView()
{

}

void WaveformView::AddControl(QVBoxLayout* vBoxLayout)
{
	waveformGraphicsItem_ = new WaveformGraphicsItem;
	waveformGraphicsItem_->setPos(QPoint(0, 0));

	scene_ = new QGraphicsScene();
	scene_->addItem(waveformGraphicsItem_);

	// The scene has to have some size when set.  This size will never be used though as 
	// Resize() will be called at startup.
	scene_->setSceneRect(0, 0, 10, 10);

	graphicsView_ = new QGraphicsView();
	graphicsView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView_->setScene(scene_);

	// The waveform image is a little bigger than the area in which it is displayed.  The following 
	// command keeps it from being vertically scrolled with a mousewheel.
	graphicsView_->verticalScrollBar()->blockSignals(true);

	vBoxLayout->addWidget(graphicsView_);
}

void WaveformView::Resize(int width, int height)
{
	scene_->setSceneRect(0, 0, width, height);
}

void WaveformView::Update()
{
	waveformGraphicsItem_->update();
}

void WaveformView::DisplayTransients(bool displayTransients)
{
	waveformGraphicsItem_->DisplayTransients(displayTransients);
}

void WaveformView::HighlightAnalysisArea(bool highlightAnalysisArea)
{
	waveformGraphicsItem_->HighlightAnalysisArea(highlightAnalysisArea);
	Update();
}

void WaveformView::UpdateAnalysisArea(std::size_t sampleStart, std::size_t sampleEnd)
{
	waveformGraphicsItem_->UpdateAnalysisWindow(sampleStart, sampleEnd);
	Update();
}
