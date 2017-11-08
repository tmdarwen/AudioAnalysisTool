#pragma once

#include <QMainWindow>

class QMenuBar;
class QMenu;
class QMenu;
class QAction;
class QAction;
class QWidget;
class QTabWidget;
class QWidget;
class QWidget;
class QGraphicsView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void resizeEvent(QResizeEvent *event);

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
};