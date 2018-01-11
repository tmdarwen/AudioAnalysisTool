#pragma once

#include <QTableWidget>

class Mediator;

class TransientTable : public QTableWidget
{
	Q_OBJECT

	public:
		TransientTable();

		void SetMediator(Mediator* mediator);
		void SetFirstLevelStepSize(std::size_t newFirstLevelStepSize);

		void RefreshTable();

	public slots:
		void ScrollChanged(int newValue);

	private:
		bool CheckForPeakSamplePosition(std::size_t samplePosition);
		Mediator* mediator_{nullptr};
		std::size_t firstLevelStepSize_{512};
};