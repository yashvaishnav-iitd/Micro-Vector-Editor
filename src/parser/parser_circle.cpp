#include "parser.h"
#include "circle.h"

// This function parses the attributes of a <circle> tag from an SVG line.
void Parser::parseCircle(const std::string &line, Canvas* canvas){

	// SVG circles use 'cx' and 'cy' for the center point.
	int cx = std::stoi(getAttributes(line,"cx"));
	int cy = std::stoi(getAttributes(line,"cy"));

	// 'r' is the radius of the circle.
	int r = std::stoi(getAttributes(line,"r"));

	// We create the Circle object using make_unique for safe memory management.
	auto shape = std::make_unique<Circle>(cx,cy,r);

	// Apply the styles(stroke,fill,width)
	setStyle(shape.get(), line);

	//Move the shape into canvas's vector of shapes
	canvas->addShape(std::move(shape));
}

