#include "mainwindow.h"
#include "parser.h"
#include <QAction>
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>


// This function builds the top toolbar and connects all the "Action" buttons to their logic.
void MainWindow::setupTopToolbar() {
    QToolBar* toolbar = new QToolBar("Actions", this);

    addToolBar(Qt::TopToolBarArea, toolbar); 

    toolbar->setMovable(false);     // Keeps the UI clean by locking the toolbar in place.

    // Colors & Width
    connect(toolbar->addAction("Stroke"), &QAction::triggered, [this](){        // Opens the standard Windows/Mac color picker for the shape border.

        QColor c = QColorDialog::getColor(Qt::black, this);

        if(c.isValid()) {
            canvas->setStrokeColor(c);
        }
    });
    
    connect(toolbar->addAction("Fill"), &QAction::triggered, [this](){          // Opens the color picker for the shape interior.
        
        QColor c = QColorDialog::getColor(Qt::transparent, this);
     
        if(c.isValid()) {
            canvas->setFillColor(c);
        }
    });
    
    // Undo/Redo
    toolbar->addSeparator();
    // Directly connects the button click to the Undo/Redo logic in the Canvas.
    connect(toolbar->addAction("Undo"), &QAction::triggered, canvas, &Canvas::undo);        
    connect(toolbar->addAction("Redo"), &QAction::triggered, canvas, &Canvas::redo);

    // File I/O
    toolbar->addSeparator();
    
    connect(toolbar->addAction("Save"), &QAction::triggered, [this](){              // Save Action: Opens a file dialog and uses the Parser to write the SVG.
        
        QString f = QFileDialog::getSaveFileName(this, "Save", "", "*.svg");
        
        if(!f.isEmpty()) {
            Parser::saveSVG(f.toStdString(), canvas);
        }
    });
    
    connect(toolbar->addAction("Load"), &QAction::triggered, [this](){              // Load Action: Wipes the current canvas and uses the Parser to reconstruct shapes from a file.
        
        QString f = QFileDialog::getOpenFileName(this, "Load", "", "*.svg");
        
        if(!f.isEmpty()) { 
            canvas->clear(); 
            Parser::loadSVG(f.toStdString(), canvas); 
            canvas->update(); 
        }
    });

    // --- CLIPBOARD TOOLS ---
    toolbar->addSeparator();

    // 1. Copy Action: Triggers cloning of the selected shape
    connect(toolbar->addAction("Copy"), &QAction::triggered, canvas, &Canvas::copy);

    // 2. Cut Action: Triggers DeleteShapeCommand for undoable removal
    connect(toolbar->addAction("Cut"), &QAction::triggered, canvas, &Canvas::cut);

    // 3. Paste Action: Handles "Paste-Once" for Cut and "Infinite-Paste" for Copy
    connect(toolbar->addAction("Paste"), &QAction::triggered, canvas, &Canvas::paste);

    // --- CANVAS MANAGEMENT ---
    toolbar->addSeparator();

    // Directly connects the button click to the Canvas::clear() logic.
    // This will wipe the shapes and the history stacks.
    connect(toolbar->addAction("Clear All"), &QAction::triggered, canvas, &Canvas::clear);
}


