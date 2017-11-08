#include "MainWindow.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <QResizeEvent>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	if(this->objectName().isEmpty())
	{
		this->setObjectName(QStringLiteral("Audio Analysis Tool"));
		setWindowTitle("Audio Analysis Tool");
	}

	this->resize(1000, 640);

	SetupMenuBar();

	SetupCentralWidget();

	SetupTabWidget();

	SetupGraphicsView();

	QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::SetupMenuBar()
{
	menuBar_ = new QMenuBar(this);
	menuBar_->setObjectName(QStringLiteral("menubar"));
	menuBar_->setGeometry(QRect(0, 0, 993, 21));

	menuFile_ = new QMenu(menuBar_);
	menuFile_->setTitle("File");
	menuFile_->setObjectName(QStringLiteral("menuFile"));

	menuAbout_ = new QMenu(menuBar_);
	menuAbout_->setTitle("About");
	menuAbout_->setObjectName(QStringLiteral("menuAbout"));

	actionOpen_ = new QAction(this);
	actionOpen_->setObjectName(QStringLiteral("actionOpen_"));
	actionOpen_->setText("Open");

	actionAbout_ = new QAction(this);
	actionAbout_->setObjectName(QStringLiteral("actionAbout"));
	actionAbout_->setText("About");

	menuBar_->addAction(menuFile_->menuAction());
	menuBar_->addAction(menuAbout_->menuAction());
	menuFile_->addAction(actionOpen_);
	menuAbout_->addAction(actionAbout_);

	this->setMenuBar(menuBar_);
}

void MainWindow::SetupCentralWidget()
{
	centralWidget_ = new QWidget(this);
	centralWidget_->setObjectName(QStringLiteral("centralWidget"));
	this->setCentralWidget(centralWidget_);
}

void MainWindow::SetupTabWidget()
{
	tabWidget_ = new QTabWidget(centralWidget_);
	tabWidget_->setObjectName(QStringLiteral("MyWidget"));
	tabWidget_->setGeometry(QRect(0, 280, 1001, 321));

	dummyTab1_ = new QWidget();
	dummyTab1_->setObjectName(QStringLiteral("tab1"));
	tabWidget_->addTab(dummyTab1_, QString("Dummy Tab 1"));

	dummyTab2_ = new QWidget();
	dummyTab2_->setObjectName(QStringLiteral("tab2"));
	tabWidget_->addTab(dummyTab2_, QString("Dummy Tab 2"));

	tabWidget_->setCurrentIndex(0);
}

void MainWindow::SetupGraphicsView()
{
	graphicsView_ = new QGraphicsView(centralWidget_);
	graphicsView_->setObjectName(QStringLiteral("graphicsView"));
	graphicsView_->setGeometry(QRect(0, 0, 1021, 281));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	auto newSize = event->size();
}
