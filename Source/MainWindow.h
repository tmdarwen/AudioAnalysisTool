#pragma once

#include <QMainWindow>
#include <memory>
#include <WaveFile/WaveFileReader.h>
#include <TransientDetectionSettings.h>
#include <TransientTabControl.h>
#include <WaveformView.h>

class QMenuBar;
class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void resizeEvent(QResizeEvent *event);

	private slots:
		void OpenFile();
		void About();

	private:
		void SetupMenuBar();
		void SetupCentralWidget();

		TransientDetectionSettings transientDetectionSettings_;
		TransientTabControl transientTabControl_;
		WaveformView waveformView_;

		QMenuBar*       menuBar_;
		QMenu*          menuFile_;
		QMenu*          menuAbout_;
		QAction*        actionOpen_;
		QAction*        actionAbout_;
		QWidget*        centralWidget_;

		std::unique_ptr<WaveFile::WaveFileReader> waveFileReader_;

		const int startingWidth_{1000};
		const int startingHeight_{600};
};