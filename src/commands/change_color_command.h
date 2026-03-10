#ifndef CHANGE_COLOR_COMMAND_H
#define CHANGE_COLOR_COMMAND_H

#include "commands.h"
#include "graphics_object.h"
#include <QColor>


// This command handles changing the border (stroke) and interior (fill) colors of a shape.
//essential for a functional undo/redo system.
class ChangeColorCommand : public Command {
	public:
		// We take pointers to the shape being edited and record the "before" and "after" colors so we can toggle between them easily.
		ChangeColorCommand( GraphicsObject* shape, const QColor &oldStrokeColor, const QColor &newStrokeColor, const QColor &oldFillColor, const QColor &newFillColor);

		// Sets the shape to the 'new' colors
		void execute() override;

		// Reverts the shape back to the 'old' colors.
		void undo() override;

	private:
		GraphicsObject* shape;				// The target object
		QColor oldStrokeColor, newStrokeColor;		// Border color states
		QColor oldFillColor, newFillColor;			// Fill color states

};

#endif

