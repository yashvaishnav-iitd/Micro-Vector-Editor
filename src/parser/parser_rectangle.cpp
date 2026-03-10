#include "parser.h"
#include "rectangle.h"
#include "rounded_rectangle.h"
#include <memory>

// This function looks at a <rect> tag and figures out if it's a normal rectangle
// or a rounded one based on the rx/ry attributes
void Parser::parseRect (const std::string &line , Canvas* canvas){

	// First, we pull out the basic geometry. Every rect has these four
	int x = std::stoi(getAttributes(line,"x"));
	int y = std::stoi(getAttributes(line,"y"));
	int w = std::stoi(getAttributes(line,"width"));
	int h = std::stoi(getAttributes(line,"height"));

	// We check for rx and ry to see if the corners should be curved
	std::string rxStr = getAttributes(line,"rx");
	std::string ryStr = getAttributes(line,"ry");

	// Using a smart pointer here so we don't have to worry about memory leaks
	std::unique_ptr<GraphicsObject> shape;

	// If either rx or ry exists, we need to create a RoundedRectangle
	if (!rxStr.empty() || !ryStr.empty()) {
		int rx = 0;
		int ry = 0;

		if (!rxStr.empty()){
			rx = std::stoi(rxStr);}

		if (!ryStr.empty()){
			ry = std::stoi(ryStr);}

    		// SVG default behavior: if only one radius is given, the other one has the sam evalue
    		if (rxStr.empty())
			{rx = ry;}

    		if (ryStr.empty())
			{ry = rx;}
		shape = std::make_unique<RoundedRectangle>(x, y, w, h, rx, ry);
	}
	else {
		// No curve attributes found, so it's just a regular rectangle
		shape = std::make_unique<Rectangle>(x,y,w,h);
	}

	//Apply the colors and stroke width before adding it to the canvas
	setStyle(shape.get(), line);

	// Finally, hand ownership of the new shape over to the canvas
	canvas->addShape(std::move(shape));
}
