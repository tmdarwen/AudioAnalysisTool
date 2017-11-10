#pragma once

#include <QMainWindow>

class QMenuBar;
class QMenu;
class QAction;
class QWidget;
class QTabWidget;
class QGraphicsView;
class QGraphicsScene;
class Waveform;

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

	private:
		void SetupMenuBar();
		void SetupCentralWidget();
		void SetupTabWidget();
		void SetupGraphicsView();

		QMenuBar*       menuBar_;
		QMenu*          menuFile_;
		QMenu*          menuAbout_;
		QAction*        actionOpen_;
		QAction*        actionAbout_;
		QWidget*        centralWidget_;
		QTabWidget*     tabWidget_;
		QWidget*        dummyTab1_;
		QWidget*        dummyTab2_;
		QGraphicsView*  graphicsView_;
		Waveform*       waveform_;
		QGraphicsScene* scene_;

		const int startingWidth_{1000};
		const int startingHeight_{600};
};