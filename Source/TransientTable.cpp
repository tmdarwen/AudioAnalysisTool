#include "TransientTable.h"
#include "TransientChart.h"
#include "AudioFile.h"
#include "Mediator.h"
#include <Utilities/Stringify.h>
#include <QScrollBar>
#include <algorithm>
#include <QHeaderView>


QTableWidgetItem* CreateTableItem(const QString& contents)
{
	auto tableItem{new QTableWidgetItem(contents)};
	tableItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
	return tableItem;
}

QTableWidgetItem* CreateTableItemHighlighted(const QString& contents)
{
	auto tableItem{CreateTableItem(contents)};
	tableItem->setBackground(QBrush(Qt::lightGray));
	return tableItem;
}

TransientTable::TransientTable()
{
	QObject::connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(ScrollChanged(int)));

	setColumnCount(3);
	setRowCount(0);

	horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	verticalHeader()->setVisible(false);

	QStringList headerStrings;
	headerStrings << "Point" << "Value" << "Sample";
	setHorizontalHeaderLabels(headerStrings);

	resizeColumnsToContents();
	resizeRowsToContents();
}

void TransientTable::ScrollChanged(int newValue)
{
	if(mediator_)
	{
		mediator_->UpdateTransientChart(this->rowAt(0), this->rowAt(this->height()));
	}
}

void TransientTable::SetFirstLevelStepSize(std::size_t newFirstLevelStepSize)
{
	firstLevelStepSize_ = newFirstLevelStepSize;
}

void TransientTable::SetMediator(Mediator* mediator)
{
	mediator_ = mediator;
}

void TransientTable::RefreshTable()
{
	setRowCount(0); // First clear the chart

	auto peakValues{AudioFile::GetInstance().GetPeakValues()};
	setRowCount(peakValues.size());

	for(std::size_t row{0}; row != peakValues.size(); ++row)
	{
		std::size_t samplePosition{row * firstLevelStepSize_};
		auto rowAsString{QLocale(QLocale::English).toString((int)row)};
		auto samplePositionAsString{QLocale(QLocale::English).toString((int)(samplePosition))};

		if(CheckForPeakSamplePosition(samplePosition))
		{
			setItem(row, 0, CreateTableItemHighlighted(rowAsString));
			setItem(row, 1, CreateTableItemHighlighted(Utilities::Stringify(peakValues[row]).c_str()));
			setItem(row, 2, CreateTableItemHighlighted(samplePositionAsString));
		}
		else
		{
			setItem(row, 0, CreateTableItem(rowAsString));
			setItem(row, 1, CreateTableItem(Utilities::Stringify(peakValues[row]).c_str()));
			setItem(row, 2, CreateTableItem(samplePositionAsString));
		}
	}

	resizeRowsToContents();
	ScrollChanged(0);
}

bool TransientTable::CheckForPeakSamplePosition(std::size_t samplePosition)
{
	auto peakSamplePositions{AudioFile::GetInstance().GetFirstStepPeakPositions()};
	return (std::find(peakSamplePositions.cbegin(), peakSamplePositions.cend(), samplePosition) != peakSamplePositions.cend());
}
