#include "mainwindow.h"


// Constructor: This is where the window starts its setup process.
MainWindow::MainWindow(QWidget* par): QMainWindow(par){

	setupInterface();	// Calls our helper to build the UI.
}

// Destructor: Empty because Qt's parent-child system handles most cleanup.
MainWindow::~MainWindow(){}

// This function organizes the window layout.
void MainWindow::setupInterface(){

	setWindowTitle ( "Micro-Vector Editor");		// The title that appears at the top.

	resize(1000,700);			// Sets the initial window size to a 1000x700 rectangle.

	//Creating the Canvas(Drawing area)
	// We create the Canvas and tell it that 'this' (MainWindow) is its parent.
	canvas= new Canvas(this);

	// The Central Widget is the main area of the window that isn't a toolbar.
	setCentralWidget(canvas);

	//Creating Toolbars
	setupLeftToolbar(); //Vertical drawing tools (Line, Rect, ect.)
	setupTopToolbar(); //Horizontal settings and actions (Undo, Save, ect.)

}
