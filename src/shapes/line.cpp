#include "line.h"
#include <sstream>

// Constructor to store the start and end points of the line.
Line::Line (int x1, int y1, int x2, int y2):
	x1(x1), y1(y1), x2(x2), y2(y2){}

void Line::draw (QPainter& painter) const {

	//Applying styles (thickness,StrokeColor,FillColor)
	applyStyle(painter);


	//Drawing the line from (x1,y1) to (x2,y2)
	painter.drawLine(x1,y1,x2,y2);
}

// Converts the line data into an SVG <line> element.
std::string Line::toString() const{
	std::stringstream ss;

	// Format: <line x1="0" y1="80" x2="100" y2="20" stroke="black" ... />
	ss << "<line ";
    	ss << "x1=\"" << x1 << "\" ";
    	ss << "y1=\"" << y1 << "\" ";
    	ss << "x2=\"" << x2 << "\" ";
    	ss << "y2=\"" << y2 << "\" ";
    
    	// Lines don't use 'fill', but we keep the stroke properties.
    	ss << "stroke=\"" << getStrokeColor().name().toStdString() << "\" ";
    	ss << "stroke-width=\"" << getStrokeWidth() << "\" ";
    	ss << "/>";

	return ss.str();
}

// Collision detection: Check if the mouse click is near the line.
bool Line::contains (const QPoint &point) const {

	// Because a line is mathematically thin, we add a 5-pixel "buffer" zone so users can actually click on it easily.
	int minX = std::min(x1,x2) - 5;
	int maxX = std::max(x1,x2) +5;

	int minY = std::min(y1,y2) - 5;
	int maxY = std::max(y1,y2) + 5;

	return (point.x() >= minX && point.x()<=maxX &&
		point.y() >= minY && point.y()<=maxY);
}

// Moves the entire line by shifting both endpoints.
void Line::move (int dx, int dy) {
	x1+=dx;
	x2+=dx;
	y1+=dy;
	y2+=dy;
}

// Returns a QRect that tightly fits the line, used for showing selection handles.
QRect Line::getBoundingBox() const{

	// normalized() ensures the box is valid even if x1 > x2.
	return QRect(QPoint(x1,y1), QPoint(x2,y2)).normalized();
}

// This updates the line during a resize.
void Line::setBoundingBox (const QRect &rect, int handle){
	Q_UNUSED(handle);

	// We check the original orientation (x1 vs x2) so the line doesn't exhange its start and end points unexpectedly when resizing.

	if (x1<=x2){
		x1 = rect.left();
		x2 = rect.right();
	}
	else{
		x1 = rect.right();
		x2 = rect.left();
	}

	if (y1<=y2){
		y1 = rect.top();
		y2 = rect.bottom();
	}
	else{
		y1= rect.bottom();
		y2 = rect.top();
	}
}

std::unique_ptr<GraphicsObject> Line::clone() const {
    // Create the new Line with geometry
    auto newLine = std::make_unique<Line>(x1, y1, x2, y2);
    
	//For copying the styles of the line
    newLine->copyStylesFrom(this);
    
    return newLine;
}