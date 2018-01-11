#pragma once

#include <QWidget>

class QHBoxLayout;
class Mediator;

namespace QtCharts
{
	class QLineSeries;
	class QValueAxis;
}

class TransientChart
{
	public:
		TransientChart(QHBoxLayout* tabLayout);

		void Update(std::size_t chartPeakStart, std::size_t chartPeakEnd);
		void SetMediator(Mediator* mediator);
		void SetFirstLevelStepSize(std::size_t newFirstLevelStepSize);
		void SetPointCount(std::size_t pointCount);

	private:
		std::pair<std::size_t, std::size_t> CalculateStartAndEndPositions(std::size_t chartPeakStart, std::size_t chartPeakEnd);

		std::size_t pointsInChart_{40};

		QtCharts::QLineSeries* chartSeriesData_;
		QtCharts::QValueAxis* axisX_;

		Mediator* mediator_;

		std::size_t firstLevelStepSize_{512};
};
