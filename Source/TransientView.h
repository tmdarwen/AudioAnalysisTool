#pragma once

#include <QWidget>

class QHBoxLayout;
class TransientTable;
class TransientChart;
class Mediator;

class TransientView
{
	public:
		TransientView();

		void AddControls(QHBoxLayout* hBoxLayout);
		void Update();
		void SetMediator(Mediator* mediator);
		void SetFirstLevelStepSize(std::size_t newFirstLevelStepSize);
		void SetChartPointCount(std::size_t newPointCount);

		TransientTable* GetTransientTable();
		TransientChart* GetTransientChart();

	private:
		TransientChart* transientChart_;
		TransientTable* transientTable_;
		Mediator* mediator_;
};