#include "TransientView.h"
#include <QTableWidget>
#include <QHBoxLayout>
#include <TransientTable.h>
#include <TransientChart.h>
#include <Mediator.h>
#include <QHeaderView>


TransientView::TransientView()
{

}

void TransientView::AddControls(QHBoxLayout* hBoxLayout)
{
	transientTable_ = new TransientTable();
	hBoxLayout->addWidget(transientTable_);

	transientChart_ = new TransientChart(hBoxLayout);
}

void TransientView::Update()
{
	transientTable_->RefreshTable();
}

void TransientView::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
	transientTable_->SetMediator(mediator);
	transientChart_->SetMediator(mediator);
}

TransientTable* TransientView::GetTransientTable()
{
	return transientTable_;
}

TransientChart* TransientView::GetTransientChart()
{
	return transientChart_;
}

void TransientView::SetFirstLevelStepSize(std::size_t newFirstLevelStepSize)
{
	transientTable_->SetFirstLevelStepSize(newFirstLevelStepSize);
	transientChart_->SetFirstLevelStepSize(newFirstLevelStepSize);
}

void TransientView::SetChartPointCount(std::size_t newPointCount)
{
	transientChart_->SetPointCount(newPointCount);
}