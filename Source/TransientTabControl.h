#pragma once

#include <string>
#include <QTabWidget>
#include <TransientTabContents.h>

class QWidget;
class QHBoxLayout;
class QVBoxLayout;

class TransientTabControl : public QTabWidget
{
	Q_OBJECT

	public:
		TransientTabControl();

		void AddControl(QHBoxLayout* hBoxLayout);
		void Reset();

	public slots:
		void CurrentChangedSlot(int index);

	private:
		struct PointSettings;

		void AddTransientTabs();
		void AddNewTab(std::size_t transientNumber);

		std::vector<TransientTabContents*> tabContents_;
};