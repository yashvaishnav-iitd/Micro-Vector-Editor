#include "canvas.h"

#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include  "polyline.h"
#include "hexagon.h"
#include "rounded_rectangle.h"

#include "delete_shape_command.h"
#include <cmath>

// This is basically a "Shape Factory" function. It takes the start and end 
// points from the mouse drag and creates the right object.
std::unique_ptr<GraphicsObject> Canvas::createShapeForTool(ToolType tool, QPoint p1, QPoint p2){
	// Calculate the width and height based on the drag distance.
	int w = p2.x() - p1.x();
	int h = p2.y() - p1.y();

	// Decide which class to instantiate based on the current tool.
	if (tool == ToolType::Rectangle) {
		//Rectangle using top-left corner and dimensions
		return std::make_unique<Rectangle>(p1.x(), p1.y(), w, h);
	}
	else if (tool == ToolType::RoundedRectangle) {
		// Similar to rectangle, but with fixed corner radii.
		return std::make_unique<RoundedRectangle>(p1.x(), p1.y(), w, h, 20, 20);
	}
	else if (tool == ToolType::Circle) {
		// Calculate radius from diagonal distance
		int r = static_cast<int>(std::hypot(w, h));
		return std::make_unique<Circle>(p1.x(), p1.y(), r);
	}
	else if (tool == ToolType::Line) {
		// A simple line connecting the start point to the end point
		return std::make_unique<Line>(p1.x(), p1.y(), p2.x(), p2.y());
	}
	else if (tool == ToolType::Hexagon) {
		// Hexagons also use the diagonal drag distance for their size
		int r = static_cast<int>(std::hypot(w, h));
		return std::make_unique<Hexagon>(p1.x(), p1.y(), r);
	}
	// If no matching tool is found, return nothing.
	return nullptr;
}



