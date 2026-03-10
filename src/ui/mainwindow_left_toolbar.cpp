#include "mainwindow.h"
#include "tool_type.h"
#include <QAction>
#include <QActionGroup> 


// This function builds the vertical toolbar on the left side of the window.
void MainWindow::setupLeftToolbar() {
    
    QToolBar* toolbar = new QToolBar("Tools", this);
    
    addToolBar(Qt::LeftToolBarArea, toolbar);
    
    toolbar->setMovable(false);     // Locking it to the left side for a real editor look.

    // We use a group so that selecting a new tool automatically unselects the old one.
    QActionGroup* group = new QActionGroup(this);

    // This lambda helper saves us from writing the same 'connect' logic 7 times.
    auto add = [&](const QString &n, ToolType tool) {
        
        QAction* a = toolbar->addAction(n);
        
        a->setCheckable(true);          // This makes the button stay "pushed in" when clicked.
        
        a->setActionGroup(group);       // Ensures only one tool in the group is checked at a time.
        
        // When clicked, tell the canvas to switch its internal ToolType.
        connect(a, &QAction::triggered, [this, tool](){ 
            canvas->setTool(tool); 
        });

        // Set 'Select' as the default checked tool
        if(tool == ToolType::Select) {
            a->setChecked(true);
        }
    };

    //Adding the specific tools required by the assignment 
    add("Select", ToolType::Select);                    // For moving and resizing
    toolbar->addSeparator();
    add("Line", ToolType::Line);                        // Standard line tool
    add("Rect", ToolType::Rectangle);                   // Basic rectangle
    add("R-Rect", ToolType::RoundedRectangle);          // The specific SVG rounded rect
    add("Circle", ToolType::Circle);                    // Circle tool
    add("Hexagon", ToolType::Hexagon);                  // Hexagon tool
    add("Draw", ToolType::FreeHand);                    // Freehand sketch (PolyLine)   
    add("Text", ToolType::Text);

}
