#include "MainWindow.h"
#include "Waveform.h"
#include "AudioFile.h"
#include <Utilities/Stringify.h>

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <QResizeEvent>
#include <QGraphicsView>
#include <QFileDialog>
#include <QMessageBox>


#ifndef VERSION_NUMBER
#define VERSION_NUMBER Non-Production Build
#endif

#ifndef BUILD_NUMBER
#define BUILD_NUMBER Non-Production Build
#endif

#define MACRO_TO_STRING_INDIRECT(s) #s
#define MACRO_TO_STRING(s) MACRO_TO_STRING_INDIRECT(s)


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	if(this->objectName().isEmpty())
	{
		this->setObjectName(QStringLiteral("Audio Analysis Tool"));
		setWindowTitle("Audio Analysis Tool");
	}

	this->resize(startingWidth_, startingHeight_);

	SetupMenuBar();

	SetupCentralWidget();

	SetupTabWidget();

	SetupGraphicsView();

	QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::OpenFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wave File"), ".", tr("Wave Files (*.wav)"));
	if(!fileName.isEmpty())
	{
		std::string waveFileName{fileName.toUtf8().constData()};

		WaveFile::WaveFileReader waveFile(waveFileName);
		auto seconds{waveFile.GetSampleCount() / waveFile.GetSampleRate()};
		if(waveFile.GetChannels() != 1 || waveFile.GetBitsPerSample() != 16 || seconds < 1 || seconds > 30)
		{
			QMessageBox::about(this, tr("Audio Analysis Tool"),
				tr("<h3>Cannot load audio file</h3>"
				   "<p>Sorry, audio input files are restricted to mono, 16 bit<br>"
				   "uncompressed wave files between 1 and 30 seconds in length."));
			return;
		}

		AudioFile::GetInstance().Initialize(waveFileName);
		waveform_->update();
	}
}

void MainWindow::About()
{
	std::string content{Utilities::Stringify("<h2>Audio Analysis Tool</h2>"
			"<p>A tool to... wait for it ...analyze audio."
			"<p>Copyright &copy; 2017 Terence M. Darwen - tmdarwen.com<br>"
			"Version: ") + Utilities::Stringify(MACRO_TO_STRING(VERSION_NUMBER)) + Utilities::Stringify("<br>") + 
			Utilities::Stringify("Build: ") + Utilities::Stringify(MACRO_TO_STRING(BUILD_NUMBER)) + Utilities::Stringify("<br>") + 
			Utilities::Stringify("Built: ") + Utilities::Stringify(__DATE__ ) + Utilities::Stringify(" ") + Utilities::Stringify(__TIME__)};

	QMessageBox::about(this, tr("Audio Analysis Tool"), tr(content.c_str()));
}


void MainWindow::SetupMenuBar()
{
	menuBar_ = new QMenuBar(this);
	menuBar_->setObjectName(QStringLiteral("menubar"));
	menuBar_->setGeometry(QRect(0, 0, startingWidth_, 21));

	menuFile_ = new QMenu(menuBar_);
	menuFile_->setTitle("File");
	menuFile_->setObjectName(QStringLiteral("menuFile"));

	menuAbout_ = new QMenu(menuBar_);
	menuAbout_->setTitle("About");
	menuAbout_->setObjectName(QStringLiteral("menuAbout"));

	actionOpen_ = new QAction(this);
	actionOpen_->setObjectName(QStringLiteral("actionOpen_"));
	actionOpen_->setText("Open");
	connect(actionOpen_, SIGNAL(triggered()), this, SLOT(OpenFile()));

	actionAbout_ = new QAction(this);
	actionAbout_->setObjectName(QStringLiteral("actionAbout"));
	actionAbout_->setText("About");
	connect(actionAbout_, SIGNAL(triggered()), this, SLOT(About()));

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
	tabWidget_->setGeometry(QRect(0, 280, startingWidth_, startingHeight_ / 2));

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
	waveform_ = new Waveform;
	waveform_->setPos(QPoint(0, 0));

	scene_ = new QGraphicsScene(0, 0, startingWidth_, startingHeight_ / 2);
	scene_->addItem(waveform_);
	scene_->setSceneRect(0, 0, startingWidth_, startingHeight_ / 2);

	graphicsView_ = new QGraphicsView(centralWidget_);
	graphicsView_->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
	graphicsView_->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
	graphicsView_->setGeometry(QRect(0, 0, startingWidth_, startingHeight_ / 2));
	graphicsView_->setScene(scene_);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	auto newSize = event->size();

	graphicsView_->setGeometry(QRect(0, 0, newSize.width(), newSize.height()/2));

	scene_->setSceneRect(0, 0, newSize.width(), newSize.height()/2);

	tabWidget_->setGeometry(QRect(0, newSize.height()/2, newSize.width(), newSize.height()/2));
}
