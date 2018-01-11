#pragma once

#include <QWidget>
#include <memory>

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
		std::shared_ptr<TransientChart> GetTransientChart();

	private:
		std::shared_ptr<TransientChart> transientChart_;
		TransientTable* transientTable_;
		Mediator* mediator_;
};