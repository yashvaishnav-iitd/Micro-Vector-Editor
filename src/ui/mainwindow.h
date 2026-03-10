#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "canvas.h"

// This is the main window of our application. It acts as the container 
// for the drawing canvas and all the toolbars.
class MainWindow : public QMainWindow{
	Q_OBJECT

	public:
		//Constructor for the window.
		explicit MainWindow(QWidget* par = nullptr) ;

		// Destructor to clean up resources when the window is closed.
		~MainWindow();

	private:
		// This is a pointer to the custom drawing area we built.
		Canvas* canvas;

		// A private function to initialize all the UI components.
		void setupInterface();

		//Helpers
		// Creates the vertical toolbar for shape selection (Rect, Circle, etc.).
		void setupLeftToolbar();

		// Creates the horizontal toolbar for actions (Undo, Redo, Save, Colors)
		void setupTopToolbar();
		
};

#endif
