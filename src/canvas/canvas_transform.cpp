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

void Canvas::mouseMoveEvent(QMouseEvent *event){

	//Editing (Moving or Resizing)
	if (selectedShape && (isMoving || isResizing)){

		// Calculate how far the mouse moved since the last frame
		int dx = event->pos().x() - lastMousePoint.x();
		int dy = event->pos().y() - lastMousePoint.y();


		if (isResizing){
			// Ask the shape to resize itself based on the handle we are holding
			selectedShape->resize(currentHandle,dx,dy);		
		}
		else{
			// Just translate the shape's position
			selectedShape->move(dx,dy);
		}

		// Critical: Update lastMousePoint so the next delta is correct
		lastMousePoint = event->pos();
		update();
		return;
	}

	//DRAWING (Previewing)
	if (!isDrawing) {return;}
	currentPoint = event->pos();

	// While the mouse is down, we constantly delete and recreate the "tempShape"
    // This creates the visual effect of dragging out a shape (rubber-banding).
	if (currentTool==ToolType::FreeHand){
		sketchPoints.push_back(currentPoint);
		tempShape = std::make_unique<PolyLine>(sketchPoints);
	}
	else{
		// For geometric shapes, create a new one based on start/current points
		tempShape = createShapeForTool (currentTool, startPoint,currentPoint);
	}
	// Make sure the preview shape has the correct colors
	if (tempShape){
	applyStyles(tempShape.get());
	}
	update();// Request a repaint to show the new tempShape
}