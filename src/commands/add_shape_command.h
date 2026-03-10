#ifndef ADD_SHAPE_COMMAND_H
#define ADD_SHAPE_COMMAND_H

#include "commands.h"
#include "graphics_object.h"
#include <memory>

// Forward declaration of Canvas to avoid circular dependency errors 
// (because Canvas.h includes this file, so we can't include Canvas.h here).
class Canvas;

// Concrete command for adding shapes. This allows us to push the "Add" action
// onto the undo stack so we can reverse it later
class AddShapeCommand : public Command{
	public: 
		// Constructor takes the canvas pointer and transfers ownership of the 
		// new shape to this command using std::move.
		AddShapeCommand (Canvas* canvas, std::unique_ptr<GraphicsObject> shape);

		// The "Do" logic: Moves the shape pointer from this object into the 
		// Canvas's shape vector so it gets drawn.
		void execute() override;

		// The "Undo" logic: Removes the shape from the Canvas and moves ownership 
		// back here, so we can Redo it if needed.
		void undo() override;

	private:
		// We need to know which Canvas to modify.
		Canvas* canvas;

		// The shape itself. It lives here when "Undone", and lives in the 
		// Canvas when "Executed"
		std::unique_ptr<GraphicsObject> shape;

};

#endif
