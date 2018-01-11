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
		void Resize(std::size_t width, std::size_t height);

	private:
		QTabWidget* tabControl_;
};
