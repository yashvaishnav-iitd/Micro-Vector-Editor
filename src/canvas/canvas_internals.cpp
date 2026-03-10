#include "canvas.h"
#include "graphics_object.h"

// Basic setter to switch which drawing tool is active.
void Canvas::setTool(ToolType tool){
	currentTool=tool;
}

// Basic getter to check the current tool.
ToolType Canvas::getTool() const{
	return currentTool;
}
// Changes the border color. If a shape is selected, it updates that shape immediately.
void Canvas::setStrokeColor(const QColor &color){
	currentStrokeColor = color;

	if (selectedShape){
		QColor existingFillColor = selectedShape->getFillColor();
		// We use setShapeColor here so the change is recorded in the Undo stack.
		setShapeColor(selectedShape,currentStrokeColor,existingFillColor);
		update();
	}
}
// Changes the inside color. Works just like the stroke color logic above.
void Canvas::setFillColor(const QColor &color){
	currentFillColor = color;
	if (selectedShape){
		QColor existingStrokeColor = selectedShape->getStrokeColor();
		setShapeColor(selectedShape, existingStrokeColor, currentFillColor);
		update();
	}
}
// Updates the thickness of the lines for the next shapes we draw.
void Canvas::setStrokeWidth(int width){
	currentStrokeWidth = width;
}
// Helper that actually pushes a shape into our vector.
// We use std::move because unique_ptrs can't be copied, only moved.
void Canvas::addShapeInternal(std::unique_ptr<GraphicsObject> shape){

	if(!shape) {return;}

	shapes.push_back(std::move(shape));
}
// Helper to remove the last shape. Used by the Undo command.
std::unique_ptr <GraphicsObject> Canvas::popShapeInternal (){
	if (shapes.empty()) {return nullptr;}

	// Safety check: if the shape we're removing is currently selected,
	// we need to clear the selection pointer so the app doesn't crash.
	if (shapes.back().get() ==selectedShape){
		selectedShape =nullptr;
		isMoving = false;
		isResizing=false;
		currentHandle=-1;
	}
	// Grab the shape, remove it from the list, and return it to the caller.
	std::unique_ptr<GraphicsObject> obj = std::move(shapes.back());
	shapes.pop_back();
	update();
	return obj;
}
// Just returns a raw pointer to the most recently added shape.
GraphicsObject* Canvas::getLastShape(){
	if (shapes.empty()) {return nullptr;}

	return shapes.back().get();
}
// Utility to apply the current toolbar settings (colors/width) to a shape.
void Canvas::applyStyles(GraphicsObject* shape){
	if (!shape) {return;}

	shape->setStrokeColor(currentStrokeColor);
	shape->setStrokeWidth(currentStrokeWidth);
	shape ->setFillColor(currentFillColor);
}
// This handles "Hit Testing" to see what the user clicked on.
GraphicsObject* Canvas::getShapeAt(const QPoint &point){
	// We loop backwards so that if shapes overlap, we pick the one
	// that is visually "on top" (the one added last).
	for (int i = static_cast<int>(shapes.size()) -1; i>=0; --i){

		if (shapes[i] ->contains(point)){
			return shapes[i].get();	// Return raw pointer for temporary use.
		}
	}
	return nullptr;
}
// Gives other classes read-only access to our shape collection.
const std::vector<std::unique_ptr<GraphicsObject>> & Canvas::getShapes() const{
	return shapes;
}


