#include "canvas.h"
#include "add_shape_command.h"
#include "change_color_command.h"

// This is the main function to add a shape. It wraps the shape in a command 
// so we can track it in our history.
void Canvas::addShape(std::unique_ptr<GraphicsObject> shape){

	// Create the command and move the shape ownership into it.
	auto cmd = std::make_unique<AddShapeCommand>(this,std::move(shape));
	// Do the actual work of adding it to the canvas list.
	cmd->execute();
	// Save it to the undo stack.
	undoStack.push(std::move(cmd));

	// if you do a new action, you have to clear the redo stack 
    // because the "future" history is now invalid.
	while (!redoStack.empty()){
		redoStack.pop();
	}
	update();	// Refresh the screen.
}

// Logic for the Undo button.
void Canvas::undo(){
	if (undoStack.empty()) {return;}	// Nothing to undo.

	//Gets the most recent command we performed
	auto &cmd = undoStack.top();

	//executes to reverse the command
	cmd->undo();			//this undo is not Canvas::undo() it is AddShapeCommand::undo() for the AddShapeCommand type

	//move the undo command to redo stack
	redoStack.push(std::move(cmd));
	undoStack.pop();
	update();
}

// Logic for the Redo button.
void Canvas::redo(){
	if (redoStack.empty()){return;}	// Nothing to redo.

	//Grab the command that was last undone.
	auto &cmd = redoStack.top();

	//executes the command again
	cmd -> execute();

	//move the redo command back to undo stack
	undoStack.push(std::move(cmd));
	redoStack.pop();
	update();
}
// Completely resets the canvas.
void Canvas::clear(){
	selectedShape = nullptr;	// Stop pointing to something that's about to be deleted.
	tempShape.reset();
	// Wipe the main list of shapes.
	shapes.clear();						

	// Clear all history stacks so the user can't undo into a blank screen.
	while (!undoStack.empty()){undoStack.pop();}		//Clears all undos
	while (!redoStack.empty()){redoStack.pop();}		//Clears all redos
	update();						//updates the window
}

// Changes the color of a shape and records it as a command.
void Canvas::setShapeColor(GraphicsObject* shape, const QColor &strokeColor, const QColor &fillColor){

	if (!shape) {return;}
	// Save the current colors so the command knows what to change back to during Undo.
	QColor oldStrokeColor = shape->getStrokeColor();
	QColor oldFillColor = shape->getFillColor();
	// Create the color change command.
	auto cmd = std::make_unique<ChangeColorCommand>(shape,oldStrokeColor, strokeColor, oldFillColor, fillColor);
	// Apply the new colors.
	cmd->execute();
	// Add to history and clear the redo stack.
	undoStack.push(std::move(cmd));
	while (!redoStack.empty()) {redoStack.pop();}

	update();
}
