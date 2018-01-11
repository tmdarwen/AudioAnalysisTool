#include "MainWindow.h"
#include "AudioFile.h"
#include <Utilities/Stringify.h>

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QResizeEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

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
		this->setObjectName(QStringLiteral("AudioAnalysisTool"));
		setWindowTitle("Audio Analysis Tool");
	}

	this->resize(startingWidth_, startingHeight_);
	SetupMenuBar();
	SetupCentralWidget();
	SetupMediator();
}

MainWindow::~MainWindow()
{

}

void MainWindow::SetupMediator()
{
	mediator_.AddTransientView(transientDetection_.GetTransientView());
	mediator_.AddWaveformView(&waveformView_);
	transientDetection_.SetMediator(&mediator_);
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
				   "<p>Sorry, audio input files are currently restricted to mono, 16 bit<br>"
				   "uncompressed wave files between 1 and 30 seconds in length."));
			return;
		}

		AudioFile::GetInstance().Initialize(waveFileName);
		RefreshUIWithNewFile();
	}
}

void MainWindow::RefreshUIWithNewFile()
{
	waveformView_.Redraw();
	transientDetection_.ResetSettingsToDefaults();
	transientDetection_.Update();
}

void MainWindow::About()
{
	// &nbsp's because I think a wider dialog box looks a little better
	std::string content{Utilities::Stringify("<h2>Audio Analysis Tool</h2>"
		"<p>A tool to... wait for it ...analyze audio. &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;"
		"<p>Copyright &copy; 2017-2018 Terence M. Darwen<br>"
		"More Info: <a href=http://www.tmdarwen.com>tmdarwen.com</a>"
		"<p>Version: ") + Utilities::Stringify(MACRO_TO_STRING(VERSION_NUMBER)) + Utilities::Stringify("<br>") + 
		Utilities::Stringify("Build: ") + Utilities::Stringify(MACRO_TO_STRING(BUILD_NUMBER)) + Utilities::Stringify("<br>") + 
		Utilities::Stringify("Built: ") + Utilities::Stringify(__DATE__ ) + Utilities::Stringify(" ") + Utilities::Stringify(__TIME__)};

	QMessageBox::about(this, tr("Audio Analysis Tool"), tr(content.c_str()));
}

void MainWindow::SetupMenuBar()
{
	menuBar_ = new QMenuBar(this);
	menuBar_->setObjectName(QStringLiteral("MenuBar"));
	menuBar_->setGeometry(QRect(0, 0, startingWidth_, 21));

	menuFile_ = new QMenu(menuBar_);
	menuFile_->setTitle("File");
	menuFile_->setObjectName(QStringLiteral("MenuFile"));

	menuAbout_ = new QMenu(menuBar_);
	menuAbout_->setTitle("About");
	menuAbout_->setObjectName(QStringLiteral("MenuAbout"));

	actionOpen_ = new QAction(this);
	actionOpen_->setObjectName(QStringLiteral("ActionOpen"));
	actionOpen_->setText("Open");
	connect(actionOpen_, SIGNAL(triggered()), this, SLOT(OpenFile()));

	actionAbout_ = new QAction(this);
	actionAbout_->setObjectName(QStringLiteral("ActionAbout"));
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
	centralWidget_->setObjectName(QStringLiteral("CentralWidget"));
	this->setCentralWidget(centralWidget_);

	// The main display is a vertical layout with two rows.  The first (top) 
	// row contains the waveform and the second (bottom) row contains 
	// the tab control.

	auto vBoxLayout = new QVBoxLayout(centralWidget_);
	
	waveformView_.AddControl(vBoxLayout);
	tabControl_.AddControl(vBoxLayout);

	auto tabWidget{tabControl_.AddTab("Transient Detection")};

	transientDetection_.AddControls(tabWidget);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	auto newSize = event->size();
	waveformView_.Resize(newSize.width(), newSize.height() / 2);
}