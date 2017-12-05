#pragma once

#include <QWidget>

class TransientTabControl;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;

namespace QtCharts
{
	class QLineSeries;
	class QValueAxis;
}

class TransientTabContents : public QWidget
{
	public:
		TransientTabContents(QWidget* parent, std::size_t tabNumber);

		void Refresh();    // Call when tab contents change

		void Activated();  // Call when tab is viewed

	private:
		void AddControls(QHBoxLayout* tabLayout);

		void AddSamplePosition(QVBoxLayout* controlLayout);

		void AddPointSettings(QVBoxLayout* vBoxLayout, const std::string& type);

		void AddChart(QHBoxLayout* tabLayout);

		void RefreshSamplePosition();
		void RefreshPeakInfo();
		void RefreshValleyInfo();
		void RefreshChart();

		std::size_t tabNumber_;
		bool refresh_{true};

		QWidget* parent_;

		QtCharts::QLineSeries* chartSeriesData_;
		QtCharts::QValueAxis* axisX_;

		QLabel* samplePosition_;

		QLabel* peakValueWidget_;
		QLabel* peakPointWidget_;

		QLabel* valleyValueWidget_;
		QLabel* valleyPointWidget_;

};