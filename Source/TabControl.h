#pragma once

#include <string>

class QVBoxLayout;
class QTabWidget;
class QWidget;

class TabControl
{
	public:
		TabControl();
		void AddControl(QVBoxLayout* vBoxLayout);
		QWidget* AddTab(const std::string& tabName);

	private:
		QTabWidget* tabControl_;
};
