#include "WaveformView.h"
#include "WaveformGraphicsItem.h"

#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

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

void WaveformView::HighlightTransient(std::size_t transientNumber)
{
	waveformGraphicsItem_->SetActiveTransient(transientNumber);
}
