#ifndef TOOL_TYPE_H
#define TOOL_TYPE_H

// This enum acts as the "State" for our editor. It tells the Canvas 
// exactly what to do when the mouse is clicked or dragged.
enum class ToolType {

	None,				// Default state where the mouse does nothing.
	Select,				// Used for grabbing, moving, and resizing existing shapes.
	Circle,				//Triggers the creation of a Circle object.
	Rectangle,			//Triggers the creation of a Rectangle object.
	Hexagon,			//Triggers the creation of a Hexagon object.
	Line,				// Triggers the creation of a Line object.
	FreeHand,			// Used for the pencil tool (PolyLine).
	RoundedRectangle,	//Triggers a Rectangle with rounded corners.
	Text 				//Triggers the creation of Text.
};

#endif
