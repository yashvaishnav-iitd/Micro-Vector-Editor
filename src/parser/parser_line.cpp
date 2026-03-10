#include "parser.h"
#include "line.h"

// This function pulls the start and end coordinates from an SVG <line> tag.
void Parser::parseLine(const std::string &line , Canvas* canvas){

	// SVG lines use x1, y1 for the start and x2, y2 for the end point.
	int x1 = std::stoi(getAttributes(line,"x1"));
	int x2 = std::stoi(getAttributes(line,"x2"));
	
	int y1 = std::stoi(getAttributes(line,"y1"));
	int y2 = std::stoi(getAttributes(line,"y2"));

	// We create the Line object using make_unique for safe memory management.
	auto shape = std::make_unique<Line>(x1,y1,x2,y2);

	// Apply the colors and thickness parsed from the rest of the line.
	setStyle(shape.get(),line);
	
	// Transfer the unique_ptr to the canvas's shape list.
	canvas->addShape(std::move(shape));
}
