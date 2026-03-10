#include "transform_command.h"

// Simple constructor to save the shape and the "before and after" rectangles.
TransformCommand::TransformCommand (GraphicsObject* shape, const QRect &oldRect, const QRect &newRect)
	: shape(shape), oldRect(oldRect), newRect(newRect){}

// This runs when we first move/resize something, or when we hit 'Redo'.
void TransformCommand::execute(){
	if (shape){

		// We set the shape to the new position/size. The '-1' tells the shape that this is a direct box update, not a specific handle resize.
		shape -> setBoundingBox(newRect,-1);
	}
}

// This runs when we hit 'Undo'. It just changes the shape back to the oldRect.
void TransformCommand::undo(){
	if (shape){

		//This effectively takes the shape back to exactly where it was before the user started dragging the mouse.
		shape->setBoundingBox(oldRect,-1);
	}
}
