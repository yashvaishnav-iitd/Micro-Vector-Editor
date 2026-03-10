#include "canvas.h"

#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include  "polyline.h"
#include "hexagon.h"
#include "rounded_rectangle.h"

#include "delete_shape_command.h"
#include <cmath>

//Copy: Saves a copy of whatever is selected into our 'clipboard' variable
void Canvas::copy() {

	//If something was previously CUT but not pasted, put it back
    if (mode == ClipboardMode::CUT_MODE && clipboard) {
        addShapeInternal(std::move(clipboard));
    }

    if (selectedShape) {
		// Deep copy: We need a new instance, not just a pointer to the existing one.
        clipboard = selectedShape->clone();
        mode = ClipboardMode::COPY_MODE;
		// Mode is Copy, so we can paste it a million times.
	}
}
//Cut: Like copy, but it physically removes the shape from the screen.
void Canvas::cut(){
	//If something was previously CUT but not pasted, put it back
	if (mode == ClipboardMode::CUT_MODE && clipboard) {
        addShapeInternal(std::move(clipboard));
    }
	if (selectedShape){
		// Clone it into the clipboard first.
		clipboard = selectedShape->clone();

		mode = ClipboardMode::CUT_MODE;
		// Use Command Pattern: extract the shape while keeping it alive for Undo
		auto cmd = std::make_unique<DeleteShapeCommand>(this, selectedShape);
		cmd->execute();

		// Save to undo stack and wipe the redo history for this branch.
		undoStack.push(std::move(cmd));

		while (!redoStack.empty()){redoStack.pop();}

		selectedShape = nullptr;
		update();
	}
}

//Paste: Puts the clipboard item back onto the canvas.
void Canvas::paste() {
    if (!clipboard || mode == ClipboardMode::NONE) return;

    if (mode == ClipboardMode::COPY_MODE) {
        //Paste a clone, then move the clipboard template by 20px.
		// This stops multiple pastes from stacking on top of each other.
        auto newShape = clipboard->clone();
        newShape->move(20, 20);
        addShape(std::move(newShape));

		// Move the original clipboard object so the NEXT paste is further down.
		clipboard->move(20,20);
    } 
    else if (mode == ClipboardMode::CUT_MODE) {
        // Move the unique_ptr out of the clipboard. 
        // Once moved, 'clipboard' becomes nullptr.
        auto newShape = std::move(clipboard);
        newShape->move(20, 20);
        
        // Add to canvas and reset state so we can't paste a cut object twice.
        addShape(std::move(newShape));
        clipboard = nullptr;
        mode = ClipboardMode::NONE;
    }
}