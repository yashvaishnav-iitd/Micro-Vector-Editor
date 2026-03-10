#include "circle.h"
#include <sstream> //For building the SVG string
#include <cmath>
#include <algorithm>

//  Saves center coordinates and radius
Circle :: Circle (int cx , int cy ,int r) 
	: cx(cx), cy(cy) ,r(r){}

// Renders the circle using Qt's QPainter
void Circle::draw(QPainter& painter) const {
	//Drawing styles
	applyStyle(painter);
	//For drawing the circle
	painter.drawEllipse(QPoint(cx,cy),r,r);
}

// Moves the center point during dragging
void Circle::move (int dx, int dy){
	cx+=dx;
	cy+=dy;
}

// Deep copy for Copy/Paste functionality
std::unique_ptr<GraphicsObject> Circle::clone() const {
    // Create a new circle with the same geometry (center x, center y, radius)
    auto newCircle = std::make_unique<Circle>(cx, cy, r);
    
    // Copy the style attributes
    newCircle -> copyStylesFrom(this);
    
    return newCircle;
}

// Converts the circle to an SVG string for saving
std::string Circle::toString () const {
	std::stringstream ss;
	//Format must match SVG standards
	ss << "<circle ";
	ss << "cx=\""<< cx << "\" ";
	ss << "cy=\""<< cy << "\" ";
	ss << "r=\"" << r << "\" ";

	//Style Attrinutes
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