#include "parser.h"
#include "polyline.h"

#include <sstream>

// This function parses the "points" string from a <polyline> tag.
void Parser::parsePolyLine(const std::string &line , Canvas* canvas){

	// Grab the long string of coordinates (e.g., "10,10 20,20 30,10")
	std::string pointsStr = getAttributes(line,"points");

	// We use stringstream to easily split the string by spaces.
	std::stringstream ss(pointsStr);
	std::string segment;
	std::vector<QPoint> points;

	// Loop through each "x,y" pair separated by a space.
	while (std::getline(ss,segment,' ')){

		size_t comm = segment.find(',');
		// Check if the comma exists to avoid crashing on bad data.
		if (comm < segment.size()){
			int x = std::stoi(segment.substr(0,comm));
			int y = std::stoi(segment.substr(comm + 1));

			points.emplace_back(x,y);		//Used emplace_back instead of push_back because push_back creates a temporary copy QPoint structure to hold the (x,y) 
											//which emplaces_back does directly so its slightly more efficient.
		}
	}
	// Wrap the collected points into our PolyLine object.
	auto shape = std::make_unique<PolyLine> (points);

	// Apply the usual stroke and fill settings.
	setStyle(shape.get(), line);

	// Give the final shape to the canvas to be drawn.
	canvas->addShape(std::move(shape));

}
