#pragma once

class QTabWidget;
class QWidget;
class QHBoxLayout;

class TransientTabControl
{
	public:
		TransientTabControl();
		void AddControl(QHBoxLayout* hBoxLayout);

	private:
		QTabWidget*     tabWidget_;
		QWidget*        dummyTab1_;
		QWidget*        dummyTab2_;
};