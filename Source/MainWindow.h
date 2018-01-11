#pragma once

#include <QMainWindow>
#include <memory>
#include <WaveFile/WaveFileReader.h>
#include <TransientDetection.h>
#include "WaveformView.h"
#include "TabControl.h"
#include "Mediator.h"

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
		void SetupMediator();
		void RefreshUIWithNewFile();

		QMenuBar*       menuBar_;
		QMenu*          menuFile_;
		QMenu*          menuAbout_;
		QAction*        actionOpen_;
		QAction*        actionAbout_;
		QWidget*        centralWidget_;

		std::unique_ptr<WaveFile::WaveFileReader> waveFileReader_;

		WaveformView waveformView_;
		TabControl tabControl_;
		TransientDetection transientDetection_;
		Mediator mediator_;

		const int startingWidth_{1000};
		const int startingHeight_{600};
};
