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

void Canvas::mousePressEvent (QMouseEvent *event) {
	lastMousePoint = event ->pos();
	isMoving = false;
	isResizing= false;
	// SELECTION MODE
    // If the user is using the "Select" tool, we aren't drawing new shapes. We are trying to grab or modify existing ones.
	if (currentTool == ToolType::Select){
		//Check Resize Handles
        // If a shape is ALREADY selected, we might be trying to resize it. We check this first because handles sit "on top" of the shape.
		if (selectedShape){
			// Snapshot the current state so we can Undo later if needed
			initialShapeRect = selectedShape -> getBoundingBox();
			std::vector <QRect> handles = getHandles(selectedShape->getBoundingBox());
			// Loop through all 8 handles to see if the mouse clicked inside one
			for (int i = 0; i<8;i++){
				if (handles[i].contains(event->pos())){
					isResizing=true;
					currentHandle=i;	// Remember WHICH handle (e.g., top-left)
					return;				// We found our target, stop processing.
				}
			}
		}
		//Check Shape Bodies
		GraphicsObject* clickedShape = getShapeAt(event->pos());

		if (clickedShape){
			selectedShape = clickedShape;
			isMoving=true;	// We are now ready to drag this shape

			// Update the toolbar colors to match what we just clicked
			currentStrokeColor = selectedShape->getStrokeColor();
			currentFillColor = selectedShape -> getFillColor();
		}
		else{
			//Empty Space
            // If we clicked nothing, deselect everything
			selectedShape =nullptr;
		}
		update();	// Trigger a redraw to show/hide the selection box
		return;
	}

	if (currentTool==ToolType::Text){
		bool ok;
		// Open a popup dialog asking for the text
		QString text = QInputDialog::getText(this, "Add Text", "Enter text:", QLineEdit::Normal,"", &ok);

		if (ok && !text.isEmpty()){
			// Create the text object at the mouse position
			// We use a default font (Arial, 20)
			auto textInp = std::make_unique<Text>(event->pos().x(), event->pos().y(),text.toStdString(), QFont("Arial", 20));

			// Apply current colors
			applyStyles(textInp.get());

			// Add to canvas
			addShape(std::move(textInp));

			update();
		}
		return ;
		
	}
	//DRAWING MODE
    // If we aren't selecting, we must be drawing a new shape.
	isDrawing = true;
	startPoint = event->pos();
	currentPoint= startPoint;

	//Special case for FreeHand: it needs a list of points, not just start/end
	if (currentTool == ToolType::FreeHand){
		sketchPoints.clear();
		sketchPoints.push_back(startPoint);
	}
}