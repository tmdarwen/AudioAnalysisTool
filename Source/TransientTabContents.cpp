#include "TransientTabContents.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QGraphicsLayout>
#include <QPen>
#include <QLocale>
#include <Utilities/Stringify.h>
#include <AudioFile.h>
#include <Windows.h>

TransientTabContents::TransientTabContents(QWidget* parent, std::size_t tabNumber) : parent_{parent}, tabNumber_{tabNumber}
{
	auto tabLayout = new QHBoxLayout(parent_);
	AddControls(tabLayout);
}

void TransientTabContents::AddControls(QHBoxLayout* tabLayout)
{
	auto controlLayout = new QVBoxLayout();

	tabLayout->addLayout(controlLayout);

	AddSamplePosition(controlLayout);

	AddPointSettings(controlLayout, "Peak");

	AddPointSettings(controlLayout, "Valley");

	controlLayout->addStretch();

	tabLayout->addLayout(controlLayout);

	AddChart(tabLayout);
}

void TransientTabContents::AddSamplePosition(QVBoxLayout* controlLayout)
{
	samplePosition_ = new QLabel("");
	samplePosition_->setText("Transient Sample Position: ");
	controlLayout->addWidget(samplePosition_);
}

void TransientTabContents::AddChart(QHBoxLayout* tabLayout)
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

	tabLayout->addWidget(chartView);
}

void TransientTabContents::AddPointSettings(QVBoxLayout* vBoxLayout, const std::string& type)
{
	// Format the given values into strings
	auto label{Utilities::Stringify("<b>") + Utilities::Stringify(type) + Utilities::Stringify("</b>")};

	// Create the groupbox
	auto groupBox = new QGroupBox();
	vBoxLayout->addWidget(groupBox);

	auto qGridLayout = new QGridLayout();

	// Add the label
	auto labelWidget = new QLabel();
	labelWidget->setText(QObject::tr(label.c_str()));
	qGridLayout->addWidget(labelWidget, 0, 0);

	QLabel *pointLabel;
	QLabel *valueLabel;

	if(type == "Peak")
	{
		pointLabel = peakPointWidget_ = new QLabel();
		valueLabel = peakValueWidget_ = new QLabel();
	}
	else
	{
		pointLabel = valleyPointWidget_ = new QLabel();
		valueLabel = valleyValueWidget_ = new QLabel();
	}

	// Add the point
	pointLabel->setText("Point: 00");
	pointLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(pointLabel, 0, 1);

	// Add the value
	valueLabel->setText("Value: 0.000000");
	valueLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(valueLabel, 0, 2);

	groupBox->setLayout(qGridLayout);
}

void TransientTabContents::Refresh()
{
	refresh_ = true;
}

void TransientTabContents::RefreshSamplePosition()
{
	auto transient{AudioFile::GetInstance().GetTransient(tabNumber_)};
	auto samplePositionQtString{QLocale(QLocale::English).toString((int)transient)}; // Add commas to the sample position value
	auto text{Utilities::Stringify("Transient Sample Position: ") + Utilities::Stringify(samplePositionQtString.toStdString())};
	samplePosition_->setText(text.c_str());
}

void TransientTabContents::RefreshPeakInfo()
{
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};
	auto peakAndValleyInfo{transientDetector->GetPeakAndValleyInfo(tabNumber_, Signal::TransientDetector::Step::FIRST)};

	auto peakPoint{peakAndValleyInfo.GetPeakPoint()};

	auto pointText{Utilities::Stringify("Point: ") + Utilities::Stringify(peakPoint)};
	peakPointWidget_->setText(pointText.c_str());

	auto valueText{Utilities::Stringify("Value: ") + Utilities::Stringify(peakAndValleyInfo.GetPlottedPoints()[peakPoint])};
	peakValueWidget_->setText(valueText.c_str());
}

void TransientTabContents::RefreshValleyInfo()
{
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};
	auto peakAndValleyInfo{transientDetector->GetPeakAndValleyInfo(tabNumber_, Signal::TransientDetector::Step::FIRST)};

	auto valleyPoint{peakAndValleyInfo.GetValleyPoint()};

	auto pointText{Utilities::Stringify("Point: ") + Utilities::Stringify(valleyPoint)};
	valleyPointWidget_->setText(pointText.c_str());

	auto valueText{Utilities::Stringify("Value: ") + Utilities::Stringify(peakAndValleyInfo.GetPlottedPoints()[valleyPoint])};
	valleyValueWidget_->setText(valueText.c_str());
}

void TransientTabContents::RefreshChart()
{
	auto transientDetector{AudioFile::GetInstance().GetTransientDetector()};
	auto peakAndValleyInfo{transientDetector->GetPeakAndValleyInfo(tabNumber_, Signal::TransientDetector::Step::FIRST)};

	chartSeriesData_->clear();

	std::size_t xPos{0};
	for(auto point = peakAndValleyInfo.GetPlottedPoints().begin(); point != peakAndValleyInfo.GetPlottedPoints().end(); ++point)
	{
		chartSeriesData_->append(xPos, *point);
		++xPos;
	}

	axisX_->setRange(0, xPos - 1);
}

void TransientTabContents::Activated()
{
	if(refresh_)
	{
		RefreshSamplePosition();
		RefreshPeakInfo();
		RefreshValleyInfo();
		RefreshChart();
		refresh_ = false;
	}
}