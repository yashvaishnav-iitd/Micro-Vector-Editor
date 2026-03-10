#ifndef TRANSFORM_COMMAND_H
#define TRANSFORM_COMMAND_H

// These headers give us the base Command class and the QRect we need for positioning.
#include "commands.h"
#include "graphics_object.h"
#include <QRect>

// This command handles both moving and resizing. It basically takes a "snapshot" 
// of where the shape was and where it ended up.
class TransformCommand: public Command {
	public:
		// Constructor where we save the shape pointer and the old/new bounding boxes.
		TransformCommand(GraphicsObject* shape, const QRect& oldRect, const QRect& newRect);

		// This runs the "redo" or initial action by snapping the shape to the newRect.
		void execute() override;

		// This reverses the move or resize by putting the shape back in its oldRect.
		void undo() override;


	private:
		// Pointer to the shape we are changing.
		GraphicsObject* shape;

		// We store the two states here so we can toggle between them for undo/redo.
		QRect oldRect;
		QRect newRect;

};

#endif
