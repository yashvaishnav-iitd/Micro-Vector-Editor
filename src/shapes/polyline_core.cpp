#include "polyline.h"
#include <sstream>
#include <QPainterPath>
#include <limits>
#include <algorithm>

//Initializes the polyline with a list of points
PolyLine::PolyLine (const std::vector <QPoint> & points)
	:points(points){}


void PolyLine::draw ( QPainter &painter) const{
	// A line needs at least two points to exist!
	if (points.size() < 2) {return;}

	//Applying styles
	applyStyle (painter);

	// We use QPainterPath to connect all the dots in the vector
	QPainterPath path;

	// Start at the first point
	path.moveTo(points[0]);

	// Draw a line to every subsequent point in the list
	for (size_t i = 1; i <points.size(); i++){
		path.lineTo(points[i]);
	}
	
	//Draw the path and fill it if brush is set
	painter.drawPath(path);
}

std::string PolyLine::toString() const{
	std::stringstream ss;
    	// Format: <polyline points="0,0 10,10 20,20" stroke="black" ... />
  	ss << "<polyline points=\"";
    	for (size_t i = 0; i < points.size(); ++i) {
			// Points are stored as x,y pairs separated by spaces	
        	ss << points[i].x() << "," << points[i].y();
        	if (i < points.size() - 1) {
            		ss << " "; // Space separator between coordinate pairs
        	}
    	}
    	ss << "\" ";
    	// Standard style attributes
    	ss << "stroke=\"" << getStrokeColor().name().toStdString() << "\" ";
    	ss << "stroke-width=\"" << getStrokeWidth() << "\" ";
	
	//Ensure hollow shapes stay hollow by using fill="none"
	if (getFillColor() == Qt::transparent){
        	ss << "fill=\"none\" ";
	}
    	else{
        	ss << "fill=\"" << getFillColor().name().toStdString() << "\" ";
	}
	ss << "/>";

	return ss.str();
}

// Moves every single point in the polyline by the same offset
void PolyLine::move(int dx, int dy){
	for (auto &p : points){
		p.rx() +=dx;	// rx() and ry() let us modify the point coordinates directly
		p.ry() +=dy;
	}
}

// Creates an exact copy of this polyline for the clipboard
std::unique_ptr<GraphicsObject> PolyLine::clone() const {
    // We pass the existing vector of points to the constructor
    auto newPoly = std::make_unique<PolyLine>(points);
	// Copy colors and line width
    newPoly->copyStylesFrom(this);
    return newPoly;
}