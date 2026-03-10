#include <QApplication>
#include <mainwindow.h>





// This is the starting point of the whole program.
int main (int argc, char *argv[]){
	
	// QApplication manages the app's control flow and main settings.
	// It is required for any Qt app that uses a GUI.
	QApplication app(argc, argv);

	// We create an instance of our MainWindow class.
	// This is where all our toolbars and the canvas are initialized.
	MainWindow window;


	// By default, windows are hidden. This command makes it visible on the screen.
	window.show();

	// app.exec() starts the "Event Loop".
	// This keeps the program running and waiting for user input (like mouse clicks).
	// The program only stops and returns once the user closes the window.
	return app.exec();
	
}

