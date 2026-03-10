#include "add_shape_command.h"
#include "canvas.h"

// Constructor:
// We take ownership of the shape immediately. It now lives inside this Command object,
// waiting to be executed or undone.
AddShapeCommand :: AddShapeCommand (Canvas* canvas, std::unique_ptr<GraphicsObject> shape)
	:canvas(canvas), shape(std::move(shape)){}

// Execute (Do/Redo):
// To "do" the action, we give the shape to the Canvas.
// The Canvas now owns the memory and will display the shape.
void AddShapeCommand::execute(){

		if (shape){
			canvas->addShapeInternal(std::move(shape));
		}
}

// Undo:
// To "undo" the action, we take the shape BACK from the Canvas.
// It is removed from the screen, but NOT deleted. It lives safely inside
// this Command object again, just in case the user hits Redo.
void AddShapeCommand::undo(){
		shape = canvas->popShapeInternal();
}
