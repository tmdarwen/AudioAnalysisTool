#include "TransientChart.h"
#include "AudioFile.h"
#include "WaveformView.h"
#include "Mediator.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QGraphicsLayout>
#include <algorithm>

TransientChart::TransientChart(QHBoxLayout* tabLayout)
{
	chartSeriesData_ = new QtCharts::QLineSeries();

	chartSeriesData_->setColor(Qt::darkBlue);
	chartSeriesData_->setPen(QPen(Qt::darkBlue, 2));
	chartSeriesData_->setPointsVisible();

	auto chart = new QtCharts::QChart();
	chart->layout()->setContentsMargins(0, 0, 0, 0);
	chart->setBackgroundRoundness(0);
	chart->legend()->hide();
	chart->addSeries(chartSeriesData_);

	axisX_ = new QtCharts::QValueAxis();
	axisX_->setLabelFormat("%d");
	axisX_->setTickCount(7);
	axisX_->setLinePenColor(chartSeriesData_->pen().color());
	axisX_->setRange(0, 20);

	auto axisY = new QtCharts::QValueAxis;
	axisY->setLinePenColor(chartSeriesData_->pen().color());
	axisY->setRange(0, 1);

	chart->addAxis(axisX_, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	chartSeriesData_->attachAxis(axisX_);
	chartSeriesData_->attachAxis(axisY);

	auto chartView = new QtCharts::QChartView(chart);
	chart->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	tabLayout->addWidget(chartView);
}

void TransientChart::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void TransientChart::SetFirstLevelStepSize(std::size_t newFirstLevelStepSize)
{
	firstLevelStepSize_ = newFirstLevelStepSize;
}

void TransientChart::SetPointCount(std::size_t pointCount)
{
	pointsInChart_ = pointCount;
}

void TransientChart::Update(std::size_t peakTableStart, std::size_t peakTableEnd)
{
	auto peakValues{AudioFile::GetInstance().GetPeakValues()};

	// Calculate chart start/end positions using the visible points from the peak table
	auto chartPositions{CalculateStartAndEndPositions(peakTableStart, peakTableEnd)};

	// Now draw the chart
	chartSeriesData_->clear();
	for(std::size_t i{chartPositions.first}; i <= chartPositions.second; ++i)
	{
		chartSeriesData_->append(i, peakValues[i]);
	}
	axisX_->setRange(chartPositions.first, chartPositions.second);

	// Update the waveform to show the part of waveform we're analyzing
	mediator_->UpdateWaveformAnalysisArea(chartPositions.first * firstLevelStepSize_, chartPositions.second * firstLevelStepSize_);
}

// We use values from the peak table to generate a new chart view
std::pair<std::size_t, std::size_t> TransientChart::CalculateStartAndEndPositions(std::size_t chartPeakStart, std::size_t chartPeakEnd)
{
	auto peakValues{AudioFile::GetInstance().GetPeakValues()};
	auto maxPeakEndPoint{peakValues.size() - 1};

	std::size_t adjustedPeakStart{chartPeakStart};
	std::size_t adjustedPeakEnd{std::min(chartPeakEnd, maxPeakEndPoint)};

	// Calculate the chart start/end positions before drawing it
	auto length{adjustedPeakEnd - adjustedPeakStart};
	if(length < pointsInChart_)
	{
		auto startPointPercent{static_cast<double>(adjustedPeakStart) / static_cast<double>(maxPeakEndPoint)};
		auto endPointPercent{static_cast<double>(maxPeakEndPoint - adjustedPeakEnd) / static_cast<double>(maxPeakEndPoint)};

		auto totalPercent{startPointPercent + endPointPercent};

		auto pointsToAdd{pointsInChart_ - length};
		auto centerPosition{adjustedPeakStart + (length * (startPointPercent / totalPercent))};
		auto centerPercent{(centerPosition / static_cast<double>(maxPeakEndPoint))};

		auto pointsToAddToTheLeft{std::size_t(centerPercent * pointsToAdd + 0.5)};
		auto pointsToAddToTheRight{pointsToAdd - pointsToAddToTheLeft};

		adjustedPeakStart = adjustedPeakStart - pointsToAddToTheLeft;
		adjustedPeakEnd += pointsToAddToTheRight;
	}

	return std::pair<std::size_t, std::size_t>(adjustedPeakStart, adjustedPeakEnd);
}