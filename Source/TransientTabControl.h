#pragma once

#include <string>

class QTabWidget;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;

class TransientTabControl
{
	public:
		TransientTabControl();
		void AddControl(QHBoxLayout* hBoxLayout);

	private:
		struct PointSettings;

		void AddNewTab(const std::string& tabName);
		void AddTabControls(QHBoxLayout* layout);
		void AddSamplePosition(QVBoxLayout* controlLayout);
		void AddLevelGroupBox(QVBoxLayout* controlLayout);
		void AddPointSettings(QVBoxLayout* vBoxLayout, PointSettings&  pointSettings);
		void AddChart(QHBoxLayout* tabLayout);

		QTabWidget*  tabControl_;
};