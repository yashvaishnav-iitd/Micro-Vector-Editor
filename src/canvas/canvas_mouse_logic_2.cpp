#include "canvas.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "polyline.h"
#include "hexagon.h"
#include "rounded_rectangle.h"
#include <QMouseEvent>
#include <cmath>
#include "transform_command.h"

#include <QInputDialog> 
#include "text.h"


void Canvas::mouseReleaseEvent (QMouseEvent *event){
	Q_UNUSED(event); //Was getting warnings

	//FINISHING AN EDIT
	if (isMoving || isResizing) {
		if (selectedShape){
			QRect finalRect = selectedShape->getBoundingBox();
			// We only want to add an Undo command if the shape actually changed.
            // (e.g., if the user clicked but didn't drag, don't fill the history stack).
			if (finalRect!=initialShapeRect){
				// Create the command to save this transformation
				auto cmd = std::make_unique <TransformCommand>(selectedShape,initialShapeRect,finalRect);
				undoStack.push(std::move(cmd));
				// Standard Undo behavior: New action clears the Redo history
				while (!redoStack.empty()){
					redoStack.pop();
				}
			}
		}
		// Reset all flags
		isMoving = false;
		isResizing = false;
		currentHandle= -1;
		update();
		return;
	}
	// Finishing the drawing
	if (!isDrawing) {return;}
	isDrawing=false;
	// The user let go of the mouse, so "tempShape" becomes a real shape.
	if (tempShape){
		addShape(std::move(tempShape)); 	// Transfer ownership to the main list
		tempShape.reset();					// Clear the temp pointer
	}
	update();
}