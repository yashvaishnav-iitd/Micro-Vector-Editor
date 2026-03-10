#include "parser.h"
#include "polyline.h"

#include <sstream>


// This function handles hexagons by parsing their vertex points.
void Parser::parseHexagon (const std::string &line, Canvas* canvas){

	// We extract the "points" attribute string from the SVG tag.
	std::string pointsStr= getAttributes(line, "points");

	// stringstream helps us break the coordinate string apart by spaces.
	std::stringstream ss(pointsStr);
	std::string segment;
	std::vector <QPoint> points;

	// We loop through each vertex pair (x,y).
	while (std::getline(ss, segment, ' ')){

		size_t comm = segment.find(',');

		if (comm < segment.length()){
			// Convert the string coordinates into actual integers.
			int x = std::stoi(segment.substr(0,comm));
			int y = std::stoi(segment.substr(comm+1));

			// Store the point directly in our vector.
			points.emplace_back(x,y);

		}
	}



	auto shape = std::make_unique<PolyLine>(points);	//We are using polyLine.h for points because the cx,cy and radius of the hexagon are lost when we convert them into SVG format.
														//So we can't use hexagon constructor in make_unique, since it needs the arguments cx, cy and r which we don't have
														//We only have the coordinates of the vertices.

	//Apply the styles													
	setStyle(shape.get(),line);

	//Transfer the finished shape to canvas
	canvas->addShape(std::move(shape));

}
