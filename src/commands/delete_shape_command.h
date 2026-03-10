#ifndef DELETE_SHAPE_COMMAND_H
#define DELETE_SHAPE_COMMAND_H

#include "commands.h"
#include "graphics_object.h"
#include <memory>

// Forward declaration of Canvas to avoid circular dependencies.
// We only need the compiler to know 'Canvas' is a class for the pointer below.
class Canvas; 


 // DeleteShapeCommand: This is the command that handles removing and restoring shapes.
 //  It's the core of the Cut/Delete Undo logic.
 
class DeleteShapeCommand : public Command {
public:
    // Constructor: Takes the canvas where the shape is and the raw pointer of the shape we want to target
    DeleteShapeCommand(Canvas* canvas, GraphicsObject* target);

   // Transfers the shape from the Canvas to this command (Called during cut() operation)
    void execute() override;

    //Transfers the shape back from this command to the Canvas. (This is called when the user hits the Undo button after cutting or cut/paste)
    void undo() override;

private:
    // Pointer back to the canvas so we can call its internal helpers
    Canvas* canvas;
    // The raw pointer of the shape we are looking for in the vector.
    GraphicsObject* target;

    //This unique_ptr stores the actual object while // it's not on the canvas.
    
    std::unique_ptr<GraphicsObject> removedShape;   // Internal storage for Undo
};

#endif