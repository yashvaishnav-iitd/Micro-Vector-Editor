#include "rectangle.h"
#include <sstream>
#include <algorithm>

// Simple constructor to set the initial position and size.
Rectangle::Rectangle (int x, int y , int w , int h) : 
	x(x), y(y) ,w(w), h(h){}

void Rectangle::draw(QPainter& painter) const {
	
	//Applying the styles
	applyStyle(painter);
	
	//Actually Drawing the rectangle
	painter.drawRect(x,y,w,h);
}

// This function generates the XML/SVG line for this shape.
std::string Rectangle::toString() const {
    std::stringstream ss;

	// We build the <rect> tag with all the required SVG attributes.
    ss << "<rect ";
    ss << "x=\"" << x << "\" ";
    ss << "y=\"" << y << "\" ";
    ss << "width=\"" << w << "\" ";
    ss << "height=\"" << h << "\" ";

	// We also include the colors and line thickness so it looks right when opened elsewhere.
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

//Point-testing to see if the user clicked on this rectangle.
bool Rectangle::contains(const QPoint &point) const{

	return getBoundingBox().contains(point);

}

// Updates the top-left corner during a move operation.
void Rectangle::move (int dx, int dy) {
	x+=dx;
	y+=dy;
}

// Returns the current box. We use normalized() so it works even if width is negative.
QRect Rectangle::getBoundingBox() const{

	return QRect (x,y,w,h).normalized();
}

// This is called during a resize to update the internal coordinates.
void Rectangle::setBoundingBox(const QRect &rect,int handle){
	Q_UNUSED(handle);
	
	QRect safe = rect.normalized();
	
	x=safe.x();
	y=rect.y();
	w=rect.width();
	h=rect.height();
}


std::unique_ptr<GraphicsObject> Rectangle::clone() const {
    // Create a new rectangle with the same geometry
    auto newRect = std::make_unique<Rectangle>(x, y, w, h);
    
    // Copy the style attributes from the current object
    newRect ->copyStylesFrom(this);
    
    return newRect;
}