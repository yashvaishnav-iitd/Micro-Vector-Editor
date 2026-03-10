#include "hexagon.h"
#include <sstream>
#include <cmath>  //For cos, sin ,M_PI
#include <QPolygon> //Useful for 'contains' check


//Saves the center (cx, cy) and the radius
Hexagon :: Hexagon (int cx, int cy, int r) :
	cx(cx), cy(cy) , r(r){}


void Hexagon::draw (QPainter &painter) const{
	//Applying the styles
	applyStyle (painter);
	
	// Get the 6 vertices and draw them as a closed polygon
	std::vector <QPoint> pts =  getPoints();
	painter.drawPolygon(pts.data(),6);
}

// Moves the center of the hexagon when dragging
void Hexagon::move(int dx, int dy){
	cx+=dx;
	cy+=dy;
}
// Creates a deep copy of this hexagon for Copy/Paste
std::unique_ptr<GraphicsObject> Hexagon::clone() const {
    // Create a new hexagon with the same center and size
    auto newHex = std::make_unique<Hexagon>(cx, cy, r);
	// Use the base class helper to copy over stroke/fill colors
    newHex->copyStylesFrom(this);
    return newHex;
}

// Checks if a mouse click is inside the hexagon body
bool Hexagon::contains( const QPoint &point) const {
	std::vector<QPoint> pts = getPoints();
	QPolygon poly;
	// Convert our points to a QPolygon so we can use Qt's math
	for (const auto& p : pts){
		poly <<p;
	}
	// Uses the Odd-Even fill rule to determine if point is inside
	return poly.containsPoint(point, Qt::OddEvenFill);
}

// Converts the hexagon to an SVG <polygon> tag
std::string Hexagon::toString () const{
	std::stringstream ss;
	//SVG Uses polygon for hexagon
	ss << "<polygon points=\"";
	std::vector <QPoint> ptss = getPoints();
	for (size_t i= 0 ; i<ptss.size(); i++){
		ss << ptss[i].x() << "," << ptss[i].y();	
		if (i<ptss.size() - 1){
			ss<<" ";
		}
	}
	ss << "\" ";
	// Border color and line thickness
	ss << "stroke=\"" << getStrokeColor().name().toStdString() << "\" ";
    ss << "stroke-width=\"" << getStrokeWidth() << "\" ";
    // Check if the fill is transparent
    if (getFillColor() == Qt::transparent) {
        ss << "fill=\"none\" ";
    } else {
        ss << "fill=\"" << getFillColor().name().toStdString() << "\" ";
    }
    ss << "/>";
    	
	return ss.str();
}