#include "change_color_command.h"


// The constructor just saves the shape we are editing and the "before/after" snapshots of both the stroke and fill colors
ChangeColorCommand::ChangeColorCommand(GraphicsObject* shape, const QColor &oldStrokeColor, const QColor &newStrokeColor, const QColor &oldFillColor, const QColor &newFillColor):
	shape(shape), oldStrokeColor(oldStrokeColor), newStrokeColor(newStrokeColor), oldFillColor(oldFillColor), newFillColor(newFillColor){}


// This runs when the user picks a new color or hits 'Redo'.
void ChangeColorCommand::execute(){
	// Safety check to make sure the shape still exists.
	if (!shape) {return;}

	// Update the shape's old colours to the new colours.
	shape->setStrokeColor(newStrokeColor);

	shape->setFillColor(newFillColor);
}

// This runs when the user hits 'Undo'.
void ChangeColorCommand::undo(){
	if (!shape) {return;}

	// We put the shape's colors back to exactly what they were before this comman was created.
	shape -> setStrokeColor (oldStrokeColor);

	shape ->setFillColor(oldFillColor);
}
