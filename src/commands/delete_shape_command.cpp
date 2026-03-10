#include "delete_shape_command.h"
#include "canvas.h"


/**
 * Constructor: Just saving the pointers for later. 
 * We need the canvas pointer to call its internal helper functions, 
 * and the target pointer to know WHICH shape we are deleting.
 */
DeleteShapeCommand::DeleteShapeCommand(Canvas* canvas, GraphicsObject* target)
    : canvas(canvas), target(target) {}


/**
 * Execute: This is called when the user hits 'Cut' or 'Delete'.
 * Instead of just deleting the shape, we "pluck" it out of the canvas 
 * and store it inside this command object.
 */
void DeleteShapeCommand::execute() {
    // We call extractShapeInternal to find the shape in the shapes vector,
    // move its unique_ptr out of the list, and hand it to removedShape.
    // This keeps the shape alive in memory even though it's gone from the screen.
    removedShape = canvas->extractShapeInternal(target);
}

/**
 * Undo: This is called when the user hits 'Undo' after a deletion.
 * We just do the exact opposite of execute().
 */
void DeleteShapeCommand::undo() {
    // If we are currently holding a removed shape..
    if (removedShape) {
        // We give the pointer back to the canvas
        // We use addShapeInternal so it doesn't trigger another command.
        canvas->addShapeInternal(std::move(removedShape));
    }
}