#ifndef CANVAS_H
#define CANVAS_H


#include "tool_type.h"
#include <QWidget>
#include <vector>
#include <memory>
#include <QPoint>
#include <QColor>
#include "graphics_object.h"
#include <stack>
#include "commands.h"



// Enum to track how the object was added to the clipboard
enum class ClipboardMode {
    NONE,
    COPY_MODE,
    CUT_MODE
};

// This class controls the entire drawing area. It inherits from QWidget so we can draw on it. It handles three big things:
// 1. Mouse events (Clicking and Dragging).
// 2. Storing all the shapes in a list.
// 3. Managing the Undo/Redo stacks.
class Canvas :	public QWidget {
		Q_OBJECT	//Qt macro required for signals and slots to work.
		public:
			// Qt constructor
			explicit Canvas(QWidget *parent = nullptr);
			
			//Deconstructor
			~Canvas () override ;

    		// Sets which tool is currently active (e.g., Pen, Rectangle, Select).
			void setTool(ToolType tool);
			ToolType getTool() const;

			// This is the main function to add a shape. It creates an Undo command and pushes it to the history stack so we can reverse it later.
   			// It takes ownership of the pointer using std::unique_ptr
			void addShape(std::unique_ptr <GraphicsObject> shape);
			
			// Returns a read-only list of shapes. Useful for the Save function so it can read the data without accidentally deleting anything.
			const std::vector<std::unique_ptr<GraphicsObject>>& getShapes() const;

			// These update the current color/width settings. If a shape is selected,
   			 // these functions update that shape immediately (Live Editing).
			void setStrokeColor(const QColor &color);
			void setFillColor(const QColor &color);
			void setStrokeWidth (int width);
			void setShapeColor (GraphicsObject* shape, const QColor &strokeColor, const QColor &fillColor);

			// Standard Undo/Redo functions. They pop commands off the stacks 
    		// and execute them.
			void undo();
			void redo();
			void clear(); //Wipes everything clean;

			// Loops through shapes in reverse to find which one is "on top" 
   			 // at the mouse coordinates. Returns nullptr if we clicked empty space.
			GraphicsObject* getShapeAt(const QPoint& pos);

			//Helper to calculate 8 resize Handles around a box.
			std::vector<QRect> getHandles(const QRect &box) const;

			//Internal Helpers
    		// These are used by Command objects to modify the canvas state without triggering *another* command (preventing infinite loops).
			void addShapeInternal(std::unique_ptr<GraphicsObject> shape);
			std::unique_ptr<GraphicsObject> popShapeInternal();
			GraphicsObject* getLastShape();

			//Clipboard COmmands
			void copy();
			void paste();
			void cut();
			std::unique_ptr<GraphicsObject> extractShapeInternal(GraphicsObject* target);
			
		protected:
			//Qt Events
    		// We override these to implement our custom drawing behavior.
			void paintEvent(QPaintEvent *event) override;
			void mousePressEvent(QMouseEvent *event) override ;
			void mouseMoveEvent (QMouseEvent *event) override ;
			void mouseReleaseEvent (QMouseEvent *event) override;
			
		private:
    		// We use unique_ptr because the Canvas "owns" these shapes.
    		// When the Canvas is destroyed, these shapes are automatically deleted.
			std::vector <std::unique_ptr <GraphicsObject>> shapes;
			
			//ClipBoard states
			std::unique_ptr<GraphicsObject> clipboard; 			//To hold the copied/cut shapes
			ClipboardMode mode = ClipboardMode::NONE;
			
			// The Undo and Redo stacks store our Command objects.
			std::stack <std::unique_ptr<Command>> undoStack;
			std::stack <std::unique_ptr <Command>> redoStack;
			
			ToolType currentTool;
    		QColor currentStrokeColor;
    		QColor currentFillColor;
    		int currentStrokeWidth;

    		//Interaction Flags
    		bool isDrawing;				// True if we are currently dragging to create a shape
    		bool isMoving = false;		// True if we are dragging an existing shape
    		bool isResizing = false;// True if we are dragging a resize handle

    		int currentHandle=-1;	// Index (0-7) of the handle being dragged, or -1

    		//Mouse Tracking
    		QPoint startPoint;		//Where did i start holding the mousebutton
    		QPoint currentPoint;		//Where the mouse pointer is currently
    		QPoint lastMousePoint;		//Where the mouse was in the PREVIOUS frame (for deltas)

    		//Temporary Object
    		std::vector <QPoint> sketchPoints; //Buffers points for the FreeHand tool
    		std::unique_ptr<GraphicsObject> tempShape ;		// The "possible" shape shown while dragging
    		GraphicsObject* selectedShape = nullptr ;		// Pointer to the shape currently selected

			// Snapshot of a shape's position BEFORE we start moving it (for Undo)
			QRect initialShapeRect;

			//Helpers
            void applyStyles(GraphicsObject* obj);
			std::unique_ptr<GraphicsObject> createShapeForTool(ToolType tool, QPoint p1, QPoint p2);


};
#endif
