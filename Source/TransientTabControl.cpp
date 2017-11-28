#include "TransientTabControl.h"

#include <QTabWidget>
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
#include <Utilities/Stringify.h>

struct TransientTabControl::PointSettings
{
	PointSettings( std::string label, std::size_t point, double value) :
		label_(label), point_(point), value_(value) { }
	std::string label_;
	std::size_t point_;
	double value_;
};

TransientTabControl::TransientTabControl()
{

}

void TransientTabControl::AddControl(QHBoxLayout* hBoxLayout)
{
	tabControl_ = new QTabWidget();
	tabControl_->setObjectName(QStringLiteral("TabControl"));
	tabControl_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	hBoxLayout->addWidget(tabControl_);

	AddNewTab("Transient 1");
	AddNewTab("Transient 2");

	tabControl_->setCurrentIndex(0);
}

void TransientTabControl::AddNewTab(const std::string& tabName)
{
	// Create the new tab
	auto tab = new QWidget();
	tab->setObjectName(tabName.c_str());
	tabControl_->addTab(tab, QString(tabName.c_str()));

	// Add the contents of the tab
	auto tabLayout = new QHBoxLayout(tab);
	AddTabControls(tabLayout);
}

void TransientTabControl::AddTabControls(QHBoxLayout* tabLayout)
{
	auto controlLayout = new QVBoxLayout();

	tabLayout->addLayout(controlLayout);
	AddSamplePosition(controlLayout);
	AddLevelGroupBox(controlLayout);
	AddPointSettings(controlLayout, PointSettings("Peak", 12, 0.7423));
	AddPointSettings(controlLayout, PointSettings("Valley", 4, 0.3423));
	controlLayout->addStretch();
	tabLayout->addLayout(controlLayout);
	AddChart(tabLayout);
}

void TransientTabControl::AddSamplePosition(QVBoxLayout* controlLayout)
{
	auto samplePosition = new QLabel();
	samplePosition->setText("Transient Sample Position: 2,123,426");
	controlLayout->addWidget(samplePosition);
}

void TransientTabControl::AddLevelGroupBox(QVBoxLayout* controlLayout)
{
	auto groupBox = new QGroupBox();

	auto levelTitle = new QLabel();
	levelTitle->setText(QObject::tr("<b>Level: </b>"));

	auto firstRadio = new QRadioButton(("First"));
	auto secondRadio = new QRadioButton(("Second"));
	auto thirdRadio = new QRadioButton(("Third"));

	firstRadio->setChecked(true);

	auto radioButtonLayout = new QHBoxLayout;
	radioButtonLayout->addWidget(levelTitle);
	radioButtonLayout->addWidget(firstRadio);
	radioButtonLayout->addWidget(secondRadio);
	radioButtonLayout->addWidget(thirdRadio);

	groupBox->setLayout(radioButtonLayout);

	controlLayout->addWidget(groupBox);
}

void TransientTabControl::AddPointSettings(QVBoxLayout* vBoxLayout, PointSettings&  pointSettings)
{
	// Format the given values into strings
	auto label{Utilities::Stringify("<b>") + Utilities::Stringify(pointSettings.label_) + Utilities::Stringify("</b>")};
	auto point{Utilities::Stringify("Point: ") + Utilities::Stringify(pointSettings.point_)};
	auto value{Utilities::Stringify("Value: ") + Utilities::Stringify(pointSettings.value_)};

	// Create the groupbox
	auto groupBox = new QGroupBox();
	vBoxLayout->addWidget(groupBox);

	auto qGridLayout = new QGridLayout();

	// Add the label
	auto labelWidget = new QLabel();
	labelWidget->setText(QObject::tr(label.c_str()));
	qGridLayout->addWidget(labelWidget, 0, 0);

	// Add the point
	auto pointWidget = new QLabel();
	pointWidget->setText(point.c_str());
	pointWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(pointWidget, 0, 1);

	// Add the value
	auto valueWidget = new QLabel();
	valueWidget->setText(value.c_str());
	valueWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	qGridLayout->addWidget(valueWidget, 0, 2);

	groupBox->setLayout(qGridLayout);
}

void TransientTabControl::AddChart(QHBoxLayout* tabLayout)
{
	auto *series = new QtCharts::QLineSeries();
	series->append(0, 0.1);
	series->append(1, 0.2);
	series->append(2, 0.3);
	series->append(3, 0.4);
	series->append(4, 0.5);
	series->append(5, 0.6);
	series->append(6, 0.7);
	series->setColor(Qt::darkBlue);
	series->setPen(QPen(Qt::darkBlue, 2));
	series->setPointsVisible();

	auto chart = new QtCharts::QChart();
	chart->layout()->setContentsMargins(0, 0, 0, 0);
	chart->setBackgroundRoundness(0);
	chart->legend()->hide();
	chart->addSeries(series);

	auto *axisX = new QtCharts::QValueAxis;
	axisX->setLabelFormat("%d");
	axisX->setTickCount(7);
	axisX->setLinePenColor(series->pen().color());

	auto axisY = new QtCharts::QValueAxis;
	axisY->setLinePenColor(series->pen().color());
	axisY->setRange(0, 1);

	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisX);
	series->attachAxis(axisY);

	auto chartView = new QtCharts::QChartView(chart);

	tabLayout->addWidget(chartView);
}
