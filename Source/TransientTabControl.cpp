#include "TransientTabControl.h"

#include <QTabWidget>
#include <QWidget>
#include <QHBoxLayout>

TransientTabControl::TransientTabControl()
{

}

void TransientTabControl::AddControl(QHBoxLayout* hBoxLayout)
{
	tabWidget_ = new QTabWidget();
	tabWidget_->setObjectName(QStringLiteral("MyWidget"));
	tabWidget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	hBoxLayout->addWidget(tabWidget_);

	dummyTab1_ = new QWidget();
	dummyTab1_->setObjectName(QStringLiteral("tab1"));
	tabWidget_->addTab(dummyTab1_, QString("Dummy Tab 1"));

	dummyTab2_ = new QWidget();
	dummyTab2_->setObjectName(QStringLiteral("tab2"));
	tabWidget_->addTab(dummyTab2_, QString("Dummy Tab 2"));

	tabWidget_->setCurrentIndex(0);
}
