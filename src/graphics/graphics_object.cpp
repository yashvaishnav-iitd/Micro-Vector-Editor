#include "graphics_object.h"
#include <algorithm>


// Constructor sets up default "blank canvas" styles so shapes aren't invisible.
GraphicsObject::GraphicsObject()
	:strokeColor(Qt::black), fillColor(Qt::transparent), strokeWidth(1){}

//Stroke Color
QColor GraphicsObject::getStrokeColor () const {
        return strokeColor;
}
void GraphicsObject::setStrokeColor(const QColor &color){
	strokeColor = color;
}

//Fill Color
QColor GraphicsObject::getFillColor () const{
        return fillColor;
}
void GraphicsObject::setFillColor (const QColor &color){
	fillColor=color;
}

//Stroke Width
int GraphicsObject::getStrokeWidth () const{
	return strokeWidth;
}
void GraphicsObject::setStrokeWidth(int width){
	strokeWidth= width;
}


//Helper for applying all the styles in a go.
void GraphicsObject::applyStyle (QPainter &painter) const{
	
	//Pen Setup
	QPen pen(strokeColor);
	pen.setWidth(strokeWidth);
	painter.setPen(pen);

	//Brush setup (color)
	painter.setBrush(fillColor);		//If color is Qt::transparent then it won't fill any color (transparent)
	
}

// This handles the math for the 8 selection handles (corners and midpoints).
// Handle index (0-7) goes clockwise starting from top-left.
void GraphicsObject::resize (int handle, int dx, int dy){

	QRect rect = getBoundingBox();
	int x= rect.x();
	int y = rect.y();
	int w = rect.width();
	int h = rect.height();

	// Horizontal resizing: Handles on the left side (0, 7, 6)
	if (handle==0 || handle ==7 || handle ==6){
		x+=dx;
		w-=dx;		// Moving the left edge right reduces the width.
	}
	
	// Horizontal resizing: Handles on the right side (2, 3, 4)
	else if (handle == 2 || handle == 3 || handle ==4){
		w+=dx;
	}
	
	// Vertical resizing: Handles on the top side (0, 1, 2)
	if (handle == 0 || handle == 1 || handle == 2){
		y+=dy;
		h-=dy;			// Moving the top edge down reduces the height.
	}
	
	// Vertical resizing: Handles on the bottom side (4, 5, 6)
	else if (handle == 4 || handle == 5 || handle==6){
		h+=dy;
	}
	
	// Prevents the shape from disappearing .
	if (w<5) {w=5;}
	if (h<5) {h=5;}

	// Finalize the new box by calling the child's implementation.
	setBoundingBox(QRect(x,y,w,h),handle);
}

//Style Copying: This is a helper that lets one shape "mimic" the look of another.
 // It is mostly used during the clone() process to make sure the new shape
 //has the same colors and line thickness as the original.
void GraphicsObject::copyStylesFrom(const GraphicsObject* other) {
    if (!other) return;						//Safety check: If there's no other shape to copy from, just stop
    this->setStrokeColor(other->getStrokeColor());	//This handles the Stroke (border) color.
    this->setFillColor(other->getFillColor());		// This handles the Fill (interior) color.
    this->setStrokeWidth(other->getStrokeWidth());	// This handles the Stroke Width (line thickness).
}