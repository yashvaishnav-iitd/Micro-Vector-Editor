#include "rounded_rectangle.h"
#include <sstream>
#include <QRect>

// Simple constructor to initialize the geometry and those corner radii (rx, ry).
RoundedRectangle::RoundedRectangle(int x, int y, int w, int h, int rx, int ry):
	x(x), y(y), w(w), h(h), rx(rx), ry(ry){}

void RoundedRectangle::draw(QPainter &painter) const {
	
	// This calls the base class helper to set the current pen and brush.
	applyStyle(painter);

	// Qt has a built-in function for this, which makes rendering easy.
	painter.drawRoundedRect(x,y,w,h,rx,ry);
}

// This builds the SVG line. Even though it's a "rounded" rect, the SVG tag is still <rect>.
std::string RoundedRectangle::toString() const{

	std::stringstream ss;

	// We just add the rx and ry attributes to the standard rectangle tag.
	ss << "<rect ";
 	ss << "x=\"" << x << "\" ";
	ss << "y=\"" << y << "\" ";
	ss << "width=\"" << w << "\" ";
	ss << "height=\"" << h << "\" ";
	ss << "rx=\"" << rx << "\" ";
	ss << "ry=\"" << ry << "\" ";

	// Adding the styling attributes so the SVG file keeps the colors.
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

// Check if the mouse is inside. We use normalized() in case width/height are negative.
bool RoundedRectangle::contains (const QPoint &point) const {

	QRect rect(x,y,w,h);
	return rect.normalized().contains(point);
}

// Just update the top-left corner by the mouse delta.
void RoundedRectangle::move (int dx, int dy){
	x+=dx;
	y+=dy;
}

// Returns the current boundary. normalized() ensures it works even if dragged backwards.
QRect RoundedRectangle::getBoundingBox() const{

        return QRect (x,y,w,h).normalized();
}

// Updates the box during a resize.
void RoundedRectangle::setBoundingBox(const QRect &rect, int handle){
	Q_UNUSED(handle);

	x=rect.x();
	y=rect.y();
	w=rect.width();
	h=rect.height();

	// Safety check: if the rectangle gets too small, we shrink the corner radius so the corners don't overlap or look broken.
	if (w>0 && rx* 2>w) {rx = w/2;}
	if (h>0 && ry*2 >h) {ry = h/2;}
}

std::unique_ptr<GraphicsObject> RoundedRectangle::clone() const {
    auto newRR = std::make_unique<RoundedRectangle>(x, y, w, h, rx, ry);
    newRR->copyStylesFrom(this);
    return newRR;
}