#include <TransientTabControl.h>
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

TransientTabControl::TransientTabControl()
{
	QObject::connect(this, SIGNAL(currentChanged(int)), this, SLOT(CurrentChangedSlot(int)));
}

void TransientTabControl::CurrentChangedSlot(int index)
{
	if(tabContents_.size() > index)
	{
		tabContents_[index]->Activated();
	}
}

void TransientTabControl::AddControl(QHBoxLayout* hBoxLayout)
{
	setObjectName(QStringLiteral("TabControl"));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	hBoxLayout->addWidget(this);

	AddTransientTabs();
}

void TransientTabControl::Reset()
{
	while((AudioFile::GetInstance().GetTransientCount() - 1) != count())
	{
		if((AudioFile::GetInstance().GetTransientCount() - 1) > count())
		{
			AddNewTab(count() + 1);
		}
		else if((AudioFile::GetInstance().GetTransientCount() - 1) < count())
		{
			removeTab(count() - 1);
			tabContents_.pop_back();
		}
	}

	// Tell the tab contents that they need to refresh their info
	for(auto tab{tabContents_.begin()}; tab != tabContents_.end(); ++tab)
	{
		(*tab)->Refresh();
	}

	// Set view to transient 1 (As long as at least one tab exists)
	if(count())
	{
		setCurrentIndex(0);
		tabContents_[0]->Activated();
	}
}

void TransientTabControl::AddTransientTabs()
{
	for(std::size_t i = 1; i < AudioFile::GetInstance().GetTransientCount(); ++i)
	{
		AddNewTab(i);
	}
}

void TransientTabControl::AddNewTab(std::size_t transientNumber)
{
	// Create the new tab
	auto tab = new QWidget();
	auto tabName{(Utilities::Stringify("Transient ") + Utilities::Stringify(transientNumber))};
	tab->setObjectName(QString(tabName.c_str()));
	addTab(tab, QString(tabName.c_str()));

	// Add the contents of the tab
	tabContents_.emplace_back(new TransientTabContents(tab, transientNumber));
}

void TransientTabControl::ResetHeight(std::size_t newHeight)
{
	setFixedHeight(newHeight);
}

